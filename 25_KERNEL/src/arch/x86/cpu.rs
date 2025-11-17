use core::arch::asm;

use crate::printk;

extern "C" {
    static stack_bottom: ();
    static stack_top: ();
}

fn stack_bounds() -> (usize, usize) {
    unsafe {
        (
            &stack_bottom as *const () as usize,
            &stack_top as *const () as usize,
        )
    }
}

pub fn read_esp() -> u32 {
    let v: u32;
    unsafe {
        core::arch::asm!("mov {}, esp", out(reg) v);
    }
    v
}

pub fn read_ebp() -> u32 {
    let v: u32;
    unsafe {
        core::arch::asm!("mov {}, ebp", out(reg) v);
    }
    v
}

pub fn reboot() -> ! {
    use crate::drivers::bus::ps2::controller;

    unsafe { asm!("cli", options(nomem, nostack, preserves_flags)); }
    controller::pulse_reset();

    loop {
        unsafe { asm!("hlt", options(nomem, nostack, preserves_flags)); }
    }
}

pub fn print_stack_info() {
    let esp = read_esp();
    let ebp = read_ebp();
    printk!("Stack:\n");
    printk!("  ESP = {:#010x}\n", esp);
    printk!("  EBP = {:#010x}\n", ebp);
}

pub fn print_stack_dump(words: usize) {
    let esp = read_esp() as usize;
    let (lo, hi) = stack_bounds();

    printk!("Stack range : [{:#010x} .. {:#010x})]\n", lo, hi);
    printk!("ESP         : {:#010x}\n", esp);

    // Abort if ESP is outside the declared stack region
    if esp < lo || esp >= hi {
        printk!("ESP is outside the stack range. Dump cancelled.\n");
        return;
    }

    // Clamp the number of words so we never read past stack_top
    let max_words = (hi - esp) / core::mem::size_of::<u32>();
    let count = words.min(max_words);

    let ptr = esp as *const u32;

    for i in 0..count {
        let addr = unsafe { ptr.add(i) } as usize;
        let val = unsafe { core::ptr::read_volatile(ptr.add(i)) };
        printk!("  {:#010x}: {:#010x}\n", addr, val);
    }

    if count < words {
        printk!("(truncated: reached top of the stack)\n");
    }
}
