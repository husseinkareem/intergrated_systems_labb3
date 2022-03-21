#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

void main(void) {
    // I left thease in main since they are needed on my shield to not burn blabla
    DDRB &= ~(1 << PB3);  // Set PB3 as output
    DDRB &= ~(1 << PB0);  // Set PB0 as input

    LED_init();
    uart_init();
    timer_init();

    // while (1) {
    // }
}
