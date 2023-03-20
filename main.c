#include <stdio.h>
#include "Gameplay.h"
#include "Supplement.h"


// command for installing gcc:
//  git clone git://gcc.gnu.org/git/gcc.git


void main()
{    
    //printf("hello world\n");
    //printf(" 32 && 5 = %d ", 32 && 5);
    
    for (int i = 0; i < 30; i++)
    {
        printf('%d\n', RandChar(1, 2));
    }
}