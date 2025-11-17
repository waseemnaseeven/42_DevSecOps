use core::fmt;

use crate::sync::spinlock::SpinLock;

use crate::subsystems::console::Console;
use crate::subsystems::console::VgaConsole;

static CONSOLE: SpinLock<VgaConsole> = SpinLock::new(VgaConsole::new());

fn with_console<F: FnOnce(&mut dyn Console)>(f: F) {
    let mut guard = CONSOLE.lock();
    f(&mut *guard);
}

pub fn printk_fmt(args: fmt::Arguments) {
    with_console(|c| {
        use core::fmt::Write;

        struct Adaptor<'a>(&'a mut dyn Console);
        impl<'a> fmt::Write for Adaptor<'a> {
            fn write_str(&mut self, s: &str) -> fmt::Result {
                self.0.write_str(s);
                Ok(())
            }
        }

        let _ = Adaptor(c).write_fmt(args);
    });
}

#[macro_export]
macro_rules! printk {
    ($($arg:tt)*) => {
        $crate::subsystems::logging::printk_fmt(format_args!($($arg)*))
    };
}

pub fn console_clear() {
    with_console(|c| c.clear_screen());
}

pub fn console_set_color(fg: u8, bg: u8) {
    with_console(|c| c.set_color(fg, bg));
}

pub fn console_write_byte(b: u8) {
    with_console(|c| c.write_byte(b));
}

pub fn console_backspace() {
    with_console(|c| c.backspace());
}
