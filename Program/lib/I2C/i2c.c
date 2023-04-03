#include <avr/io.h>
#include <stdbool.h>
#include <inttypes.h>
#include <compat/twi.h>
#include "i2c.h"

#define F_CPU 16000000UL
#define SCL_CLOCK  10000L


void I2C_init(void){
    TWSR = 0; 
	uint16_t twbr_val = ((F_CPU / SCL_CLOCK) - 16) / 2;
    TWBR = (uint8_t)twbr_val;
}

unsigned char I2C_start(unsigned char addr){
    
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	
	if(((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)){
        return 1;
    }

	TWDR = addr;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	if(((TW_STATUS & 0xF8) != TW_MT_SLA_ACK) && ((TW_STATUS & 0xF8) != TW_MR_SLA_ACK)){
        return 1;
    } 

	return 0;
}

void I2C_start_wait(unsigned char addr){
    while(1)
    {
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    
    	while(!(TWCR & (1<<TWINT)));
    
    	if(((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)){
            continue;
        }
    
    	TWDR = addr;
    	TWCR = (1<<TWINT) | (1<<TWEN);
    
    	while(!(TWCR & (1<<TWINT)));
    
    	if (((TW_STATUS & 0xF8) == TW_MT_SLA_NACK) || ((TW_STATUS & 0xF8) == TW_MR_DATA_NACK)){
	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	        
	        while(TWCR & (1<<TWSTO));
	        
    	    continue;
    	}
    	break;
     }
}

void I2C_stop(void){
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    while(TWCR & (1<<TWSTO));
}

unsigned char I2C_write(unsigned char data){

    TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	if((TW_STATUS & 0xF8) != TW_MT_DATA_ACK){
        return 1;
    }
	return 0;
}

unsigned char I2C_read(unsigned char ack){
    return (ack) ? I2C_readAck() : I2C_readNak(); 
}

unsigned char I2C_readAck(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;
}

unsigned char I2C_readNak(void){
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;
}


