// För att kompilera skriv i terminalen -> make && screen -S arduino /dev/ttyACM0 38400
// Tryck på knappen på din shöld.

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "debounce.h"
#include "led.h"
#include "serial.h"
#include "stdbool.h"
#include "timer.h"

int main() {
    // I left thease in main since they are needed on my shield to not burn it.
    DDRB &= ~(1 << PB3);  // Set PB3 as input
    DDRB &= ~(1 << PB0);  // Set PB0 as input

    DDRD &= ~(1 << PD2);  // Set PD2 as input

    LED_init();
    uart_init();
    timer2();

    while (1) {
        debounce_button();

        if (bit_is_set(TIFR2, OCF2A)) {  // millis
            timeMs++;                    // Global time in MS
            TIFR2 = (1 << OCF2A);        // reset the flag
        }
    }
}