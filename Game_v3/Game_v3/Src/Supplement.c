/*
 * Supplement.c
 *
 * Created: 2023-04-15 8:56:45 PM
 * Author:	Johanna Shaw
 */ 
#include "Supplement.h"
#include <avr/io.h>
#include <stdlib.h>

// Is the address that we 
static unsigned int addStart = 0;

// initializes the random function used to create new games, 
// the seed used is taken from memory, used as a seed, and then a new random number is selected and replaces the seed
// therefore insuring that it will be different each time
void initRandom()
{
	// seed the random generator using the value stored in EEPROM
	srandom((long)EEPROM_read(addStart) + (((long)EEPROM_read(addStart + 1)) << 8));
	
	// rewrite the EEPROM value with a new random number generated using the last seed
	int temp = (int)random();
	EEPROM_write(addStart, (char)temp);
	EEPROM_write(addStart + 1, (char)(temp >> 8));
}


// returns a random integer
int GetRandom()
{
	return random();
}

// generates a random int up until max (exclusive)
int GetRandomMax(int max)
{
	return random() % max;
}

// generates a random int from min (inclusive) to max (exclusive)
int GetRandomMinMax(int min, int max)
{
	return random() % (max - min) + min;
}



/* The following two functions were provided to my by the ATmega328/P Datasheet: */

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
