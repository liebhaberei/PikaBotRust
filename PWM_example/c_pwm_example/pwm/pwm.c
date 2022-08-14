// Inspired by https://gist.github.com/Wollw/2425784

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>




int main (void) {
	// all PWM pins as output
    DDRB |= _BV(PB1); // OC1A
    DDRB |= _BV(PB2); // OC1B
    DDRB |= _BV(PB3); // OC2A
    DDRD |= _BV(PD3); // OC2B
    DDRD |= _BV(PD5); // OC0B
    DDRD |= _BV(PD6); // OC0A

    /*
     * PikaBot
     * Motor 1 (left):  OC2A: forward, OC1B: backward
     * Motor 2 (right): OC1A: forward, OC2B: backward
     */

	// COM1Ax = 0b10: Clear OC1A on compare match
    // COM1Bx = 0b10: Clear OC1B on compare match
    // WGM1x = 0b0001: PWM, phase correct, 8-bit
    //                Top: 0x00FF - Update of OCR1x at: TOP - TOV1 Flag Set on: BOTTOM
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
    // (WGM12 = 0, WGM12 = 0)
    // CS1x 0b001: clkIO, no prescaling
	TCCR1B = _BV(CS10);

    // Asynchronous Status Register
    // AS2 = 0: When AS2 is written to zero, Timer/Counter2 is clocked from the I/O clock
    ASSR = 0x00;
    // COM2Ax = 0b10: Clear OC2A on compare match
    // COM2Bx = 0b10: Clear OC2B on compare match
    // WGM2x = 0b011: Fast PWM
    //                Top: 0xFF - Update of OCRx at: BOTTOM - TOV Flag Set on: MAX
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20)| _BV(WGM21);
    // (WGM22 = 0)
    // CS2x 0b001: clkT2S, no prescaling
	TCCR2B = _BV(CS20);

    // TCCR0A |= _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
	// TCCR0B |= _BV(CS00);

	uint8_t pwm = 0x00;
	bool up = true;
	for(;;) {
        OCR0A = 0;
        OCR0B = 0;

		OCR1A = pwm;
        OCR1B = pwm;

        OCR2A = 0;
        OCR2B = 0;

		pwm += up ? 1 : -1;
		if (pwm == 0xff)
			up = false;
		else if (pwm == 0x00)
			up = true;

		_delay_ms(10);
	}

}