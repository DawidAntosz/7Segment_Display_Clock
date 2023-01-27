#ifndef MAX7219_H
#define MAX7219_H

#define DDR_SPI DDRB
#define DD_MOSI PB3
#define DD_SCK PB5
#define DD_SS PB2

#define NoOp_Register 0x00
#define DecodeMode_Register 0x09
#define Intensity_Register 0x0A
#define ScanLimit_Register 0x0B
#define Shutdown_Register 0x0C
#define DisplayTest_Register 0x0F

#define DIG_1 1
#define DIG_2 5
#define DIG_3 3
#define DIG_4 4
#define DIG_5 6
#define DIG_6 2
#define DIG_Led 7

#define Clock_Mode 1


void MAX7219_init(void);
void SPI_MasterInit(void);
void SPI_MasterTransmit(char cData);
void MAX7219_write(char register_data, char data);
void MAX7219_displayTest(uint8_t number);
void MAX7219_displayClock(uint8_t* hour, uint8_t* minute, uint8_t* second);





#endif