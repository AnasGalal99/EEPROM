/*
 * ATmega16_Master_I2C.c
 */ 


#define F_CPU 8000000UL						/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>							/* Include AVR std. library file */
#include <util/delay.h>						/* Include inbuilt defined Delay header file */
#include <string.h>							/* Include string header file */
#include "i2c.h"							/* Include I2C header file */
#include "uart.h"
#define EEPROM_Write_Addess		0xA0
#define EEPROM_Read_Addess		0xA1

int main(void)
{
	char array[20] = "Anas Test";			/* Declare array to be print */
	uart_init();							/* Initialize uart */
	I2C_INIT();								/* Initialize I2C */
	while(1)
	{
		
	serial_debug("start writing to eeprom");
	I2C_START(EEPROM_Write_Addess);			/* Start I2C with device write address */
	I2C_SEND(0x00);						/* Write start memory address for data write */
	for (int i = 0; i<strlen(array); i++) 
		{
			I2C_SEND(array[i]); 
		}
	I2C_STOP();								/* Stop I2C */
	_delay_ms(2000);
	serial_debug("start reading from eeprom");
	I2C_START(EEPROM_Write_Addess);				/* Start I2C with device write address */
	I2C_SEND(0x00);								/* Write start memory address */
		for (int i = 0; i<strlen(array); i++)
		{
			I2C_SEND(array[i]);
		}
	I2C_STOP();
	I2C_START();						/* Start I2C with device write address */
	I2C_SEND(EEPROM_Write_Addess);		/* Write start memory address */
	I2C_SEND(0x00);
	I2C_START(EEPROM_Read_Addess);	/* Repeat start I2C with device read address */
	
	for (int i = 0; i<strlen(array); i++)
	{
		serial_debug(I2C_RECIEVE(1));
	}
	I2C_STOP();								/* Stop I2C */	
}
}