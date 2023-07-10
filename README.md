# Voltorb_game
## A recreation of the Voltorb minigame from Pokemon Soul-Silver in the form of an embedded device that I designed and programmed.

I have chosen to affectionately rename the game Boom-Boom since "Voltorm minigame from Pokemon Soul-Silver" was a mouthful.

- The PCB was designed to incorperates a 5x5 button matrix and have the game displayed on an OLED using I2C interfacing. 

- The Software component was designed to be used with the ATmega328P-P microchip and the SSD1306 OLED.

- SSD1306, I2C, and sci libraries were all provided to me by my NAIT instructor, Simon Walker.


## Game description:
The game is displayed on the OLED as a "game board" of 25 tiles, arranged in a 5x5 grid.
Each tile on the grid begins each level blank and will contain a value of either a 1, 2, 3, or a bomb.
To the right of each row and below each column there will be: 
  - A line containing between 0 and 5 "ticks", indicating the amount of bombs in that row/column
  - A second line below that, there will be a 2-digit leading-zero number, indicating the sum total of the point tiles (1s, 2s, and 3s) in the given row/column


###Gameplay: 
The objective of the game is to reveal all of the tiles containing a 2 or a 3 in each round, while avoiding revealing any the bomb tiles. 
  - The player starts the game at level 1. 
  - Each round begins with all tiles hidden and the player has 1 point.
  - The player's Level-Points will be multiplied by the value of each point tile the player reveals.
  - If all of the 2's and 3's in a given round have been revealed, they: 
	* Have won the round. 
	* Move up a level.

  - If the player reveals a bomb, they: 
	* Have lost the round. 
	* Have their Level-Points fall down to 0.   
	* Drop down a level.
 
  - At the end of each round, the player's Level-Points will be added to their Total-Points and the board resets for the next round.  
  - The levels start at 1 and go up to 9, increasing in difficulty as the palyer moves up in levels.

###User Interface
The user is able to interact with the game through the 5x5 button matrix. Pressing a given button will select the corresponding tile in the game.
Once a tile is selected:
  - If a round is in progress, then it will reveal the tile underneath.
  - If the round is over and only one tile has been revealed, it will reveal all the remaining tiles.
  - If the round is over and all the remaining tiles have been revealed, it will start a new round.
  
E.g.: (Game with the tiles revealed)
```
        Boom-Boom
        Level: 2
        Total-Points: 127
        Level-Points: 36
        ______________________________________________
        |        |        |        |        |        | '
        |    1   |    2   |  Bomb  |    1   |    1   |  05
        |________|________|________|________|________|        
        |        |        |        |        |        | 
        |    1   |    1   |    1   |    2   |    1   |  06
        |________|________|________|________|________|
        |        |        |        |        |        | ''
        |  Bomb  |    1   |  Bomb  |    1   |    1   |  03
        |________|________|________|________|________|
        |        |        |        |        |        | ''
        |    1   |    3   |  Bomb  |    1   |  Bomb  |  05
        |________|________|________|________|________|
        |        |        |        |        |        | '
        |    1   |    1   |    1   |  Bomb  |    3   |  06
        |________|________|________|________|________|
          '                '''      '        '
             04       08       02       05       06
```
  
  





  
