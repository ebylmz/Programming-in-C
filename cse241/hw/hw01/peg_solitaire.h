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

void startHumanGame (vector<vector<CellState>> & board);

void startComputerGame (vector<vector<CellState>> & board);

void getMovement (const vector<vector<CellState>> & board, int & startRow, int & startCol, Direction & dir);
// Reads the movement from console and returns the movement as 
// indexes of the start point and the direction of movement
//? OPTIMIZATION NEEDED

Direction getDirection (string & movement);
// Returns the Obtained direction information inside of the movement 

string dirToStr (Direction dir);

int applyMovement (vector<vector<CellState>> & b, int startRow, int startCol, Direction dir);
// Applies the movement, for invalid operation returns EXIT_FAILURE

void moveUp (int & jumpRow, int & targetRow);
void moveDown (int & jumpRow, int & targetRow);
void moveRight (int & jumpCol, int & targetCol);
void moveLeft (int & jumpCol, int & targetCol);
// Pre: jump and target Cells are should be equal to start Cell

int getMoveCell (int startRow, int startCol, Direction dir, int & jumpRow, int & jumpCol, int & targetRow, int & targetCol);
//? Produce movement cell ..............

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol);
// Checks if given board cell is movable or not

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol, Direction dir);
// Checks if given board cell is movable or not for specific direction

bool isDiagonalMovement (Direction dir);

bool isGameOver (const vector<vector<CellState>> & board);

int calculateScore (vector<vector<CellState>> & board);

/***********************************************************************************
 * Board Start
 **********************************************************************************/

void initBoard (vector<vector<CellState>>& b, BoardType btype);
//! NOT IMPLEMENTED YET

void createBoard (vector<vector<CellState>> & b, int row, int col, CellState c);
// Creates a board as given dimension and initiliaze all the board with c

void showBoard (const vector<vector<CellState>> & b);
// Prints the curent status of board

bool isInBoard (const vector<vector<CellState>> & b, int row, int col);
//! IMPLEMENTED FOR NON-TRIANGULAR BOARD
// Checks if given row and col is inside of the board

bool isTriangularBoard (const vector<vector<CellState>> & b);

void printAllBoardTypes ();
// Prints 6 different type of boards

/***********************************************************************************
 * Utility
 **********************************************************************************/
void throwError (string prompt);

void throwError (string prompt, string location);

bool getChoice (string prompt);
// Takes an prompt for Y/N question, and returns it's answer

int getChoice (string prompt, int lb, int ub);
//? Takes an prompt and returns it's answer 

int getChoice (string in_prompt, string err_prompt, int lb, int ub);
//? Takes an prompt and returns it's answer 

bool isNumber (char c);

bool isLetter (char c);

char upperCase (char c);

void convertUpperCase (string & s);

#endif 