#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/pgmspace.h>

#include "Menu.h"
#include "Button.h"
#include "MAX7219.h"
#include "ds1307.h"

#define BUZZER PB1

uint8_t year = 0;
uint8_t month = 0;
uint8_t day = 0;
uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;

volatile uint8_t numberButton = 0;

void displayClock(void);
void setTime(void);


int main(void)
{
    MAX7219_init();
    DS1307_init();
    
    MenuItem menuItems[] = {
            {"Czas", (void *) displayClock},
            {"Ustaw czas", (void *) setTime}
    };
    int numItems = sizeof(menuItems)/ sizeof(menuItems[0]);
    Menu *menu = createMenu("Menu glowne", numItems, menuItems);

    while(1)
    {
        switch (numberButton)
        {
        case 1:
            selectMenuItem(menu,0);
            break;
        case 2:
            selectMenuItem(menu,0);
            break;
        default:
            break;
        }
        _delay_ms(10);
    }
}

void displayClock(void){
    DS1307_getdate(&year, &month, &day, &hour, &minute, &second);
    MAX7219_displayClock(&hour, &minute, &second);
}

void setTime(void){
    DS1307_setdate(23, 2, 23, 6, 5, 40);
}