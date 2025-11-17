use core::ptr::{read_volatile, write_volatile};

pub const VGA_TEXT_WIDTH: usize = 80;
pub const VGA_TEXT_HEIGHT: usize = 25;

const VGA_BASE: usize = 0xb8000; // VGA text buffer base address

const fn attr(fg: u8, bg: u8) -> u8 {
    ((bg & 0x0F) << 4) | (fg & 0x0F)
}
const fn pack_cell(ch: u8, fg: u8, bg: u8) -> u16 {
    ((attr(fg, bg) as u16) << 8) | (ch as u16)
}

#[derive(Copy, Clone)]
pub struct VgaText {
    base: usize,
}

impl VgaText {
    pub(crate) const fn new_unchecked() -> Self {
        Self { base: VGA_BASE }
    }

    pub const fn dims(&self) -> (usize, usize) {
        (VGA_TEXT_WIDTH, VGA_TEXT_HEIGHT)
    }

    pub fn put_cell(&self, row: usize, col: usize, ch: u8, fg: u8, bg: u8) {
        debug_assert!(row < VGA_TEXT_HEIGHT && col < VGA_TEXT_WIDTH);
        if row >= VGA_TEXT_HEIGHT || col >= VGA_TEXT_WIDTH {
            return;
        }
        let idx = row * VGA_TEXT_WIDTH + col;
        unsafe {
            write_volatile((self.base as *mut u16).add(idx), pack_cell(ch, fg, bg));
        }
    }

    pub fn get_cell(&self, row: usize, col: usize) -> (u8, u8, u8) {
        debug_assert!(row < VGA_TEXT_HEIGHT && col < VGA_TEXT_WIDTH);
        if row >= VGA_TEXT_HEIGHT || col >= VGA_TEXT_WIDTH {
            return (b' ', 0x7, 0x0);
        }
        let idx = row * VGA_TEXT_WIDTH + col;
        let w = unsafe { read_volatile((self.base as *mut u16).add(idx)) };
        let ch = (w & 0x00FF) as u8;
        let at = (w >> 8) as u8;
        let fg = at & 0x0F;
        let bg = (at >> 4) & 0x0F;
        (ch, fg, bg)
    }

    pub fn fill_rect(
        &self,
        row: usize,
        rows: usize,
        col: usize,
        cols: usize,
        ch: u8,
        fg: u8,
        bg: u8,
    ) {
        let (w, h) = self.dims();
        let r0 = row.min(h);
        let c0 = col.min(w);
        let r1 = (row.saturating_add(rows)).min(h);
        let c1 = (col.saturating_add(cols)).min(w);
        if r0 >= r1 || c0 >= c1 {
            return;
        }
        let val = pack_cell(ch, fg, bg);
        for r in r0..r1 {
            let base = r * w + c0;
            for i in 0..(c1 - c0) {
                unsafe { write_volatile((self.base as *mut u16).add(base + i), val) };
            }
        }
    }

    pub fn write_line_span(&self, row: usize, col: usize, bytes: &[u8], fg: u8, bg: u8) -> usize {
        let (w, h) = self.dims();
        if row >= h || col >= w || bytes.is_empty() {
            return 0;
        }
        let n = (w - col).min(bytes.len());
        let mut idx = row * w + col;
        for &b in &bytes[..n] {
            unsafe { write_volatile((self.base as *mut u16).add(idx), pack_cell(b, fg, bg)) };
            idx += 1;
        }
        n
    }

    pub fn blit_rows_up(&self, dst_row: usize, src_row: usize, rows: usize) {
        let (w, h) = self.dims();
        if rows == 0 || dst_row >= h || src_row >= h {
            return;
        }
        let rmax = rows.min(h - dst_row).min(h - src_row);
        for i in 0..rmax {
            let sr = src_row + i;
            let dr = dst_row + i;
            let sbase = sr * w;
            let dbase = dr * w;
            for x in 0..w {
                let v = unsafe { read_volatile((self.base as *mut u16).add(sbase + x)) };
                unsafe { write_volatile((self.base as *mut u16).add(dbase + x), v) };
            }
        }
    }
}
