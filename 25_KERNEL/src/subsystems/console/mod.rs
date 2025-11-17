pub mod color;

pub trait Console {
    fn clear_screen(&mut self);
    fn set_color(&mut self, fg: u8, bg: u8);
    fn write_byte(&mut self, b: u8);

    fn write_bytes(&mut self, bytes: &[u8]) {
        for &b in bytes {
            self.write_byte(b);
        }
    }

    fn backspace(&mut self);

    fn write_str(&mut self, s: &str) {
        for byte in s.bytes() {
            match byte {
                0x20..=0x7e | b'\n' => self.write_byte(byte),
                _ => self.write_byte(0xfe), // ▮
            }
        }
    }
}

use crate::drivers::vga::crtc;
pub use crate::drivers::vga::text as vga;

use crate::drivers::vga::text::{VgaText, VGA_TEXT_HEIGHT, VGA_TEXT_WIDTH};

pub struct VgaConsole {
    vga: VgaText,
    fg: u8,
    bg: u8,
    row: usize,
    col: usize,
}

impl VgaConsole {
    pub const fn new() -> Self {
        Self {
            vga: VgaText::new_unchecked(),
            fg: 0x07,
            bg: 0x00,
            row: 0,
            col: 0,
        }
    }

    fn newline(&mut self) {
        self.col = 0;
        if self.row + 1 >= VGA_TEXT_HEIGHT {
            self.vga.blit_rows_up(0, 1, VGA_TEXT_HEIGHT - 1);
            self.vga.fill_rect(
                VGA_TEXT_HEIGHT - 1,
                1,
                0,
                VGA_TEXT_WIDTH,
                b' ',
                self.fg,
                self.bg,
            );
        } else {
            self.row += 1;
        }
        self.sync_hw_cursor();
    }

    fn sync_hw_cursor(&self) {
        let r = self.row.min(VGA_TEXT_HEIGHT - 1);
        let c = self.col.min(VGA_TEXT_WIDTH - 1);
        crtc::set_cursor_rc(r, c);
    }
}

impl Console for VgaConsole {
    fn clear_screen(&mut self) {
        self.vga.fill_rect(
            0,
            VGA_TEXT_HEIGHT,
            0,
            VGA_TEXT_WIDTH,
            b' ',
            self.fg,
            self.bg,
        );
        self.row = 0;
        self.col = 0;
        self.sync_hw_cursor();
    }

    fn set_color(&mut self, fg: u8, bg: u8) {
        self.fg = fg & 0x0F;
        self.bg = bg & 0x0F;
    }

    fn write_byte(&mut self, b: u8) {
        match b {
            b'\n' => {
                self.newline();
            }
            _ => {
                if self.col >= VGA_TEXT_WIDTH {
                    self.newline();
                }
                self.vga.put_cell(self.row, self.col, b, self.fg, self.bg);
                self.col += 1;
                self.sync_hw_cursor();
            }
        }
    }

    fn write_bytes(&mut self, bytes: &[u8]) {
        for &b in bytes {
            self.write_byte(b);
        }
    }

    fn backspace(&mut self) {
        if self.col > 0 {
            self.col -= 1;
        } else if self.row > 0 {
            self.row -= 1;
            self.col = VGA_TEXT_WIDTH - 1;
        } else {
            return;
        }
        self.sync_hw_cursor();
        self.vga
            .put_cell(self.row, self.col, b' ', self.fg, self.bg);
    }
}
