#ifndef I2C_H
#define I2C_H


#define I2C_READ 1
#define I2C_WRITE 0


extern void I2C_init(void);

extern unsigned char I2C_start(unsigned char addr);
extern void I2C_start_wait(unsigned char addr);
extern void I2C_stop(void);

extern unsigned char I2C_write(unsigned char data);
extern unsigned char I2C_read(unsigned char ack);

extern unsigned char I2C_readAck(void);
extern unsigned char I2C_readNak(void);

extern unsigned char I2C_read(unsigned char ack);


#endif