/*
 * Gameplay.c
 *
 * Created: 2023-04-15 8:56:32 PM
 * Author:	Johanna Shaw
 */ 
 
#include <stdio.h>
#include "Gameplay.h"
#include "Supplement.h"
#include "sci.h"

// for accessing the board
#define Board(row, col) board[row * 5 + col]


typedef enum GameState
{
	Playing,
	Win,
	Show_W,
	Lose,
	Show_L
}GameState;

//****************************************************************************
//						Globals (private to this file):
//****************************************************************************


// global var for the game board values, and which tiles are currently showing
static char board[25];   // will

// 
static int totalPoints = 0;
static int Level = 0;
static int LevelPoints = 0;
GameState State = Show_W;



//****************************************************************************
//									Functions:
//****************************************************************************


/*
// initializations that need to be done for the game
// give the game the function it needs to use for random number generation
void  Boardinit(char **brd, int **tPts, int **lvl, int **lvlpts)
//char*  Boardinit(int *tPts, int *lvl, int *lvlpts)
{
	//NewLevel();
	//
	//tPts = &totalPoints;
	//lvl = &Level;
	//lvlpts = &LevelPoints;
	
	//   
	*brd = board;
	tPts = &totalPoints;
	lvl = &Level;
	lvlpts = &LevelPoints;

	for (int i = 0 ;i < 25; i++)
	{
		board[i] = (char)i;// % 4;
	}
	
	SCI0_TxString("Board in Gameplay Init:\n");
	char output[30];
	for (int i = 0; i < 10; i++)
	{
		sprintf(output, "Tile *(board + i) %d = %d\t", i, *(board + i));
		SCI0_TxString(output);	

		sprintf(output, "Tile (board + i) %d = %d\n", i, (board + i)); 
		SCI0_TxString(output);
	}
	// *brd = board;
	
	//return;
	//return board;
	//return board;
}
*/

// initializations that need to be done for the game
// give the game the function it needs to use for random number generation
void  Boardinit()
{
	totalPoints = 0;
	Level = 0;
	LevelPoints = 0;
	
	// Initializes the random functions accessed by Supplement.h
	initRandom();
	
	// Makes a new level to start the game.
	NewLevel();
}

//	*********************************************************************************************
//		 The following are to pass the gameplay variables to your main function:
char* GetArray_pt()
{
	return board;

}
int* GetTotalPoints_pt()
{
	return &totalPoints;

}

int* GetLevel_pt()
{
	return &Level;
}

int* GetLevelPoints_pt()
{
	return &LevelPoints;
}


//	*********************************************************************************************

// Populate the game for the Next level.
// Levels start at 1 and go up to 9. 
// If the player lost the last level, they will move down a level up until level 1.
// If the player won the last level, they will move up a level until level 9.
void NewLevel()
{
	// local vars:
	int Spot = 0;
	char temp = 0;
	
	// reset level points
	LevelPoints = 1;	
	
	SCI0_TxString("\n\nGameplay NewLevel\n");
   
	// player won, increment Level (up to 9)
	if (State == Show_W)
	{
		Level++;
		if (Level > 9)
			Level = 9;
	}
	// player lost, decrement level (down to 1)
	else
	{
		Level--;
		if (Level < 1)
			Level = 1;		
	}
	
	// Use the level to determine the number of bombs and points
	char bombs = (Level/6)*10 + !(Level/5) * (Level + 5);
	
	// Use the level to determine points to give. A slight random variance or +-1 can be added, but isn't necessary.
	char PTs = Level + 5;		
	
	
	//qPrint("bombs: %d\n", bombs);	
	//qPrint("PTs: %d\n\n", PTs);
   
	// Add all the bombs
	for (Spot = 0; Spot < bombs; Spot++ )
	{
		board[Spot] = 0;
	}

	// Add all the points to the array
	while (PTs > 0 && PTs < 25)
	{
		// randomly chose a number 1 or 2 (will become 2 or 3)
		temp = GetRandomMax(2) + 1;
			
		// 
		board[Spot] = temp + 1;
		PTs -= temp;
		
				
		Spot++;
	}

	// Fill remainder's with 1s
	for (;Spot < 25; Spot++)
	{
		board[Spot] = 1;
	}

	// Shuffle the array using the Fisher-Yates shuffle
	for (int i = 24; i > 0; i--)
	{
		Spot = GetRandomMax(25);
		temp = board[i];
		board[i] = board[Spot];
		board[Spot] = temp;
	}	   
	
	State = Playing;
}



// takes a value for the row and column and uses them to check what to do next in the game
// Returns:
//		0 => no change
//		1 => smol change		(one tile)
//		2 => win/lose change	(one tile and indicate win/lose)
//		3 => big change			(Flip all of the tiles)
//		4 => New level
int TryReveal(int row, int col)
{
	// if the state  is win/lose:
	if (State == Win || State == Lose)
	{
	//		- increment state
	//		- set all tiles to shown
	//		- return 3
		totalPoints += LevelPoints;
		State++;
		for (int i = 0; i < 25; i++)
			board[i] |= RevealedBit;
		return 3;		
	}
	
	// if state is show_L or Show_W:
	if (State == Show_W || State == Show_L)
	{
	//		- call newlevel (it will change State to Playing)
	//		- return 3
		NewLevel();
		return 4;
	}
	
	// if the revealed bit at the given tile != 0 (already revealed)
	if ((Board(row, col) & RevealedBit) != 0)
	//		- return 0
		return 0;
	
	// change the bit to revealed
	Board(row, col) |= RevealedBit;
	// multiply level points by tile's value
	LevelPoints *= Board(row, col) & ValueBits;
	
	// if the given tile's value is 0 (ie a bomb)
	if (!(Board(row, col) & ValueBits))
	{
	//		- change state to lose
	//		- return 2
		State = Lose;
		return 2;
	}
	
	// if IsWin() returns 1, indicating level was won:
	if (IsWin())
	{
	//		- change state to Win
	//		- return 2
		State = Win;	
		return 2;
	}
	
	// if it got to here, it's just a normal reveal,
	// return 1	
	return 1;
}


// Checks if the board is in a win state.
// returns 1 if win-state, 0 if not.
char IsWin()
{
	// will go through the board, checking if all of the 2/3 point tiles have been revealed. Returns 0 if the have not
	for (int i = 0; i < 25; i++)
	{
		// if the tile is a 2 or 3 and has not been revealed, the game is not over
		// return 0;
		if ((board[i] & ValueBits)  > 1 && !(board[i] & RevealedBit))
			return 0;
	}
	
	// all point tiles have been revealed, game is won, return 1
	return 1;
}


// Function used in testing
void ChangeBoard()
{
	for (int i = 0 ;i < 25; i++)
	{
		board[i] = i+2;// % 4;
	}

	totalPoints = 12;
	Level = 34;
	LevelPoints = 56;

	
	#ifdef DEBUG_MAIN
	SCI0_TxString("\n\nBoard in Gameplay ChangeBoard:\n");
	char output[30];
	for (int i = 0; i < 10; i++)
	{
		sprintf(output, "Tile *(board + i) %d = %d\t", (int)i, (int)*(board + i)); //(board)[i]);	//*(*board+i));
		SCI0_TxString(output);	

		sprintf(output, "Tile (board + i) %d = %d\n", (int)i, (int)(board + i)); //(board)[i]);	//*(*board+i));
		SCI0_TxString(output);
	}
	#endif

}