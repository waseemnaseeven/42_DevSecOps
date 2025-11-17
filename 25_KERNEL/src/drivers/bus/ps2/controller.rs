use crate::arch::x86::io::ports::{KBD_CMD, KBD_DATA, KBD_STAT};

/// Status flag: Output Buffer Full (data available to read).
/// Set when the controller has data ready in the data port.
const STAT_OBF: u8 = 1 << 0;

/// Status flag: Input Buffer Full (controller busy).
/// Set when the controller is still processing the last command/data write.
const STAT_IBF: u8 = 1 << 1;

fn status() -> u8 {
    KBD_STAT.read()
}

pub fn data_available() -> bool {
    status() & STAT_OBF != 0
}

pub fn try_read_data() -> Option<u8> {
    if data_available() {
        Some(KBD_DATA.read())
    } else {
        None
    }
}

fn wait_input_idle() {
    while KBD_STAT.read() & STAT_IBF != 0 {}
}

fn flush_output_buffer() {
    while KBD_STAT.read() & STAT_OBF != 0 {
        let _ = KBD_DATA.read();
    }
}

pub fn pulse_reset() {
    wait_input_idle();
    flush_output_buffer();
    let mut cmd = KBD_CMD;
    cmd.write(0xFE); // 8042 pulse CPU reset line
}
