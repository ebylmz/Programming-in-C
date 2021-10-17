// http://recmath.org/pegsolitaire/

#ifndef peg_solitaire
#define peg_solitaire

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;

typedef enum {empty, peg, out} CellState;

typedef enum {french = 1, german = 2, asymmetrical = 3, english = 4, diamond = 5, triangular = 6} BoardType;

typedef enum {up_d, down_d, right_d, left_d, upRight_d, upLeft_d, downRight_d, downLeft_d, none_d} Direction;

/***********************************************************************************
 * Game Management
 **********************************************************************************/

void pegStart ();

void getMovement (const vector<vector<CellState>> & board, int & startRow, int & startCol, Direction & dir);
// Reads the movement from console and returns the movement as 
// indexes of the start point and the direction of movement

Direction getDirection (string & movement);
// Returns the Obtained direction information inside of the movement 

bool isDiagonalMovement (Direction dir);

int applyMovement (vector<vector<CellState>> & b, int startRow, int startCol, Direction dir);
// Applies the movement, for invalid operation returns EXIT_FAILURE

int getMoveCell (int startRow, int startCol, Direction dir, int & jumpRow, int & jumpCol, int & targetRow, int & targetCol);
//? Produce movement cell ..............

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol);
// Checks if given board cell is movable or not

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol, Direction dir);
// Checks if given board cell is movable or not for specific direction

bool isGameOver (vector<vector<CellState>> & board);
/***********************************************************************************
 * Board Start
 **********************************************************************************/

void initBoard (vector<vector<CellState>>& b, BoardType btype);
//! NOT IMPLEMENTED YET

void createBoard (vector<vector<CellState>> & b, int row, int col, CellState c);
// Creates a board as given dimension and initiliaze all the board with c

void showBoard (const vector<vector<CellState>> & b);
// Prints the curent status of board

BoardType selectBoardType ();

bool isInBoard (const vector<vector<CellState>> & b, int row, int col);
// Checks if given row and col is inside of the board

bool isTriangularBoard (const vector<vector<CellState>> & b);

void printAllBoardTypes ();
// Prints 6 different type of boards

/***********************************************************************************
 * Utility
 **********************************************************************************/
void throwError (string prompt);

void throwError (string prompt, string location);

int getChoice (string prompt, int lb, int ub);

int getChoice (string in_prompt, string err_prompt, int lb, int ub);

char upperCase (char c);

void convertUpperCase (string & s);

#endif 