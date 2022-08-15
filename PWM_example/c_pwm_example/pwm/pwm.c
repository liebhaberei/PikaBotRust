// Inspired by https://gist.github.com/Wollw/2425784

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

enum channel {
    PWM_0A, PWM_0B, PWM_1A, PWM_1B, PWM_2A, PWM_2B
};

inline void set(volatile uint8_t *reg, int8_t bit_nr) {
    *reg |= _BV(bit_nr);
}

inline void clear(volatile uint8_t *reg, int8_t bit_nr) {
    *reg &= ~(_BV(bit_nr));
}

void duty(enum channel pwm_channel, uint8_t duty) {
    switch(pwm_channel) {
        case PWM_0A:
            OCR0A = duty;
            break;
        case PWM_0B:
            OCR0B = duty;
            break;
        case PWM_1A:
            OCR1A = duty;
            break;
        case PWM_1B:
            OCR1B = duty;
            break;
        case PWM_2A:
            OCR2A = duty;
            break;
        case PWM_2B:
            OCR2A = duty;
            break;
    }
}

void max(enum channel pwm_channel) {
    switch(pwm_channel) {
        case PWM_0A:
            set(&DDRD, PD6); // OC0A as output
            set(&PORTD, PD6); // OC0A as high
            break;
        case PWM_0B:
            set(&DDRD, PD5); // OC0B as output
            set(&PORTD, PD5); // OC0A as high
            break;
        case PWM_1A:
            set(&DDRB, PB1); // OC1A as output
            set(&PORTB, PB1); // OC0A as high
            break;
        case PWM_1B:
            set(&DDRB, PB2); // OC1B as output
            set(&PORTB, PB2); // OC0A as high
            break;
        case PWM_2A:
            set(&DDRB, PB3); // OC2A as output
            set(&PORTB, PB3); // OC0A as high
            break;
        case PWM_2B:
            set(&DDRD, PD3); // OC2B as output
            set(&PORTD, PD3); // OC0A as high
            break;
    }
}

void off(enum channel pwm_channel) {
    switch(pwm_channel) {
        case PWM_0A:
            set(&DDRD, PD6); // OC0A as output
            clear(&PORTD, PD6); // OC0A as high
            break;
        case PWM_0B:
            set(&DDRD, PD5); // OC0B as output
            clear(&PORTD, PD5); // OC0A as high
            break;
        case PWM_1A:
            set(&DDRB, PB1); // OC1A as output
            clear(&PORTB, PB1); // OC0A as high
            break;
        case PWM_1B:
            set(&DDRB, PB2); // OC1B as output
            clear(&PORTB, PB2); // OC0A as high
            break;
        case PWM_2A:
            set(&DDRB, PB3); // OC2A as output
            clear(&PORTB, PB3); // OC0A as high
            break;
        case PWM_2B:
            set(&DDRD, PD3); // OC2B as output
            clear(&PORTD, PD3); // OC0A as high
            break;
    }
}

void init_pwm(enum channel pwm_channel) {
    switch(pwm_channel) {
        case PWM_0A:
            set(&DDRD, PD6); // OC0A as output
        case PWM_0B:
            if (pwm_channel == PWM_0B) {
                set(&DDRD, PD5); // OC0B as output
            }

            // WGM0x = 0b011: Fast PWM
            //                Top: 0xFF - Update of OCRx at: bottom - TOV Flag Set on: MAX
            set(&TCCR0A, WGM00);
            set(&TCCR0A, WGM01);
            clear(&TCCR0B, WGM02);
            // CS0x 0b001: clkIO, no prescaling
            set(&TCCR0B, CS00);
            clear(&TCCR0B, CS01);
            clear(&TCCR0B, CS02);
            break;
        case PWM_1A:
            break;
        case PWM_1B:
            break;
        case PWM_2A:
            break;
        case PWM_2B:
            break;
    }
}

void pwm(enum channel pwm_channel, bool enable) {
    switch(pwm_channel) {
        case PWM_0A:
            if (enable) {
                // COM0Ax = 0b10: Clear OC0A on compare match
                set(&TCCR0A, COM0A1);
                clear(&TCCR0A, COM0A0);
            } else {
                // COM0Ax = 0b00: Normal port operation, OC0A disconnected
                clear(&TCCR0A, COM0A1);
                clear(&TCCR0A, COM0A0);

                off(PWM_0A); // set pin as output and value to 0
            }
            break;
        case PWM_0B:
            if (enable) {
                // COM0Bx = 0b10: Clear OC0B on compare match
                set(&TCCR0A, COM0B1);
                clear(&TCCR0A, COM0B0);
            } else {
                // COM0Bx = 0b00: Normal port operation, OC0B disconnected
                clear(&TCCR0A, COM0B1);
                clear(&TCCR0A, COM0B0);

                off(PWM_0B); // set pin as output and value to 0
            }
            break;
        case PWM_1A:
            break;
        case PWM_1B:
            break;
        case PWM_2A:
            break;
        case PWM_2B:
            break;
    }
}

int main (void) {
    init_pwm(PWM_0A);

    for(;;) {
        max(PWM_1A);

        pwm(PWM_0A, false);
		
        _delay_ms(1000);

        pwm(PWM_0A, true); // enable PWM channel
        duty(PWM_0A, 20); // set duty to 20 of 255

        off(PWM_1A);

        _delay_ms(1000);
	}

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