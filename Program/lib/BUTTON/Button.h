#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define DEBOUNCE_MS 50
#define LONGCLICK_MS 200
#define DOUBLECLICK_MS 300

typedef struct {
    uint8_t pin;
    volatile uint8_t *pin_reg;
    volatile uint8_t *ddr_reg;
    volatile uint8_t *port_reg;
} Button;

typedef struct {
    Button *buttons;
    uint8_t buttons_num;
} Buttons_all;

volatile Buttons_all buttons_all;

void init_button(Button *button);
void Buttons_all_init(Buttons_all *buttons_all);





#endif //BUTTON_H