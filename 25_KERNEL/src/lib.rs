#![no_std]
#![no_main]

use core::panic::PanicInfo;

pub mod arch;
pub mod drivers;
pub mod subsystems;
pub mod sync;

use crate::arch::x86::gdt;

#[derive(Copy, Clone)]
struct BootArgs {
    magic: u32,
    mbi_addr: u32,
}

static mut BOOT_ARGS: BootArgs = BootArgs {
    magic: 0,
    mbi_addr: 0,
};

#[no_mangle]
pub extern "C" fn _start_kernel(magic: u32, mbi_addr: u32) -> ! {
    unsafe {
        BOOT_ARGS = BootArgs { magic, mbi_addr };
    }
    gdt::init_with_entry(kernel_entry_post_gdt)
}

extern "C" fn kernel_entry_post_gdt() -> ! {
    let args = unsafe { BOOT_ARGS };
    kernel_main(args.magic, args.mbi_addr)
}

fn kernel_main(magic: u32, mbi_addr: u32) -> ! {
    printk!("kfs: boot magic={:#x} mbi={:#x}\n", magic, mbi_addr);
    printk!("42\n");
    printk!("> ");

    let mut editor = subsystems::shell::LineEditor::new();

    loop {
        if let Some(ev) = drivers::input::keyboard::poll_event() {
            subsystems::shell::handle_key_event(&mut editor, ev);
        }
    }
}

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    printk!("PANIC: {info}");
    loop {}
}

#[no_mangle]
pub unsafe extern "C" fn memcmp(s1: *const u8, s2: *const u8, n: usize) -> i32 {
    for i in 0..n {
        let a = core::ptr::read(s1.add(i));
        let b = core::ptr::read(s2.add(i));
        if a != b {
            return (a as i32) - (b as i32);
        }
    }
    0
}
