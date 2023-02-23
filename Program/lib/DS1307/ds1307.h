#ifndef DS1307_H
#define DS1307_H

#define DS1307_ADDR (0x68<<1) 

extern void DS1307_init();

extern uint8_t DS1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
extern void DS1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second);

#endif