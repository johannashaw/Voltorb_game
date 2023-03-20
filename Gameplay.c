#include <stdio.h>
#include "Gameplay.h"
#include "Supplement.h"

// for accessing the board
#define Board(row, col) board[row * 5 + col]

// global var for the game board values, and which tiles are currently showing
char board[25], 
      showing[25];   // will

// 


// initializations that need to be done for the game
// give the game the function it needs to use for random number generation
void Boardinit()
{
   //   

}

//populate the game
void NewLevel(char points, char bombs)
{
   char i;
   // Add all the bombs
   for (i = 0; i < bombs; i++ )
   {
      board[i] = 0;
   }

   // Add all the points to the array
   while (points > 0)
   {

   }

   // Fill remainder's with 1s

   // Shuffle the array

   //
   
}

