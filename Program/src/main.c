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
#include "uart.h"

#define B1_PIN PD5
#define B2_PIN PD6
#define B3_PIN PD7
#define B4_PIN PB0

#define BUZZER PB1

uint8_t year = 0;
uint8_t month = 0;
uint8_t day = 0;
uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;

uint8_t year_SET = 0;
uint8_t month_SET = 0;
uint8_t day_SET = 0;
uint8_t hour_SET = 0;
uint8_t minute_SET = 0;
uint8_t second_SET = 0;

uint8_t hour_SET_pom = 0;
uint8_t minute_SET_pom = 0;
uint8_t second_SET_pom = 0;

uint8_t flag_OK;
uint8_t flag_BACK;

void displayClock(void);
void setTime(void);
void Pomodoro(void);
void displayCear2(void);

volatile uint8_t number_menu = 1;

int main(void)
{
    MAX7219_init();
    DS1307_init();
    uart_init();

    Button button_table[4] = {
        {B1_PIN, &PIND, &DDRD, &PORTD}, // przyciosk inkrementacji wartości "+1"
        {B2_PIN, &PIND, &DDRD, &PORTD}, // przycisk dekrementacji wartosći "-1"
        {B3_PIN, &PIND, &DDRD, &PORTD}, // przycisk zatwierdzenia opcji "ok"
        {B4_PIN, &PINB, &DDRB, &PORTB}  // przycisk powrotu z opcji "back"
    };

    MenuItem menuItems[] = {
            {"Czas", (void *) displayClock},
            {"Ustaw czas", (void *) displayCear2},
            {"Clear display", (void *) Pomodoro},
    };

    int numItems = sizeof(menuItems)/ sizeof(menuItems[0]);

    Menu *menu = createMenu("Menu glowne", numItems, menuItems);

    Buttons_all buttons_all = {
        .buttons = button_table,
        .buttons_quantity = 4,
        .Temp = &number_menu,
        .limit = &numItems,
        .flag_OK = &flag_OK,
        .flag_BACK = &flag_BACK
    };

    Buttons_all_init(&buttons_all);

    while(1)
    {
        selectMenuItem(menu,number_menu);
        
        _delay_ms(10);
    }

    return 0;
}

void displayClock(void){
    DS1307_getdate(&year, &month, &day, &hour, &minute, &second);
    MAX7219_displayClock(&hour, &minute, &second);
}
void Pomodoro(void){

    uint8_t h = 0;
    uint8_t m = 25;
    uint8_t s = 0;

    DS1307_getdate(&year, &month, &day, &hour, &minute, &second);
    

    MAX7219_displayClock(&h, &m, &s);
}



void displayCear2(void){
    uint8_t h = 0;
    uint8_t m = 0;
    uint8_t s = 3;
    MAX7219_displayClock(&h, &m, &s);
}

void setTime(void){
    DS1307_setdate(23, 2, 23, 6, 5, 40);
}