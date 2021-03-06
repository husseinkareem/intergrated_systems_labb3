// Labb 3 Del 3...För att kompilera skriv i terminalen -> make && screen -S arduino /dev/ttyACM0 38400
// Höj och sänk ljusstyrkan.

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "debounce.h"
#include "led.h"
#include "serial.h"
#include "stdbool.h"
#include "timer.h"

volatile uint8_t adc_value = 0;
ISR(ADC_vect) {
    adc_value = ADCH;
}
ISR(TIMER2_COMPA_vect) {
    ADCSRA |= (1 << ADSC);  // start adc
    OCR0A = adc_value;
}
int main() {
    // I left thease in main since they are needed on my shield to not burn it.
    DDRB &= ~(1 << PB3);  // Set PB3 as input
    DDRB &= ~(1 << PB0);  // Set PB0 as input

    DDRD &= ~(1 << PD2);  // Set PD2 as input

    LED_init();
    uart_init();
    timer2();
    timer0();

    // ADC
    DDRC &= ~(1 << PC0);
    ADMUX |= (1 << ADLAR) | (1 << REFS0);
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1);
    ADCSRA |= (1 << ADEN) | (1 << ADIE);

    sei();

    while (1) {
        debounce_button();
        if (bit_is_set(TIFR2, OCF2A)) {  // millis
            timeMs++;                    // Global time in MS
            TIFR2 = (1 << OCF2A);        // reset the flag
        }
    }
}