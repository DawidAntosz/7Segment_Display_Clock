#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>

#include "MAX7219.h"

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;


int main(void)
{
    MAX7219_init();


    while(1)
    {
        if(second > 59){
            second =0;
            minute +=1;
        }
        if(minute > 59){
            minute =0;
            hour += 1;
        }
        if(hour > 23){
            hour = 0;
            second = 0;
            minute = 0;
        }
        second++;
        _delay_ms(100);

        MAX7219_displayClock(&hour, &minute, &second);
        
    }
}