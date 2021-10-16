// http://recmath.org/pegsolitaire/

#ifndef peg_solitaire
#define peg_solitaire

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;

typedef enum {empty, peg, out} CellState;

typedef enum {french = 1, german = 2, asymmetrical = 3, english = 4, diamond = 5, triangular = 6} BoardType;

typedef struct {
    int row,    // row
        col;    // coloumn
} Cell;

typedef struct {
    Cell source,
         jump,
         target;
} Movement;

/***********************************************************************************
 * Game Management
 **********************************************************************************/

void pegStart ();

void getMovement (const vector<vector<CellState>> & board, Movement & m);

bool isValidMovement (const vector<vector<CellState>> & board, Movement & m);

void applyMovement (vector<vector<CellState>> & b, Movement & mov);

bool isValidMovement (const vector<vector<CellState>> & board, Movement & m);

bool isGameOver (vector<vector<CellState>> & board);
//! NOT IMPLEMENTED YET

/***********************************************************************************
 * Board Start
 **********************************************************************************/

void initBoard (vector<vector<CellState>>& b, BoardType btype);
//! NOT IMPLEMENTED YET

void createBoard (vector<vector<CellState>> & b, int row, int col, CellState c);

void showBoard (const vector<vector<CellState>> & b);

BoardType selectBoardType ();

bool isInBoard (const vector<vector<CellState>> & b, int row, int col);

bool isTriangularBoard (const vector<vector<CellState>> & b);

void printAllBoardTypes ();

/***********************************************************************************
 * Utility
 **********************************************************************************/
void throwError (string prompt);

void throwError (string prompt, string location);

int getChoice (string prompt, int lb, int ub);

int getChoice (string in_prompt, string err_prompt, int lb, int ub);

#endif 