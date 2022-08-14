#![no_std]
#![no_main]

extern crate avr_std_stub;

/// The data direction register for PORT B, which is mapped to 0x24 in memory on the atmega328.
const DDRB: *mut u8 = 0x24 as *mut u8;
/// The pin status register for PORT B, which is mapped to 0x25 in memory on the atmega328.
const PORTB: *mut u8 = 0x25 as *mut u8;

#[no_mangle]
pub extern fn main() {
    unsafe {
        // Set the upper four physical pins on PORT B to inputs, the lower four to outputs.
        // The AVR interprets '1' in the data direction register as 'output', '0' input
        // for the corresponding pin.
        core::ptr::write_volatile(DDRB, core::ptr::read_volatile(DDRB) | 0b00001111);

        // Write half of the output pins as high, the other half low.
        core::ptr::write_volatile(PORTB, 0b00001010);
    }
}
