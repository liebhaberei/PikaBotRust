# PikaBotRust

Rust implementation if PikaBot booklet projects.

## Dependencies

- [Ruduino](https://github.com/avr-rust/ruduino)

## Project 1

Basic moving of PikaBot.

### Project 1.1

#### Prepare crate

- Create crate
	- `cargo new --bin PikaBotProject1-1`
	- `rustup override set nightly`

- Target json: 
``` json
{
    "arch": "avr",
    "cpu": "atmega328p",
    "data-layout": "e-P1-p:16:8-i8:8-i16:8-i32:8-i64:8-f32:8-f64:8-n8-a:8",
    "env": "",
    "executables": true,
    "linker": "avr-gcc",
    "linker-flavor": "gcc",
    "linker-is-gnu": true,
    "llvm-target": "avr-unknown-unknown",
    "os": "unknown",
    "position-independent-executables": false,
    "exe-suffix": ".elf",
    "eh-frame-header": false,
    "pre-link-args": {
        "gcc": ["-mmcu=atmega328p"]
    },
    "late-link-args": {
        "gcc": ["-lgcc", "-lc"]
    },
    "target-c-int-width": "16",
    "target-endian": "little",
    "target-pointer-width": "16",
    "vendor": "unknown"
}
```

- Cargo.toml
``` shell
[dependencies]
ruduino = {  git = "https://github.com/avr-rust/ruduino", branch = "master" }
```

- build.sh
``` shell
#!/bin/zsh

rustup override set nightly
export AVR_CPU_FREQUENCY_HZ=16000000
cargo build -Z build-std=core --target atmega328p.json --release
```

- main.rs blink example
``` rust
#![no_std]
#![no_main]

use ruduino::Pin;
use ruduino::cores::current::{port};

fn init_pins() {

}

#[no_mangle]
pub extern fn main() {
    port::B5::set_output();

    loop {
        port::B5::set_high();

        ruduino::delay::delay_ms(1000);

        port::B5::set_low();

        ruduino::delay::delay_ms(1000);
    }
}
```

- build: `.\build.sh`
- flash: `avrdude -patmega328p -carduino -P/dev/ttyUSB0 -b115200 -D -Uflash:w:target/atmega328p/release/PikaBotProject1-1.elf:e`


####  Implementation

- [ ] implement analogWrite using Rust/ruduino(?)
- [ ] implement Cytron Motor Driver (trivial with analogWrite), see [git](https://github.com/CytronTechnologies/CytronMotorDriver/blob/master/CytronMotorDriver.cpp)


