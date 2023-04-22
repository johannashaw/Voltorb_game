/*
 * Buttons.c
 *
 * Created: 2023-04-12 10:23:34 PM
 *  Author: Johanna
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "sci.h"
#include "Buttons.h"
#include "SSD1306.h"

// Set Rows 1, 2, and/or 3 to high
#define ROW1to3_C_On(Row) PORTC |= Row// Set Rows 1, 2, and/or 3 to low
#define ROW1to3_C_Off(Row) PORTC &= ~(Row)
// Set Rows 4 and/or 5 to high
#define ROW4to5_D_On(Row) PORTD |= Row// Set Rows 4 and/or 5 to low
#define ROW4to5_D_Off(Row) PORTD &= ~(Row)

	// for outputs, set to a 1							// for inputs set to a 0	// Rows: (Outputs)									// Columns: (Inputs)	// 1 = PC1											// 1 = PD4	// 2 = PC2											// 2 = PD5	// 3 = PC3											// 3 = PD6	// 4 = PD2											// 4 = PD7	// 5 = PD3											// 5 = PB0

//****************************************************************************
//						Globals (private to this file):
//****************************************************************************

// Shows whether the buttons are pressed or not:
int ArePressed[25];
char WasPressed = 0;
//int ArePressed[2];
// Function that gets called when a button is initially pressedvoid (*ButtonpressedCallback)(int, int);		//this can't be in the header or it'll breakvoid (*ButtonHeldCallback)(int, int);		//this can't be in the header or it'll break

//****************************************************************************
//									Functions:
//****************************************************************************// setting up the buttons that are being usedvoid ButtonsSetup(void (*PushedCallback)(int, int), void (*HeldCallback)(int, int)){
	// set global Callback function pointer to the one passed to us
	ButtonpressedCallback = *PushedCallback;	ButtonHeldCallback = *HeldCallback;		//Set as as outputs	DDRC |=	ROW1_C | ROW2_C | ROW3_C;	DDRD |= ROW4_D | ROW5_D;		//set the outputs to high	ROW1to3_C_On(ROW1_C | ROW2_C | ROW3_C);	ROW4to5_D_On(ROW4_D | ROW5_D);		//disable the pull-ups *IMPORTANT*	PORTD &= ~(COL1_D | COL2_D | COL3_D | COL4_D);	PORTB &= ~COL5_B;	// Set pins as inputs	DDRD &= ~(COL1_D | COL2_D | COL3_D | COL4_D);		//0b 0000 1111	DDRB &= ~COL5_B;		//0b 1111 1110		
		
	// indicator led setup
	DDRB |= IndicatorLed_B;			// set all bits in ArePressed to 0	//ArePressed[0] = ArePressed[1] = 0;	for (int i = 0; i < 25; i++)		ArePressed[i] = 0;	}// Used in the Check BUttons function// checks to see if any of the buttons in the given row is pushed, if so, invokes the callback function void __checkColsHelper(int row){	//cause I started this stupid:		row--;		//for columns 1 through 4, pins on port D	for (int col = 0; col < 4; col++)	{		if(PIND & (1 << (col + 4)))		{			ArePressed[row*5 + col]++;						// Callback for when the button is first pressed			if (ArePressed[row*5 + col] == 1)				ButtonpressedCallback(row, col);							// Callback for when the button is held for 2 seconds			else if (ArePressed[row*5 + col] == 10)			{				ButtonHeldCallback(row, col);			}		}		else		{			ArePressed[row*5 + col] = 0;		}	}	//for col 5, pin on port B	if (PINB & COL5_B)	{		ArePressed[row*5 + 4]++;					// Callback for when the button is first pressed		if (ArePressed[row*5 + 4] == 1)			ButtonpressedCallback(row, 4);					// Callback for when the button is held for 2 seconds		else if (ArePressed[row*5 + 4] == 10)			ButtonHeldCallback(row, 4);	}	else		ArePressed[row*5 + 4] = 0;}// A button in column 1, 2, 3, and/or 4 has been pushed.// Find out which row/column belongs to the button(s) pressed.void CheckButtons(){	// if no buttons are pressed, leave
	if (!((PIND & (COL1_D | COL2_D | COL3_D | COL4_D)) | (COL5_B & PINB)))	{		WasPressed = 0;		return;	}		if (!WasPressed)	{		for (int i = 0; i < 25; i++)			ArePressed[i] = 0;	}		// set the outputs of the rows to 0	ROW1to3_C_Off(ROW1_C | ROW2_C | ROW3_C);	ROW4to5_D_Off(ROW4_D | ROW5_D);		// go through each row, setting the output to 1, and seeing if any of the columns inputs are high	// for rows 1 to 3, the pins on port C	for (int row = 1; row <= 3; row++ )	{		//set the row we're checking to high		ROW1to3_C_On(1 << row);				//check each column		__checkColsHelper(row);				// set the row back to low		ROW1to3_C_Off(1 << row);	}	// for rows 4 and 5, the pins on port D	for (int row = 4; row <= 5; row++ )	{		ROW4to5_D_On(1 << (row - 2));				//check each column		__checkColsHelper(row);						ROW4to5_D_Off(1 << (row - 2));	}		// set rows back to high	ROW1to3_C_On(ROW1_C | ROW2_C | ROW3_C);	ROW4to5_D_On(ROW4_D | ROW5_D);			WasPressed = 1;}
// if you want the button to do something different midway through the application
void ReassignButtonCallback(void (*CallbackFunc)(int, int)){
	// set global Callback function pointer to the one passed to us
	ButtonpressedCallback = *CallbackFunc;}