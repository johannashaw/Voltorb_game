#include "Supplement.h"

#include <time.h>   // for the random numbers
#include <stdio.h>

time_t t;

void RandomInit()
{
    time(&t);
   
   /* Intializes random number generator */
   //srand(2);
}

// generates a random character between min inclusive and max exclusive
char RandChar(char min, char max)
{
    //return rand() % (max - min) + min; 
    return (char)(time(&t) % (max - min) + min); 
}