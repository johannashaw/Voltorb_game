/*
 * Supplement.c
 *
 * Created: 2023-04-15 8:56:45 PM
 *  Author: Johanna
 */ 
#include "Supplement.h"
//#include <avr/io.h>
//#include <stdio.h>
#include <stdlib.h>



// For the EEPROM write operation, the EEDR Register contains the data to be written to the EEPROM in
// the address given by the EEAR Register. For the EEPROM read operation, the EEDR contains the data
// read out from the EEPROM at the address given by EEAR.


/* The following two functions were provided to my by the ATmega328/P Datasheet: 
	EEPROM_write
	EEPROM_read
*/

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}


unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}




void initRandom()
{
	//base += random();
	//srandom((int)base);
}



int GetRandom()
{
	
	return random();
}

int GetRandomMax(int max)
{
	return random() % max;
}

int GetRandomMinMax(int min, int max)
{
	return random() % (max - min) + min;
}


