
#define RevealedBit 0x08
#define ValueBits 0x07
#define PredictBit_0 0x10
#define PredictBit_1 0x20
#define PredictBit_2 0x40
#define PredictBit_3 0x80

// getters to pass gameplay variables
char* GetArray_pt();
int* GetTotalPoints_pt();
int* GetLevel_pt();
int* GetLevelPoints_pt();


void  Boardinit();

void NewLevel();
int TryReveal(int row, int col);      
char IsWin();



void ChangeBoard();
// 0110 1000 1000
// 1000 1000

// 0110 1000 1001
// 0110