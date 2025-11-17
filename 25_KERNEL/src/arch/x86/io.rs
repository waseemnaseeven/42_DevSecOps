//------------------------------------------------------------------------------
// Assumption: Direction Flag (DF) = 0
//------------------------------------------------------------------------------
// All REP string I/O instructions (INSx/OUTSx) used here assume DF = 0,
// meaning destination/source pointers (RDI/RSI or EDI/ESI) increment
// after each iteration. This is guaranteed by the System V ABI, which
// requires DF to be cleared (forward direction) on all function entry.
//------------------------------------------------------------------------------

#[cfg(not(any(target_arch = "x86", target_arch = "x86_64")))]
compile_error!("This module requires x86/x86_64 (uses IN/OUT port-mapped I/O).");

use core::arch::asm;
use core::marker::PhantomData;

mod sealed {
    pub trait Sealed {}
}
use sealed::Sealed;

pub enum U8Width {}
impl Sealed for U8Width {}
pub enum U16Width {}
impl Sealed for U16Width {}
pub enum U32Width {}
impl Sealed for U32Width {}

pub enum RdOnly {}
impl Sealed for RdOnly {}
pub enum WrOnly {}
impl Sealed for WrOnly {}
pub enum RdWr {}
impl Sealed for RdWr {}

pub trait IoWidth: Sealed {
    type Value;

    unsafe fn in_port(port: u16) -> Self::Value;

    unsafe fn out_port(port: u16, value: Self::Value);

    unsafe fn ins_port(port: u16, dst: *mut Self::Value, count: usize);

    unsafe fn outs_port(port: u16, src: *const Self::Value, count: usize);
}

impl IoWidth for U8Width {
    type Value = u8;

    unsafe fn in_port(port: u16) -> u8 {
        let v: u8;
        asm!(
            "in al, dx",
            in("dx") port,
            out("al") v,
            options(nostack, preserves_flags)
        );
        v
    }

    unsafe fn out_port(port: u16, value: u8) {
        asm!(
            "out dx, al",
            in("dx") port,
            in("al") value,
            options(nostack, preserves_flags)
        );
    }

    unsafe fn ins_port(port: u16, dst: *mut u8, count: usize) {
        asm!(
            "rep insb",
            in("dx") port,
            inout("rdi") dst => _,
            inout("rcx") count => _,
            options(nostack, preserves_flags)
        );
    }

    #[cfg(target_arch = "x86_64")]
    unsafe fn outs_port(port: u16, src: *const u8, count: usize) {
        asm!(
            "rep outsb",
            in("dx") port,
            inout("rsi") src => _,
            inout("rcx") count => _,
            options(nostack, preserves_flags)
        );
    }

    // rsi is used by LLVM in x86
    #[cfg(target_arch = "x86")]
    unsafe fn outs_port(port: u16, src: *const u8, count: usize) {
        for i in 0..count {
            let byte = *src.add(i);
            asm!(
                "out dx, al",
                in("dx") port,
                in("al") byte,
                options(nostack, preserves_flags),
            );
        }
    }
}

impl IoWidth for U16Width {
    type Value = u16;

    unsafe fn in_port(port: u16) -> u16 {
        let v: u16;
        asm!(
            "in ax, dx",
            in("dx") port,
            out("ax") v,
            options(nostack, preserves_flags)
        );
        v
    }

    unsafe fn out_port(port: u16, value: u16) {
        asm!(
            "out dx, ax",
            in("dx") port,
            in("ax") value,
            options(nostack, preserves_flags)
        );
    }

    unsafe fn ins_port(port: u16, dst: *mut u16, count: usize) {
        asm!(
            "rep insw",
            in("dx") port,
            inout("rdi") dst => _,
            inout("rcx") count => _,
            options(nostack, preserves_flags)
        );
    }

    #[cfg(target_arch = "x86_64")]
    unsafe fn outs_port(port: u16, src: *const u16, count: usize) {
        asm!(
            "rep outsw",
            in("dx") port,
            inout("rsi") src => _,
            inout("rcx") count => _,
            options(nostack, preserves_flags)
        );
    }

    #[cfg(target_arch = "x86")]
    unsafe fn outs_port(port: u16, src: *const u16, count: usize) {
        for i in 0..count {
            let word = *src.add(i);
            asm!(
                "out dx, ax",
                in("dx") port,
                in("ax") word,
                options(nostack, preserves_flags),
            );
        }
    }
}

impl IoWidth for U32Width {
    type Value = u32;

    unsafe fn in_port(port: u16) -> u32 {
        let v: u32;
        asm!(
            "in eax, dx",
            in("dx") port,
            out("eax") v,
            options(nostack, preserves_flags)
        );
        v
    }

    unsafe fn out_port(port: u16, value: u32) {
        asm!(
            "out dx, eax",
            in("dx") port,
            in("eax") value,
            options(nostack, preserves_flags)
        );
    }

    unsafe fn ins_port(port: u16, dst: *mut u32, count: usize) {
        asm!(
            "rep insd",
            in("dx") port,
            inout("rdi") dst => _,
            inout("rcx") count => _,
            options(nostack, preserves_flags)
        );
    }

    #[cfg(target_arch = "x86_64")]
    unsafe fn outs_port(port: u16, src: *const u32, count: usize) {
        asm!(
            "rep outsd",
            in("dx") port,
            inout("rsi") src => _,
            inout("rcx") count => _,
            options(nostack, preserves_flags)
        );
    }

    #[cfg(target_arch = "x86")]
    unsafe fn outs_port(port: u16, src: *const u32, count: usize) {
        for i in 0..count {
            let word = *src.add(i);
            asm!(
                "out dx, eax",
                in("dx") port,
                in("ax") word,
                options(nostack, preserves_flags),
            );
        }
    }
}

#[repr(transparent)]
pub struct Port<W: IoWidth, A: Sealed = RdWr> {
    port: u16,
    _w: PhantomData<W>,
    _a: PhantomData<A>,
}

impl<W: IoWidth, A: Sealed> Copy for Port<W, A> {}
impl<W: IoWidth, A: Sealed> Clone for Port<W, A> {
    fn clone(&self) -> Self {
        *self
    }
}

impl<W: IoWidth, A: Sealed> Port<W, A> {
    pub const unsafe fn new(port: u16) -> Self {
        Self {
            port,
            _w: PhantomData,
            _a: PhantomData,
        }
    }

    pub const fn addr(&self) -> u16 {
        self.port
    }
}

impl<W: IoWidth> Port<W, RdOnly> {
    pub fn read(&self) -> W::Value {
        unsafe { W::in_port(self.port) }
    }

    pub fn read_buf(&self, dst: &mut [W::Value]) {
        unsafe { W::ins_port(self.port, dst.as_mut_ptr(), dst.len()) }
    }
}

impl<W: IoWidth> Port<W, WrOnly> {
    pub fn write(&mut self, v: W::Value) {
        unsafe { W::out_port(self.port, v) }
    }

    pub fn write_buf(&mut self, src: &[W::Value]) {
        unsafe { W::outs_port(self.port, src.as_ptr(), src.len()) }
    }
}

impl<W: IoWidth> Port<W, RdWr> {
    pub fn read(&self) -> W::Value {
        unsafe { W::in_port(self.port) }
    }

    pub fn write(&mut self, v: W::Value) {
        unsafe { W::out_port(self.port, v) }
    }

    pub fn read_buf(&self, dst: &mut [W::Value]) {
        unsafe { W::ins_port(self.port, dst.as_mut_ptr(), dst.len()) }
    }

    pub fn write_buf(&mut self, src: &[W::Value]) {
        unsafe { W::outs_port(self.port, src.as_ptr(), src.len()) }
    }
}

#[macro_export]
macro_rules! const_port {
    ($name:ident, $width:ty, $acc:ty, $addr:expr) => {
        pub const $name: Port<$width, $acc> = unsafe { Port::new($addr) };
    };
}

pub mod ports {
    use super::*;

    const_port!(KBD_DATA, U8Width, RdOnly, 0x60);
    const_port!(KBD_STAT, U8Width, RdOnly, 0x64);
    const_port!(KBD_CMD, U8Width, WrOnly, 0x64);
    const_port!(VGA_CRTC_ADDR, U8Width, WrOnly, 0x3D4);
    const_port!(VGA_CRTC_DATA, U8Width, RdWr, 0x3D5);
}
