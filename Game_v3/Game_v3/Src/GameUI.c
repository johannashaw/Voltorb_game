/*
 * GameUI.c
 *
 * Created:	2023-04-15 5:46:46 PM
 * Author:	Johanna Shaw 
 */ 

#include "GameUI.h"
#include "SSD1306.h"
#include "Gameplay.h"
#include "Buttons.h"

// Symbols:

// Larger symbols that are to be displayed within the tiles on the grid
char BigSymbols[ 4 * 5] =
{
	0b00000000, 0b11011101, 0b10111000, 0b11101101, 0b11000000,			// bomb
	0b00100001, 0b00011000, 0b01000010, 0b00010001, 0b11000000,			// 1
	//0b00100001, 0b00001000, 0b01000010, 0b00010000, 0b10000000,		// 1
	0b01110110, 0b11100010, 0b00110011, 0b00110011, 0b11100000,			// 2
	0b01110110, 0b11000110, 0b01100001, 0b11101101, 0b11000000			// 3
};

// Smaller numbers indicating points-totals for each column or row 
// these are to be displayed underneath each column or to the right of each row.
char SmolSymbols[10 * 2] =
{
	0b11110110, 0b11011110,	// 0
	0b00100100, 0b10010010,	// 1
	0b11100111, 0b11001110,	// 2
	0b11100111, 0b10011110,	// 3
	0b10110111, 0b10010010,	// 4
	0b11110011, 0b10011110,	// 5
	0b10010011, 0b11011110,	// 6
	0b11100100, 0b10010010,	// 7
	0b11110111, 0b11011110,	// 8
	0b11110111, 0b10010010	// 9
};

// Displays the titleScreen for the game.
void GameInitUI()
{	
	SSD1306_Clear();
	char row = 0;
	SSD1306_StringXY(0, row++, "Boom-Boom");
	row++;
	SSD1306_StringXY(0, row++, "Created by Johanna ");
	SSD1306_StringXY(0, row++, "Shaw. Based off a");
	SSD1306_StringXY(0, row++, "Pokemon minigame");
	row++;
	SSD1306_StringXY(0, row++, "Press any button to");
	SSD1306_StringXY(0, row++, "begin");

	
	SSD1306_Render();
}

/*		An Explanation of the grid: the portion that contains the tiles is 100 px by 100px tiles are laid out in a 5 x 5 matrix each tile is 9 px wide, tiles are separated by 1px line and tile section is outlined in a 1px line  tile matrix makes up the first 5 ( 0 to 4) rows and columns of the grid, with a 6th row and a 6th column at the end the last row indicates the amount bombs and the sum of the point tiles in it's respective column it's the same idea for the last column  The origin of the grid is 0,0. Where this ends up on the OLED is determined in the AddPxGrid function,  and depends on which orientation mode the game is in ( Landscape or Portrait, defined by a macro)each row/column will begin at a multiple of 10.*/

// sends a pixel relative to the grid's origin// grid origin and display orientation are relative to whether the game is in portrait or landscape modevoid AddPxGrid(char px, int iX, int iY){	
	#ifdef PORTRAIT_MODE
	// The pixel that the x and y plane start displaying at (AKA gird origin)	int temp = iY + 65 ;	iY = 63 - (iX); //+ 2);	iX = temp;	//int xStart = 2;	//int yStart = 65;
	//SSD1306_SetSpecPixel( px, iY + yStart, iX + xStart);	#endif
	
	#ifdef LANDSCAPE_MODE
	// The pixel that the x and y plane start displaying at (AKA gird origin)	iX += 65;	iY += 4;	//int xStart = 65;	//int yStart = 2;
	//SSD1306_SetSpecPixel( px, iX + xStart, iY + yStart);	#endif	
	SSD1306_SetSpecPixel( px, iX, iY);}// makes the outline of the 5x5 tile grid.void MakeGrid(){		for (int i = 0; i < 6; i++)	{		for (int j = 0; j < 50; j++)		{			// add col pixel			//AddPxPortrait(1, i * 10, j);			AddPxGrid(1, i * 10, j);						//add row pixel			//AddPxPortrait(1, j, i * 10);			AddPxGrid(1, j, i * 10);		}	}} // will display a given symbol in the tile at the specified row and columnvoid ChangeTile(int row, int col, char symbol, char showing){	if (symbol > 3)	{		Indicator_Tog;		return;	}			char *start = BigSymbols + symbol * 5;	for (int i = 0; i < 35; i++)	{				//AddPxGrid( showing, (i % 5) + col* 10 + 3 , (i / 5) + row * 10 + 2);		// displays a shaded block where the symbol would go		AddPxGrid( ( (*start >> (7 - (i % 8)) ) & 1 ) * showing, (i % 5) + col* 10 + 3 , (i / 5) + row * 10 + 2);				//if we're at the end of the byte, go to next		if ( i % 8 == 7)			start++;	}	}// a helper function for displaying the Point Sumvoid SendSmolSymbol(int xStart, int yStart, char Symbol){	char *start = SmolSymbols + Symbol * 2;	for (int i = 0; i < 15; i++)	{					//AddPxGrid( showing, (i % 5) + col* 10 + 3 , (i / 5) + row * 10 + 2);		// displays a shaded block where the symbol would go		//AddPxGrid( 1 , (i % 3) + xStart , (i / 3) + yStart);		AddPxGrid( ( (*start >> (7 - (i % 8)) ) & 1 ), (i % 3) + xStart , (i / 3) + yStart);		//AddPxGrid( (*start >> (7 - (i % 8)) ) & 1 , (i % 3) + xStart , (i / 3) + yStart);					//if we're at the end of the byte, go to next		if ( i % 8 == 7)		start++;	}	}// used to display the point total for a given column/row on the bottom/ right side (respectively) of the gridvoid DisplayPointSum(char value, int row, int col){		// x is + 3 and + 7	// y is + 5				SendSmolSymbol(col * 10 + 3 , row * 10 + 5, value / 10 );	// displays in the 10's spot		SendSmolSymbol(col * 10 + 7 , row * 10 + 5, value % 10 );	// displays in the 1's spot	}// Displays the number of bombs in a given row/column by means of ticks above the row/column point totalvoid DisplayBombLine(char bombs, int row, int col){		// x is + 3 and + 7		//// y is + 5		//SendSmolSymbol(col * 10 + 3 , row * 10 + 5, value / 10 );	// displays in the 10's spot		//SendSmolSymbol(col * 10 + 7 , row * 10 + 5, value % 10 );	// displays in the 1's spot		//		//AddPxGrid( ( (*start >> (7 - (i % 8)) ) & 1 ), (i % 3) + xStart , (i / 3) + yStart);				for (int i = 1; i <= bombs; i++)		{			AddPxGrid(1, col * 10 + (i << 1), row * 10 + 2);			AddPxGrid(1, col * 10 + (i << 1), row * 10 + 3);		}}