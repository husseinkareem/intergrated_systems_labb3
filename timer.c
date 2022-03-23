#include "timer.h"

#include <avr/io.h>
int timeMs = 0;
int then = 0;

void timer0() {
    // Fast PWM-mod, 0xFF som TOP. Table 19-4.
    TCCR0A &= ~(1 << COM0A0);  // 19-17.
    TCCR0A |= (1 << COM0A1);

    TCCR0A |= (1 << WGM00);   // WGM00 -> 1
    TCCR0A |= (1 << WGM01);   // WGM01 -> 1
    TCCR0B &= ~(1 << WGM02);  // WGM02 -> 0
    // Prescaler = 64 Table 15-9.
    TCCR0B |= (1 << CS00);   // CS00 -> 1
    TCCR0B |= (1 << CS01);   // CS01 -> 1
    TCCR0B &= ~(1 << CS02);  // CS02 -> 0
}
void timer2() {
    // Timer mode with 1024 prescaler
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS21);
    TCCR2B |= (1 << CS22);

    // CTC table 22-9.
    TCCR2A &= (1 << WGM20);
    TCCR2A |= (1 << WGM21);
    TCCR2B &= ~(1 << WGM22);

    // 1 1 Set OC2A on compare match
    TCCR2A &= ~(1 << COM2A0);
    TCCR2A |= (1 << COM2A1);

    OCR2A = 156;  // Set top counter to 16000000/1024*0.01 -1 since it starts at index 0, to get ~1ms

    TIMSK2 |= (1 << OCIE2A);
}
