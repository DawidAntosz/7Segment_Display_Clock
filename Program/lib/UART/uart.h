#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUD_RATE 9600
#define F_CPU 16000000UL
#define UBRR_VALUE ((F_CPU / (BAUD_RATE * 16UL)) - 1)

void uart_init();
void uart_send_char(char data);
void uart_send_string(const char* str);
char uart_receive_char();
void uart_receive_string(char* buffer, uint8_t buffer_size);


#endif //UART_H