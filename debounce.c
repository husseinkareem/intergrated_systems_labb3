#include "debounce.h"

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "stdbool.h"
#include "timer.h"

int debounce_button() {
    if (bit_is_set(PIND, PD2)) {
        if (then == 0) {
            then = timeMs;  // update
            printf("released\r\n");
        }
    } else if (then != 0 && (timeMs - then) > 10) {  // interruption management
        then = 0;
        printf("pushed\r\n");
    }
}