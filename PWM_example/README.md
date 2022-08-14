# AVR Rust PWM example

## AVR basics

- [Makefile for Arduino UNO](https://de.wikibooks.org/wiki/C-Programmierung_mit_AVR-GCC/_Makefile)

### Learn the Basics of I/O Pins for an AVR Microcontroller

- [Learn the Basics of I/O Pins for an AVR Microcontroller](https://maker.pro/custom/tutorial/learn-the-basics-of-io-pins-for-an-avr-microcontroller)

#### Data Direction Register (DDR)

- 8-bit register that defines if a pin is input or output
- 1 is output, 0 is input
	- Example: Port B all output: `DDRB = 0xFF` (`DDRB = 0b11111111`)

#### PINx Register

- read digital values from pins configured as input

#### PORTx Register

- set digital values for output pins

### AVR GCC tutorial

- [AVR-GCC-Tutorial](https://www.mikrocontroller.net/articles/AVR-GCC-Tutorial)

## AVR PWM

- [Mikrocontroller AVR PWM](https://www.mikrocontroller.net/articles/AVR_PWM)
- [Mikrocontroller AVR PWM Tutorial](https://www.mikrocontroller.net/articles/AVR-Tutorial:_PWM)
- [PWM Signal Generation by Using AVR Timers. Part II](https://extremeelectronics.co.in/avr-tutorials/pwm-signal-generation-by-using-avr-timers-part-ii/)




