/*
 * Gameplay.h
 *
 * Created: 2023-04-15 8:56:32 PM
 *  Author: Johanna Shaw
 
 * Purpose: Facilitates all game functionality. The programmer only needs to initialize the board and then use 
			TryReveal to interact with the game. The board, Point Total, Level Points, and Level can be accessed
			through their pointers.
 */ 

#define RevealedBit 0x08
#define ValueBits 0x07
#define PredictBit_0 0x10
#define PredictBit_1 0x20
#define PredictBit_2 0x40
#define PredictBit_3 0x80

// NOTE: PredictBits are reserved for the option to allow tile prediction, but this function has not yet been implemented.

// getters to pass gameplay variables
char* GetArray_pt();
int* GetTotalPoints_pt();
int* GetLevel_pt();
int* GetLevelPoints_pt();

// Initializes game board and game variables. Also starts the game at level 1.
void  Boardinit();


// Takes a value for the row and column and uses them to check what to do next in the game
// Returns:
//		0 => no change
//		1 => smol change		(one tile)
//		2 => win/lose change	(one tile and indicate win/lose)
//		3 => big change			(Flip all of the tiles)
//		4 => New level
int TryReveal(int row, int col);  

// Starts a new level and generates a new board.
// Levels start at 1 and go up to 9.
// If the player lost the last level, they will move down a level up until level 1.
// If the player won the last level, they will move up a level until level 9.
void NewLevel();    

// Checks the game for a win state, is currently only used locally.
char IsWin();



// used in testing.
void ChangeBoard();