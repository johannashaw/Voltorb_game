/*
 * Supplement.h
 *
 * Created: 2023-04-15 8:56:32 PM
 * Author:	Johanna Shaw
 
 * Purpose: To define different random functions for the game-play to use while 
			creating the game board.
			This is in a separate library to allow for easier changes in mediums.
 */ 


#ifndef SUPPLEMENT_H_
#define SUPPLEMENT_H_
#endif /* SUPPLEMENT_H_ */

void initRandom();

// returns a random integer
int GetRandom();

// returns a random int from 0 to max
int GetRandomMax(int max);

// returns a random int from min to max
int GetRandomMinMax(int min, int max);


// functions for reading and writing from EEPROM
// taken directly from the ATmega328/P Datasheet
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
