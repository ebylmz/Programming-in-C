// http://recmath.org/pegsolitaire/

#ifndef peg_solitaire
#define peg_solitaire

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_SUDO    2

using namespace std;

enum class CellState {empty, peg, out};

enum class BoardType {french = 1, german = 2, asymmetrical = 3, english = 4, diamond = 5, triangular = 6};

enum class Direction {up, down, right, left, upRight, upLeft, downRight, downLeft, none};

/***********************************************************************************
 * Game Management
 **********************************************************************************/

void pegStart ();

void startHumanGame (vector<vector<CellState>> & board);

void startComputerGame (vector<vector<CellState>> & board);

int getMovement (int & startRow, int & startCol, Direction & dir);
// Reads the movement from console and returns the movement as 
// indexes of the start point and the direction of movement
//? OPTIMIZATION NEEDED

Direction getDirection (string & movement);
// Returns the Obtained direction information inside of the movement 

string dirToStr (Direction dir);
// Generate a string indicate an direction. Exp: U, D, L, R, UR ...

int applyMovement (vector<vector<CellState>> & b, int startRow, int startCol, Direction dir);
// Applies the movement, for invalid operation returns EXIT_FAILURE
//! NOT IMPLEMENTED FOR TRIANGULAR BOARD

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

bool isProperDirection (const vector<vector<CellState>> & board, Direction dir);

bool isTriangularMovement (Direction dir);

bool isDiagonalMovement (Direction dir);

bool isGameOver (const vector<vector<CellState>> & board);

int calculateScore (vector<vector<CellState>> & board);

/***********************************************************************************
 * Board Start
 **********************************************************************************/

void initBoard (vector<vector<CellState>>& b, BoardType btype);

void initBoardFrench(vector<vector<CellState>> & board);        

void initBoardGerman(vector<vector<CellState>> & board);        

void initBoardAsymmetrical(vector<vector<CellState>> & board);  

void initBoardEnglish(vector<vector<CellState>> & board);       

void initBoardDiamond(vector<vector<CellState>> & board);       

void initBoardTriangular(vector<vector<CellState>> & board);    

void createBoard (vector<vector<CellState>> & b, int row, int col, CellState c);
// Creates a board as given dimension and initiliaze all the board with c

void showBoard (const vector<vector<CellState>> & b);
// Prints the curent status of board

void showTriangularBoard (const vector<vector<CellState>> & b);
//! NOT IMPLEMENTED YET

void showNonTriangularBoard (const vector<vector<CellState>> & b);

bool isInBoard (const vector<vector<CellState>> & b, int row, int col);
// Checks if given row and col is inside of the board
//! NOT IMPLEMENTED FOR TRIANGULAR BOARD

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