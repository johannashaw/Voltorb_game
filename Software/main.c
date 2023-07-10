/*
 * Game_v3.c
 *
 * Created: 3/31/2023 1:38:12 PM
 * Author : Johanna Shaw
 * Description :	The main file for the Voltorb game. Will handle button callbacks, and OLED displays for things that
					are game specific and require multiple GamePlay pointers.
 */ 
#ifndef F_CPU
#define F_CPU 2E6 // with external xtal enabled, and clock div/8, bus == 2MHz
#endif


#include <avr/io.h>
#include <util/delay.h> // have to add, has delay implementation (requires F_CPU to be defined)
#include <stdio.h>
#include "sci.h"
#include "Buttons.h"
#include "SSD1306.h"
#include "Gameplay.h"
#include "GameUI.h"

// Macros
#ifndef IndicatorLed_B
#define IndicatorLed_B 0b00000010		// #define IndicatorLed PORTB1
#endif

// Macros to be uncommented when testing and debugging respectively.

//#ifndef TESTING
//#define TESTING
//#endif
//
//#ifndef DEBUG_MAIN
//#define DEBUG_MAIN
//#endif


// for accessing the board
#define Board(row, col) (board[row * 5 + col])



//****************************************************************************
//								Global Variables:
//****************************************************************************

// Pointers to the variables used in gameplay
char *board; 
int *totalPoints;
int *Level;
int *LevelPoints;

// holds which row the LevelPoints should be drawn too,
// so that I don't have to change this in a bunch of places later if I decide to move stuff around
char pointRow = -1;

//****************************************************************************
//								Function Declarations:
//****************************************************************************

void ButtonPressed(int row, int col);
void ButtonHeld(int row, int col);

void StartGame();
void TestGame();
// OLED UI functionsvoid RevealAllTiles();void FullNewScreen();


int main(void)
{
	//  **************************************************************
	//							local variables
	//  **************************************************************
	
	
	//  **************************************************************
	//							One-Time Inits:
	//  **************************************************************
	
	// set up serial for 2MHz bus, 9600 BAUD, no interrupts
	SCI0_Init(F_CPU, 9600, 0);
	SCI0_TxString("\n\nHello from the ATmega328P!\n\n");
	
	// initialize OLED
	SSD1306_DispInit();
	
	// initialize the Game UI
	//GameInitUI();

	board = GetArray_pt();
	totalPoints = GetTotalPoints_pt();
	Level =GetLevel_pt();
	LevelPoints = GetLevelPoints_pt();

	// initialize the game.
	Boardinit();
	
	#ifdef TESTING
	TestGame();		// initialize the buttons and set buttonPressed and held callback functions	ButtonsSetup(&ButtonPressed, &ButtonHeld);
	#endif
	
	#ifndef TESTING	// display the title screen on the OLED	GameInitUI();		// initialize the buttons and set buttonPressed and button_held callback functions	// StartGame will get called when a button is first pressed, (this gets reassigned after title screen is displayed)	// ButtonHeld will be called when a button is pressed for 2 seconds	ButtonsSetup(&StartGame, &ButtonHeld);		#endif
	
		
	// main program loop - don't exit
	while(1)
	{
		// current version is running based on delays, may change to interrupts later.
		_delay_ms(100);
				
		// toggle the led, inicating game is running
		PINB = IndicatorLed_B;
		
		// Does checks of each the 25 game buttons. Will pass the row and column to 
		// the respective callback funtions if a button is pressed or held for 2 seconds
		CheckButtons();
	}
}

//****************************************************************************
//								Function Declarations:
//****************************************************************************// A button was pressed, do something with that information.void ButtonPressed(int row, int col){	char output[30];		// tells the GamePlay file that the user has pressed a button	// this is the only way in which the user will interact with the game itself, and apart from making a newLevel at the 	char retval = TryReveal(row, col);			#ifdef DEBUG_MAIN	sprintf(output, "row = %d, col = %d\n", row, col);	SCI0_TxString(output);			qPrint("retval = %d\n\n", retval);	#endif			// if 0, no changes so return	if (retval == 0)		return;			// only one of the tiles has changed:	if (retval < 3)	{		ChangeTile(row, col, Board(row,col) & ValueBits, (Board(row,col) & RevealedBit) >> 3);	
		// update level points		sprintf(output, "%9d", *LevelPoints);
		SSD1306_StringXY(0, pointRow, output);				// indicate the lose state		if (retval == 2 && *LevelPoints == 0)				SSD1306_StringXY(0, 7, "You Lost.");		// indicate the win state		else if (retval == 2 && *LevelPoints > 0)			SSD1306_StringXY(0, 7, "Win!     ");						
		SSD1306_Render();		return;	}	// End of a level, show the board:	if (retval == 3)	{		RevealAllTiles();
		SSD1306_Render();		return;	}		// retval == 4, time to clear and reset the screen for a new level.	FullNewScreen();}// A button was pressed, do something with that information.void ButtonHeld(int row, int col){	#ifdef DEBUG_MAIN	char output[18];	sprintf(output, "held %d %d", row, col);			SSD1306_StringXY(0,1,output);	Indicator_Tog;	#endif		#ifdef TESTING	RevealAllTiles();		#endif}#ifdef DEBUG_MAINvoid CheckChange(){	char output[50];
	//SCI0_TxString("CheckChanged:\n");
	for (int i = 0; i < 25; i++)	{		// Access via pointers:		//sprintf(output, "Tile *(board + %d) = %d\n", (int)i, (int)*(board + i)); 		//SCI0_TxString(output);				// Access like an array:		sprintf(output, "Tile %d = %d\n", (int)i, board[i]); 		SCI0_TxString(output);	}	sprintf(output, "\ntp = %d, lvl = %d, lvlpts = %d\n\n", *totalPoints, *Level, *LevelPoints);
	SCI0_TxString(output);}#endifvoid RevealAllTiles(){	for (int i = 0; i < 25; i++) 	{		ChangeTile(i / 5, i % 5, board[i] & ValueBits, 1);	}	SSD1306_Render();}void FullNewScreen(){	char output[50];
	int row = 0;
	
		#ifdef DEBUG_MAIN	CheckChange();	#endif
	
	SSD1306_Clear();

	//display the game title
	SSD1306_StringXY(0, row++, "Boom-Boom");
	row++;
	
	//display level	sprintf(output, "Level: %2d", *Level);
	SSD1306_StringXY(0, row++, output);

	//display total points
	SSD1306_StringXY(0, row++, "Total:");	sprintf(output, "%9d", *totalPoints);
	SSD1306_StringXY(0, row++, output);

	//display level points
	SSD1306_StringXY(0, row++, "Points:");
	pointRow = row;		// so that the Points will always be printed to the right row	sprintf(output, "%9d", *LevelPoints);
	SSD1306_StringXY(0, row++, output);



	row++;
	
	// make game grid	MakeGrid();	// display the bombs and points for each row/column'	for (int i = 0; i < 5; i++)	{		char rowBombs = 0, colBombs = 0, rowPts = 0, colPts = 0;		for (int j = 0; j < 5; j++)		{			// going through i row: Board(i, j)			rowBombs += (Board(i, j) & ValueBits) == 0;			rowPts += Board(i, j) & ValueBits;						// going through i column: Board(j, i)			colBombs += (Board(j, i) & ValueBits) == 0;			colPts += Board(j, i) & ValueBits;		}		// set for row		DisplayBombLine(rowBombs, i, 5);		DisplayPointSum(rowPts, i, 5);		// set for col		DisplayBombLine(colBombs, 5, i);		DisplayPointSum(colPts, 5, i);	}	
	SSD1306_Render();}// Only called at the beginning of the game (when not in Test mode)// void StartGame(){	//NewLevel();	// display the new level on the OLED	FullNewScreen();		// Reassign the button-press callback so that it actually plays the game.	ReassignButtonCallback(&ButtonPressed);}

// Code used in testing.
void TestGame(){	char output[50];		SCI0_TxString("\nBoard in main.TestGame:\n");		// Display each of the tiles			//StartGame();	FullNewScreen();			SCI0_TxString("\nBack to Board in main.TestGame:\n");	}