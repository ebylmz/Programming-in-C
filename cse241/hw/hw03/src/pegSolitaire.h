
#ifndef pegSolitaire
#define pegSolitaire

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// #include <random>

using namespace std;

const int RETURN_SUCCESS =  0;  // return value for successfull execution
const int RETURN_FAILURE = -1;  // return value for unsuccessfull execution
const int RETURN_SUDO    = -2;  // return value for stopped execution by user

class PegSolitaire {
    public:
        // Constructors
        PegSolitaire (const char * fileName);
        // Starts with given board
        PegSolitaire (int boardType);
        // Starts with the specific board type (1 to 6)
        PegSolitaire ();

        enum class CellValue : char {peg = 'P', empty = '.', out = ' '};
        enum class Direction {none, up, down, right, left};
        enum class GameMode {undefined, computer, human};

        /* ======================== Movement ======================== */
        class Movement {
            public:
                Movement (int rowValue, int colValue, Direction dir);
                Movement ();

                void setRand (int n);
            private:
                int row;
                int col;
                Direction direction;
        };

        /* ======================== Cell ======================== */
        class Cell {
            public:
                // Constructors
                Cell (const string & cellCol, int cellRow, CellValue CellValue);
                Cell ();
                //! NOT IMPLEMENTED YET

                // Getters
                void getCell (string & cellCol, int & cellRow, CellValue & cellValue) const;
                CellValue getValue () const;
                string getCol () const;
                int getRow () const;

                // Setters
                void setCell (string cellCol, int cellRow, CellValue cellValue);
                void setValue (CellValue cellValue);
                void setCol (string cellCol);
                void setRow (int cellRow);

                int convertCellCol (const string & col) const;
                // String to int value
                string convertCellCol (int col) const;

            //* Private part cannot accessed even by the outer class
            private:

                // Cell position and value
                GameMode gameMode;
                string col;     // A, B, C, etc
                int row;        // 1, 2, 3, etc
                CellValue value;  // peg, empty, out
        };

        void startGame ();
        // Starts the pegSolitaire game

        Movement play ();
        // plays the current game for a single step and returns the movement that made.
        
        void play (string col, int row, Direction dir);
        // The second function takes a cell position and it plays the user.

        void playGame ();   // Computer Game
        // plays the game by asking the user the board type first then
        // automatically plays the game until it ends. 

        void getMovement (Movement & mov) const;
        
        int applyMovement (const Movement & mov);
        // Returns 0 for succesfull movement

        // Load & Save
        void load (const char * fileName);
        //! NOT IMPLEMENTED YET
        void save (const char * fileName) const;
        //! NOT IMPLEMENTED YET

        void displayBoard () const;
        //! NOT IMPLEMENTED YET

        bool isMovable (const Movement & mov) const;

        bool isGameOver () const;

        int getBoardSize () const;

        void PegSolitaire::printIntro () const;
        void PegSolitaire::printGameRules () const;
        void PegSolitaire::printGameResult (int score, int numberOfMovement) const;    //! movment number ?

    private:
        void setBoard ();
        void setBoard (int boardType);

        void setBoardFrench ();        
        void setBoardGerman ();        
        void setBoardAsymmetrical ();  
        void setBoardEnglish ();       
        void setBoardDiamond ();       
        void setBoardTriangular ();    

        void initBoard (int row, int col, CellValue initValue);
        //! NOT IMPLEMENTED YET
        // Allocates enough memory and initialize the board as initValue

        void fillBoard (int outStart, int outEnd, int inStart, int inEnd, CellValue v);
        // fills the given rectangular area with given value v
        
        int boardSize;
        // int boardType;
        GameMode gameMode;
        vector<vector<Cell>> board;
        // static vector<PegSolitaire> allGames;
};

// Helper Functions
void printAllBoardTypes ();

void printn (char c, int n);
bool getChoice (string prompt);
int getChoice (string prompt, int lb, int ub);
int getChoice (string inPrompt, string errPrompt, int lb, int ub);
int strToInt (const string & s);
void strUp (string & s);
bool isInRange (int n, int lb, int ub);


#endif