#![no_std]
#![no_main]

use ruduino::Pin;
use ruduino::cores::current::{port};

#[no_mangle]
pub extern fn main() {
    port::B3::set_output();
    port::B2::set_output();

    port::B3::set_high();
    port::B2::set_low();

    loop {
        port::B3::set_high();
        ruduino::delay::delay_ms(1000);

        port::B3::set_low();
        ruduino::delay::delay_ms(1000);
    }
}
