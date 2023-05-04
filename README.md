# Voltorb_game
## A recreation of the Voltorb minigame from Pokemon Soul-Silver

I have chosen to affectionately rename the game Boom-Boom.

- The PCB was designed to incorperates a 5x5 button matrix and have the game displayed on an OLED using I2C interfacing. 

- The Software component was designed to be used with the ATmega328P-P microchip and the SSD1306 OLED.

- SSD1306, I2C, timer, atd, and sci libraries were all provided to me by Simon Walker.


Game description:
  The game contains a "game board" filled with 25 tiles, arranged in a 5x5 grid. 
  Each tile on the grid can contain either a 1, 2, 3, or a bomb.
  To the right of each row and below each column: 
    - there will be a line containing between 0 and five "ticks", indicating the amount of bombs in the row/column
    - below that line there will be a 2-digit number, indicating the sum total of the 1s, 2s, and 3s in the row/column
    
  The objective of the game is to select all of the tiles containing a 2 or a 3, while avoiding the bomb tiles. Points 
  for a given level (Level-Points) are determined by multiplying the numbered tiles together. If you select a bomb, your Level-Points 
  falls down to 0. Your Level-Points will be added to your Total-Points at the end of each level and then your 
  Level-Points will be reset to 1. Levels range from 1 to 9 and increase in difficulty.
  
  E.g.:
        * Game with the tiles revealed *
```
        Level-Points: 36
        ______________________________________________
        |        |        |        |        |        | '
        |    1   |    2   |    B   |    1   |    1   |  05
        |________|________|________|________|________|        
        |        |        |        |        |        | 
        |    1   |    1   |    1   |    2   |    1   |  06
        |________|________|________|________|________|
        |        |        |        |        |        | ''
        |    B   |    1   |    B   |    1   |    1   |  03
        |________|________|________|________|________|
        |        |        |        |        |        | ''
        |    1   |    3   |    B   |    1   |    B   |  05
        |________|________|________|________|________|
        |        |        |        |        |        | '
        |    1   |    1   |    1   |    B   |    3   |  06
        |________|________|________|________|________|
          '                 '''      '        '
           04       08       02       05       06
```
  
  
The user is able to interact with the game through the 5x5 button matrix, pressing a given button will select the corresponding tile in the game.





  
