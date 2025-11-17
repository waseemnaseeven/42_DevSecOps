use crate::arch::x86::io::ports::{VGA_CRTC_ADDR, VGA_CRTC_DATA};

pub fn set_cursor_pos(linear_pos: u16) {
    let mut idx = VGA_CRTC_ADDR;
    let mut data = VGA_CRTC_DATA;
    idx.write(0x0F);
    data.write((linear_pos & 0xFF) as u8);
    idx.write(0x0E);
    data.write((linear_pos >> 8) as u8);
}

pub fn set_cursor_rc(row: usize, col: usize) {
    let pos = (row * 80 + col) as u16;
    set_cursor_pos(pos);
}

pub fn enable_cursor(scan_start: u8, scan_end: u8) {
    let mut idx = VGA_CRTC_ADDR;
    let mut data = VGA_CRTC_DATA;

    idx.write(0x0A);
    let mut v = data.read();
    v = (v & 0xC0) | (scan_start & 0x1F);
    data.write(v & !0x20);

    idx.write(0x0B);
    let mut ve = data.read();
    ve = (ve & !0x1F) | (scan_end & 0x1F);
    data.write(ve);
}

pub fn disable_cursor() {
    let mut idx = VGA_CRTC_ADDR;
    let mut data = VGA_CRTC_DATA;
    idx.write(0x0A);
    let mut v = data.read();
    v |= 0x20;
    data.write(v);
}
