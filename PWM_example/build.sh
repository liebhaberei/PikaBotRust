#!/bin/zsh

rustup override set nightly
export AVR_CPU_FREQUENCY_HZ=16000000
cargo build -Z build-std=core --target atmega328p.json --release

avrdude -patmega328p -carduino -P/dev/ttyUSB0 -b115200 -D -Uflash:w:target/atmega328p/release/pwm_example.elf:e
