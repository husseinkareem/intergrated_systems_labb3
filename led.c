#include "led.h"

#include <avr/io.h>

void LED_init() {
    DDRB |= (1 << PB3);  // Set PB3 as output
    DDRD |= (1 << PD6);  // Set PD6 as output
}
uint8_t simple_ramp() {
    // ...
}
