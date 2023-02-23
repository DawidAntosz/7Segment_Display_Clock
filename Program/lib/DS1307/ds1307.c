#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>

#include "ds1307.h"
#include "i2c.h"


const uint8_t DayInMonth [] PROGMEM = {31,28,31,30,31,30,31,31,30,31,30,31};

void DS1307_init(){
    I2C_init();
}

static uint8_t DS1307_bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}

static uint8_t DS1307_dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}

static uint16_t DS1307_date2days(uint8_t y, uint8_t m, uint8_t d) {
	uint16_t days = d;
	for (uint8_t i = 1; i < m; ++i)
		days += pgm_read_byte(DayInMonth + i - 1);
	if (m > 2 && y % 4 == 0)
		++days;
	return days + 365 * y + (y + 3) / 4 - 1;
}

static uint8_t DS1307_getdayofweek(uint8_t y, uint8_t m, uint8_t d) {
	uint16_t day = DS1307_date2days(y, m, d);
	return (day + 6) % 7;
}

uint8_t DS1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second){
    
    if (second < 0 || second > 59 ||
		minute < 0 || minute > 59 ||
		hour < 0 || hour > 23 ||
		day < 1 || day > 31 ||
		month < 1 || month > 12 ||
		year < 0 || year > 99)
		return 0;

	if(day > pgm_read_byte(DayInMonth + month - 1))
		return 0;

	uint8_t dayofweek = DS1307_getdayofweek(year, month, day);

	I2C_start_wait(DS1307_ADDR | I2C_WRITE);
	I2C_write(0x00);
	I2C_write(DS1307_dec2bcd(second));
	I2C_write(DS1307_dec2bcd(minute));
	I2C_write(DS1307_dec2bcd(hour));
	I2C_write(DS1307_dec2bcd(dayofweek));
	I2C_write(DS1307_dec2bcd(day));
	I2C_write(DS1307_dec2bcd(month));
	I2C_write(DS1307_dec2bcd(year));
	I2C_write(0x00);
	I2C_stop();

	return 1;
}

void DS1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second){
    
    I2C_start_wait(DS1307_ADDR | I2C_WRITE);
	I2C_write(0x00);
	I2C_stop();

	I2C_start(DS1307_ADDR | I2C_READ);
	*second = DS1307_bcd2dec(I2C_readAck() & 0x7F);
	*minute = DS1307_bcd2dec(I2C_readAck());
	*hour = DS1307_bcd2dec(I2C_readAck());
	I2C_readAck();
	*day = DS1307_bcd2dec(I2C_readAck());
	*month = DS1307_bcd2dec(I2C_readAck());
	*year = DS1307_bcd2dec(I2C_readNak());
	I2C_stop();
}


