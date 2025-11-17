use crate::drivers::input::keyboard::types::{KeyCode, KeyEvent};
use crate::printk;
use crate::subsystems::logging::{
    console_backspace, console_clear, console_set_color, console_write_byte,
};

pub struct LineEditor {
    buf: [u8; 80],
    len: usize,
}

impl LineEditor {
    pub const fn new() -> Self {
        Self {
            buf: [0; 80],
            len: 0,
        }
    }

    fn push_byte(&mut self, b: u8) {
        if self.len < self.buf.len() {
            self.buf[self.len] = b;
            self.len += 1;
            console_write_byte(b);
        }
    }

    fn backspace(&mut self) {
        if self.len > 0 {
            self.len -= 1;
            console_backspace();
        }
    }

    fn submit(&mut self) {
        console_write_byte(b'\n');
        let line = core::str::from_utf8(&self.buf[..self.len]).unwrap_or("");
        handle_command(line.trim());
        self.len = 0;
        printk!("> ");
    }
}

pub fn handle_key_event(ed: &mut LineEditor, ev: KeyEvent) {
    if !ev.pressed {
        return;
    }

    match ev.code {
        KeyCode::Char(b) => {
            ed.push_byte(b);
        }
        KeyCode::Backspace => {
            ed.backspace();
        }
        KeyCode::Enter => {
            ed.submit();
        }
        KeyCode::Tab => {
            // ignore
        }
        KeyCode::Unknown(_) => {}
    }
}

fn handle_command(cmd: &str) {
    if cmd.is_empty() {
        return;
    }

    match cmd {
        "clear" | "cls" => {
            console_clear();
        }
        _ if cmd.starts_with("echo ") => {
            let text = &cmd[5..];
            printk!("{}\n", text);
        }
        _ if cmd.starts_with("stack") => {
            let n = cmd
                .strip_prefix("stack")
                .and_then(|s| s.trim().parse::<usize>().ok())
                .unwrap_or(16);

            crate::arch::x86::cpu::print_stack_dump(n);
        }
        _ if cmd.starts_with("color ") => {
            set_color_cmd(&cmd[6..]);
        }
        "reboot" => {
            printk!("Rebooting...\n");
            crate::arch::x86::cpu::reboot();
        }
        _ => {
            printk!("Unknown command: {}\n", cmd);
        }
    }
}

fn set_color_cmd(args: &str) {
    let mut it = args.split_whitespace();
    let fg = it.next();
    let bg = it.next().unwrap_or("black");

    let fg_code = parse_color(fg.unwrap_or("white"));
    let bg_code = parse_color(bg);

    console_set_color(fg_code, bg_code);
}

fn parse_color(name: &str) -> u8 {
    use crate::subsystems::console::color::color::*;
    match name {
        "black" => BLACK,
        "blue" => BLUE,
        "green" => GREEN,
        "cyan" => CYAN,
        "red" => RED,
        "magenta" => MAGENTA,
        "brown" => BROWN,
        "grey" | "gray" => LIGHT_GREY,
        "darkgrey" | "darkgray" => DARK_GREY,
        "lightblue" => LIGHT_BLUE,
        "lightgreen" => LIGHT_GREEN,
        "lightcyan" => LIGHT_CYAN,
        "lightred" => LIGHT_RED,
        "lightmagenta" => LIGHT_MAGENTA,
        "yellow" => YELLOW,
        "white" => WHITE,
        _ => LIGHT_GREY,
    }
}
