/*
 * Buttons.h
 *
 * Created:		2023-04-12 10:23:21 PM
 * Author:		Johanna Shaw
 * Description:	This library deals with the setup and implementation of 5x5 button grid.
  				It uses the two callback functions passed in the ButtonsSetup function to indicate
  				when a given button has been pressed and held.
 */ 
 

#ifndef BUTTONS_H_
#define BUTTONS_H_

#endif /* BUTTONS_H_ */
// ********************************************************************************************************
// *****************************               MACROS:           ******************************************

// defines the bits for their respective register.
// trailing letter indicates which port it's on
#define ROW1_C 0b00000010		//
#define ROW2_C 0b00000100
#define ROW3_C 0b00001000
#define ROW4_D 0b00000100
#define ROW5_D 0b00001000

#define COL1_D 0b00010000
#define COL2_D 0b00100000
#define COL3_D 0b01000000
#define COL4_D 0b10000000
#define COL5_B 0b00000001

// #define IndicatorLed PORTB1
#ifndef IndicatorLed_B
#define IndicatorLed_B 0b00000010		
#endif


#define Indicator_On PORTB |= 0b00000010
#define Indicator_Off PORTB &= ~0b00000010
#define Indicator_Tog PINB = 0b00000010




//****************************************************************************
//								Function Declarations
//****************************************************************************


// Sets up button grid and indicator led,
// Stores the two callback functions for later use in CheckButtons.
void ButtonsSetup(void (*PushedCallback)(int, int), void (*HeldCallback)(int, int));

// Will call the PushedCallback when pushed, and HeldCallback when held for 10 calls,
// Both callbacks will be passed the button's row and column 
void CheckButtons();

// for reassigning the pushed callback function.
void ReassignButtonCallback(void (*CallbackFunc)(int, int));