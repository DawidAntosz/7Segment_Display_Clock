#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "MAX7219.h"

const uint8_t DIG_tab[7] = {1,5,3,4,6,2,7};

const uint8_t Set_number[10] = {
							   0b10101111,	/* 0 */
							   0b00001010,	/* 1 */
							   0b10111001,	/* 2 */
							   0b10111010,	/* 3 */
							   0b00011110,	/* 4 */
							   0b10110110,	/* 5 */
							   0b10110111,	/* 6 */
							   0b10001010,	/* 7 */
							   0b10111111,	/* 8 */
							   0b10111110,	/* 9 */
							   0b00000000,	/* NULL */
							   0b11111111	/* FULL */
											};

void MAX7219_init(void){

    SPI_MasterInit();

    MAX7219_write(Shutdown_Register, 1); // Shutdown adres write 1 for mode- Normal Operation
    MAX7219_write(DecodeMode_Register, 0x00); // Decode Mode write 0xff for mode -Code B decode for digits 7–0-
    MAX7219_write(Intensity_Register, 8); // Intensity adres write 8 mode- 17/32 min on
    MAX7219_write(ScanLimit_Register, 6); // Scan Limit adres 6 mode - Display digits 0 1 2 3 4 5 6 -
    if(Clock_Mode){
        MAX7219_write(DIG_tab[6], 0b10101010);
    }
}

void SPI_MasterInit(void){
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData){
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
}

void MAX7219_write(char register_data, char data){
    PORTB &= ~(1<<DD_SS); // allow transfer
    // sent in 16-bit packets
    SPI_MasterTransmit(register_data); // first 8 bit adres
    SPI_MasterTransmit(data); // second 8 bit data
    PORTB |= (1<<DD_SS); // close tranfer
}


void MAX7219_displayTest(uint8_t number){

    if (number > 0 && number <10){
        MAX7219_write(DIG_1, Set_number[number]);
        MAX7219_write(DIG_2, Set_number[2]);
        MAX7219_write(DIG_3, Set_number[3]);
        MAX7219_write(DIG_4, Set_number[4]);
        MAX7219_write(DIG_5, Set_number[5]);
        MAX7219_write(DIG_6, Set_number[6]);
        MAX7219_write(DIG_Led, 0b10101010);
    }

}

void MAX7219_displayClock(uint8_t* hour, uint8_t* minute, uint8_t* second){

    uint8_t tab_value[6];
    tab_value[5] = *hour / 10; //decimals units
    tab_value[4] = *hour % 10; //parts of unity ...
    tab_value[3] = *minute / 10;
    tab_value[2] = *minute % 10;
    tab_value[1] = *second / 10;
    tab_value[0] = *second % 10;

    for(auto i = 0; i<6 ;i++){
        MAX7219_write(DIG_tab[i], Set_number[tab_value[i]]);
    }
}
