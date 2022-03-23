#include "led.h"

#include <avr/io.h>
#include <stdint.h>  //libary for uint8_t

void LED_init() {
    DDRD |= (1 << PD6);
}
uint8_t simple_ramp() {
    return 1;
}
