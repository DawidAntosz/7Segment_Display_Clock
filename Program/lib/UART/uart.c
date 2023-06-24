#include "uart.h"

void uart_init() {
    UBRR0H = (UBRR_VALUE >> 8);
    UBRR0L = UBRR_VALUE; // predkosc transmisji1
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // wlaczenie odbiornika i nadajnika
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // format ramki- 8bit, 1 bit stopu
}

void uart_send_char(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // oczekiwanie zakonczenia transmisji
    UDR0 = data; // Wysła dane
}

void uart_send_string(const char* str) {
    uint8_t i = 0;
    while (str[i] != '\0') {
        uart_send_char(str[i]);
        i++;
    }
}

char uart_receive_char() {
    while (!(UCSR0A & (1 << RXC0))); // Oczekiwanie na dane
    return UDR0; // zwraca otrzymana dana
}

void uart_receive_string(char* buffer, uint8_t buffer_size) {
    uint8_t i = 0;
    char received_char;

    do {
        received_char = uart_receive_char();
        buffer[i] = received_char;
        i++;
    } while (received_char != '\n' && i < (buffer_size - 1));
    
    buffer[i] = '\0'; // null na koncu
}