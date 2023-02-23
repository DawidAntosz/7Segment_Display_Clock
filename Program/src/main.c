#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>

#include "MAX7219.h"
#include "ds1307.h"


int main(void)
{
    MAX7219_init();
    DS1307_init();
    
    uint8_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;

    DS1307_setdate(23, 2, 23, 6, 5, 40);

    while(1)
    {
        DS1307_getdate(&year, &month, &day, &hour, &minute, &second);

        MAX7219_displayClock(&hour, &minute, &second);

        _delay_ms(10);
    }
}