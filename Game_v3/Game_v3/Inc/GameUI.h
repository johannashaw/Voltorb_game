/*
 * GameUI.h
 *
 * Created:		2023-04-15 5:46:28 PM
 *  Author:		Johanna Shaw
 * Description:	Controls basic UI to be displayed on the OLED screen.
 */  


#ifndef GAMEUI_H_
#define GAMEUI_H_
#endif /* GAMEUI_H_ */

// Comment in/out your desired game play orientation.

//#ifndef PORTRAIT_MODE
//#define PORTRAIT_MODE
//#endif

#ifndef LANDSCAPE_MODE
#define LANDSCAPE_MODE
#endif

void GameInitUI();

void AddPxGrid(char px, int iX, int iY);
void MakeGrid();
void ChangeTile(int row, int col, char symbol, char showing);

//
void SendSmolSymbol(int xStart, int yStart, char Symbol);
void DisplayPointSum(char value, int row, int col);
void DisplayBombLine(char bombs, int row, int col);
//
