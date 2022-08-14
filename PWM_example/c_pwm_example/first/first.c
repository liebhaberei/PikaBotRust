#include <avr/io.h>

int main (void) {
    DDRB  = 0xFF;
    PORTB = 0x03;

    while(1) { }

    return 0;
}
