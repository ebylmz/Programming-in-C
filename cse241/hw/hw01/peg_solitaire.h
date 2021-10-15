#ifndef peg_solitaire
#define peg_solitaire

using namespace std;

typedef enum {empty, peg, out} CellState;

typedef enum {french = 1, german = 2, asymmetrical = 3, english = 4, diamond = 5, triangular = 6} BoardType;


void pegStart ();
bool isGameOver (vector<vector<CellState>> & board);

void initBoard (vector<vector<CellState>>& b, BoardType btype);
void createBoard (vector<vector<CellState>> & b, int row, int col, CellState c);
void showBoard (const vector<vector<CellState>> & b);
BoardType select_board_type ();
void printAllBoards ();

// Takes an integer from console which is bounded as given inclusive lower and upper values  
void throwError (string prompt, string location);
int getChoice (string prompt, int lb, int ub);
int getChoice (string in_prompt, string err_prompt, int lb, int ub);

#endif 