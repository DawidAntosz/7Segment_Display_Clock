#include "Button.h"

volatile Buttons_all buttons_all;

void init_button(Button *button) {
    *button->ddr_reg &= ~(1 << button->pin); //pin jako wejście
    *button->port_reg |= (1 << button->pin); //pull-up
    button->press_duration = 0;
    button->state = 0;
}

void Buttons_all_init(Buttons_all *buttons_all_ptr) {
    buttons_all = *buttons_all_ptr;
    // pętla dla wszystkich przycisków zainicjalizuje jako pull up wejscie
    for (uint8_t i = 0; i < buttons_all.buttons_num; i++) {
        init_button(&buttons_all.buttons[i]);
    }

    // Timer1 dla odczytu stanu przycisku co 10ms
    TCCR1B |= (1 << WGM12); // Tryb CTC
    TCCR1B |= (1 << CS12) | (1 << CS10); // Preskaler 1024
    //OCR1A = (F_CPU / (2 * N * Częstotliwość przerwań)) - 1
    //OCR1A = 1562; // Wartość licznika dla 10Hz - za wolny
    OCR1A = 16; // Wartość licznika dla 1kHz 
    TIMSK1 |= (1 << OCIE1A); // Włącz przerwanie od porównania z OCR1A
    sei();
}


ISR(TIMER1_COMPA_vect) {
    
    for (uint8_t i = 0; i < buttons_all.buttons_num; i++) {
        Button *button = &buttons_all.buttons[i];

        if((*button->pin_reg & (1 << button->pin)) == 0){
            button -> press_duration += 1;
            
            if(button->press_duration >= DEBOUNCE_MS){
                if ((i == 0) && !(*buttons_all.position >= *buttons_all.numItems - 1)){
                    *buttons_all.position += 1;
                }
                if ((i == 1) && !(*buttons_all.position <= 0)){
                    *buttons_all.position -= 1;
                }
                if ((i == 2) ){
                    *buttons_all.flag_OK = 1;
                }
                if ((i == 3) ){
                    *buttons_all.flag_BACK = 1;
                }
                button->press_duration = 0;
            }
        }
        else{
            button->press_duration = 0;
        }
       
    }
}