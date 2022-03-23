// screen -S arduino /dev/ttyACM0 38400

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "stdbool.h"

//#include "debounce.h"
#include "led.h"
#include "serial.h"
#include "timer.h"

int main() {
    // I left thease in main since they are needed on my shield to not burn it.
    DDRB &= ~(1 << PB3);  // Set PB3 as input
    DDRB &= ~(1 << PB0);  // Set PB0 as input

    DDRD &= ~(1 << PD2);  // Set PD2 as input

    LED_init();
    uart_init();
    timer2();

    int timeMs = 0;
    int then = 0;
    while (1) {
        if (bit_is_set(TIFR2, OCF2A)) {
            timeMs++;              // Global time in MS
            TIFR2 = (1 << OCF2A);  // reset the flag
        }
        if (bit_is_set(PIND, PD2)) {
            if (then == 0) {
                then = timeMs;
                printf("released\r\n");
            }
        } else if (then != 0 && (timeMs - then) > 10) {
            then = 0;
            printf("pushed\r\n");
        }
    }
}
