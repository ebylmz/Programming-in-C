#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "peg_solitaire.h"

using namespace std;  

/***********************************************************************************
 * Game Management
 **********************************************************************************/

void pegStart () {
    int choice;
    bool playAgain;

    do {
        vector<vector<CellState>> board;
        BoardType btype;

        // Ask the board type and initialize the board
        printAllBoardTypes();
        btype = static_cast<BoardType>(getChoice("Select Your board type(1...6): ", 1, 6));
        initBoard(board, btype);

        // There are two types of game: human & computer
        cout << "0. Exit\n"
             << "1. Human Game\n"
             << "2. Computer Game\n"
             << "______________________" << endl;
        choice = getChoice("Select the game type: ", 0, 2);

        switch (choice) {
            case 0:
                playAgain = false;
                break;
            case 1:
                startHumanGame(board);
                break;
            case 2:
                startComputerGame(board);
                break;
        }
        
        if (choice != 0) {
            showBoard(board);
            // Calculate and print the score, ask for play again
            cout << "______________________" << endl
                 << "Score: " << calculateScore(board) << endl;

            playAgain = getChoice("Do you want to play again(Y/N): ");
        }
    } while (playAgain == true);
}

void startHumanGame (vector<vector<CellState>> & board) {
    int r;
    showBoard(board);

    do {
        int startRow, startCol;
        Direction dir;

        getMovement(board, startRow, startCol, dir);
        r = applyMovement(board, startRow, startCol, dir);

        if (r == EXIT_SUCCESS)
            showBoard(board);
        else
            throwError("Invalid Move");
    } while (r == EXIT_FAILURE || isGameOver(board) == false);
}

void startComputerGame (vector<vector<CellState>> & board) {
    srand(time(NULL));
    showBoard(board);
    
    do {
        Direction dir;
        int row, col; 

        do {
            // Select random position at the board
            row = rand() % board.size();
            col = rand() % board[0].size(); 

            // Select a proper random direction
            if (isTriangularBoard(board))
                dir = static_cast<Direction>((rand() % 4) + 4);
            else
                dir = static_cast<Direction>(rand() % 4);
        } while (isMovable(board, row, col, dir) == false);
        
        // Print the movement made by computer
        cout << "Movement: " << static_cast<char>('A' + col) << static_cast<char>('1' + row) << '-' << dirToStr(dir) << endl;

        applyMovement(board, row, col, dir);
        showBoard(board);
    } while (isGameOver(board) == false);
}

void getMovement (const vector<vector<CellState>> & board, int & startRow, int & startCol, Direction & dir) {
    string mov;
    bool err;

    do {
        err = true;

        cout << "\nMovement: ";
        cin >> mov;
        convertUpperCase(mov);

        // Check  movement entered in a proper format
        if ((mov.length() == 4 || mov.length() == 5) && isLetter(mov[0]) && isNumber(mov[1]) && mov[2] == '-') {
            startCol = mov[0] - 'A';
            startRow = mov[1] - '1';

            dir = getDirection(mov);

            if (dir != none_d) err = false;
        }
        
        if (err == true) 
            throwError("Invalid movement format");
    } while (err == true); 
}

Direction getDirection (string & movement) {
    Direction dir = none_d;

    if (movement.length() == 4 || movement.length() == 5) {
        int x = 0, y = 0;
        bool err = false;
        
        /*  To find the direction, use 1x1 cordinate system.
            If given directions resulted in at orijin or out of cordinate system,
            then given directions are invalid. 
        */ 
        for (int i = 3; i < movement.length() && err == false; ++i) {
            switch (movement[i]) {
                case 'U':
                    ++y; break;
                case 'D':
                    --y;
                    break;
                case 'R':
                    ++x; break;
                case 'L':
                    --x; break;
                default:
                    err = true;
            }
        } 

        if (err == false) {
            if (x == 0 && y == 1)
                dir = up_d;
            else if (x == 0 && y == -1)
                dir = down_d;
            else if (x == 1 && y == 0)
                dir = right_d;
            else if (x == -1 && y == 0)
                dir = left_d;
            else if (x == 1 && y == 1)
                dir = upRight_d;
            else if (x == -1 && y == 1)
                dir = upLeft_d;
            else if (x == 1 && y == -1)
                dir = downRight_d;
            else if (x == -1 && y == -1)
                dir = downLeft_d;
        }
    }

    return dir;
}

string dirToStr (Direction dir) {
    string s;

    switch (dir) {
        case up_d:
            s = "U";  break;
        case down_d:
            s = "D";  break;
        case left_d:
            s = "L";  break;
        case right_d:
            s = "R";  break;
        case upRight_d:
            s = "UR"; break;
        case upLeft_d:
            s = "UL"; break;
        case downLeft_d:
            s = "DL"; break;
        case downRight_d:
            s = "DR"; break;
        default:
            s = ""; //!    
    }
    return s;
}

int applyMovement (vector<vector<CellState>> & board, int startRow, int startCol, Direction dir) {
    int r = EXIT_FAILURE;

    // up/down movements are invalid for triangular board 
    // diagonal movements are invalid for all the boards except triangular board 
    if (dir != none_d &&
        ((isDiagonalMovement(dir) && isTriangularBoard(board)) ||
         (!isDiagonalMovement(dir) && !isTriangularBoard(board)))) {

        // Check if movement is exceed board
        if (isMovable(board, startRow, startCol, dir)) {
            int jumpRow, jumpCol, targetRow, targetCol;
            getMoveCell(startRow, startCol, dir, jumpRow, jumpCol, targetRow, targetCol);

            // Apply movement
            board[startRow][startCol] = empty;
            board[jumpRow][jumpCol] = empty;
            board[targetRow][targetCol] = peg;
            r = EXIT_SUCCESS;

            cout << "_____________________________" << endl;
            cout << "start  " << '[' << startRow << ", " << startCol << ']' << endl;
            cout << "jump   " << '[' << jumpRow << ", " << jumpCol << ']' << endl;
            cout << "target " << '[' << targetRow << ", " << targetCol << ']' << "" << endl;
        }
    }
    return r;
}

int getMoveCell (int startRow, int startCol, Direction dir, int & jumpRow, int & jumpCol, int & targetRow, int & targetCol) {
    int r = EXIT_SUCCESS;
    
    // Pre condition for move... functions
    jumpRow = targetRow = startRow;
    jumpCol = targetCol = startCol;

    switch (dir) {
        case up_d:
            moveUp(jumpRow, targetRow);    break;
        case down_d:
            moveDown(jumpRow, targetRow);  break;
        case left_d:
            moveLeft(jumpCol, targetCol);  break;
        case right_d:
            moveRight(jumpCol, targetCol); break;
        case upRight_d:
            moveUp(jumpRow, targetRow);
            moveRight(jumpCol, targetCol); break;
        case upLeft_d:
            moveUp(jumpRow, targetRow);
            moveLeft(jumpCol, targetCol);  break;
        case downLeft_d:
            moveDown(jumpRow, targetRow);
            moveLeft(jumpCol, targetCol);  break;
        case downRight_d:
            moveDown(jumpRow, targetRow);
            moveRight(jumpCol, targetCol); break;
        default:
            r = EXIT_FAILURE;
    }

    return r;
}

void moveUp (int & jumpRow, int & targetRow) {
    --jumpRow;
    targetRow -= 2;
}

void moveDown (int & jumpRow, int & targetRow) {
    ++jumpRow;
    targetRow += 2;
}

void moveRight (int & jumpCol, int & targetCol) {
    ++jumpCol;    
    targetCol += 2;    
}

void moveLeft (int & jumpCol, int & targetCol) {
    --jumpCol;    
    targetCol -= 2;    
}

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol) {
    bool r;
    if (isTriangularBoard(board)) {
        // For triangular board just try diagonal movements
        r = isMovable(board, startRow, startCol, upLeft_d)   ||
            isMovable(board, startRow, startCol, upRight_d)  ||
            isMovable(board, startRow, startCol, downLeft_d) ||
            isMovable(board, startRow, startCol, downRight_d);
    }
    else {
        // For other boards try the 4 main direction
        r = isMovable(board, startRow, startCol, up_d)   ||
            isMovable(board, startRow, startCol, down_d) ||
            isMovable(board, startRow, startCol, left_d) ||
            isMovable(board, startRow, startCol, right_d);
    }

    return r;
}

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol, Direction dir) {
    int r; 
    
    if (dir != none_d && 
        ((isDiagonalMovement(dir) && isTriangularBoard(board)) ||
         (!isDiagonalMovement(dir) && !isTriangularBoard(board)))) {
        int v, jumpRow, jumpCol, targetRow, targetCol;
        
        v = getMoveCell(startRow, startCol, dir, jumpRow, jumpCol, targetRow, targetCol);
        
        r = v == EXIT_SUCCESS                       &&
            isInBoard(board, startRow, startCol)    && 
            board[startRow][startCol] == peg        &&
            isInBoard(board, jumpRow, jumpCol)      && 
            board[jumpRow][jumpCol] == peg          &&
            isInBoard(board, targetRow, targetCol)  && 
            board[targetRow][targetCol] == empty;
    }
    else
        r = false; 
    return r;
}

bool isDiagonalMovement (Direction dir) {
    return dir == upRight_d || dir == upLeft_d || dir == downRight_d || dir == downLeft_d;
}

bool isGameOver (const vector<vector<CellState>> & board) {
    bool r = true;
    
    // The game continues until there are no pegs to move legally.
    for (int i = 0; i < board.size() && r == true; ++i)
        for (int j = 0; j < board[i].size() && r == true; ++j)
            if (board[i][j] == peg)
                r = !isMovable(board, i, j);

    return r;
}

int calculateScore (vector<vector<CellState>> & board) {
    int score = 0;

    for (int i = 0; i < board.size(); ++i) 
        for (auto it = board[i].begin(); it != board[i].end(); ++it)
            if (*it == peg)
                ++score;

    return score;
}

/***********************************************************************************
 * Board Start
 **********************************************************************************/

//! NOT IMPLEMENTED YET
void initBoard (vector<vector<CellState>>& b, BoardType btype) {
    //! Board are not created yet
    switch (btype) {
        case french:
            createBoard(b, 7, 7, peg);
            b[0][1] = b[0][0] = b[1][0] = out;
            b[0][5] = b[0][6] = b[1][6] = out;
            b[5][0] = b[6][0] = b[6][1] = out;
            b[5][6] = b[6][5] = b[6][6] = out;
            b[2][3] = empty;
            break;
        case german:
            createBoard(b, 9, 9, peg);
            // hole b[4][4]
            break;
        case asymmetrical:
            createBoard(b, 8, 8, peg);
            // hole b[4][3]
            break;
        case english:
            createBoard(b, 7, 7, peg);
            // hole b[3][3]
            break;
        case diamond:
            createBoard(b, 9, 9, peg);
            // hole b[4][4]
            break;
        case triangular:
            createBoard(b, 5, 9, peg);
            // hole b[0][4]
            break;
        default:
           throwError("Undefined board type. Board was unable to create correctly", "createBoard");
    }
}

void createBoard (vector<vector<CellState>> & b, int row, int col, CellState c) {
    b.resize(row);
    for (int i = 0; i < row; ++i) {
        b[i].resize(col);
        for (int j = 0; j < col; ++j)
            b[i][j] = c;
    }
}

void showBoard (const vector<vector<CellState>> & b) {
    // Print column order
    cout << "\n    ";
    for (int j = 0; j < b[0].size(); ++j)
        cout << static_cast<char>('A' + j) << ' ';
    cout << "\n\n";

    for (int i = 0; i < b.size(); ++i) {
        // Print the row order
        cout << 1 + i << "   ";
        for (auto it = b[i].begin(); it != b[i].end(); ++it) {
            switch (*it) {
                case peg:
                    cout << "P";
                    break;
                case empty:
                    cout << ".";
                    break;
                case out:
                    cout << " ";
                    break;
            }
            cout << " ";
        }
        cout << endl;
    }
}

bool isInBoard (const vector<vector<CellState>> & b, int row, int col) {
    // Define the movement bound for given board
    //! this is not valid (b[0].size for triangle)
    return  0 <= row && row < b.size()      &&
            0 <= col && col < b[0].size()   &&
            b[row][col] != out;
}

bool isTriangularBoard (const vector<vector<CellState>> & b) {
    return b.size() == 5 && b[0].size() == 9;
}


void printAllBoardTypes () {
    cout    << "1- French\n"
            << "---------------------\n"
            << "    P P P\n"
            << "  P P P P P\n"
            << "P P P . P P P\n"
            << "P P P P P P P\n"
            << "P P P P P P P\n"
            << "  P P P P P\n"
            << "    P P P\n"
            << "\n\n";

    cout    << "2- German\n"
            << "---------------------\n"
            << "      P P P\n"
            << "      P P P\n"
            << "      P P P\n"
            << "P P P P P P P P P\n"
            << "P P P P . P P P P\n"
            << "P P P P P P P P P\n"
            << "      P P P\n"
            << "      P P P\n"
            << "      P P P\n"
            << "\n\n";

    cout    << "3- Asymmetrical\n"
            << "---------------------\n"
            << "    P P P\n"
            << "    P P P\n"
            << "    P P P\n"
            << "P P P P P P P P\n"
            << "P P P . P P P P\n"
            << "P P P P P P P P\n"
            << "    P P P\n"
            << "    P P P\n"
            << "    P P P\n"
            << "\n\n";
    
    cout    << "4- English\n"
            << "---------------------\n"
            << "    P P P\n"
            << "    P P P\n"
            << "P P P P P P P\n"
            << "P P P . P P P\n"
            << "P P P P P P P\n"
            << "    P P P\n"
            << "    P P P\n"
            << "\n\n";

    cout    << "5- Diamond\n"
            << "---------------------\n"
            << "        P\n"
            << "      P P P\n"
            << "    P P P P P\n"
            << "  P P P P P P P\n"
            << "P P P P . P P P P\n"
            << "  P P P P P P P\n"
            << "    P P P P P\n"
            << "      P P P\n"
            << "        P\n"
            << "\n\n";

    cout    << "6- Triangle\n"
            << "---------------------\n"
            << "        .\n"
            << "      P   P\n"
            << "    P   P   P\n"
            << "  P   P   P   P\n"
            << "P   P   P   P   P\n"
            << "\n\n";
}

/***********************************************************************************
 * Utility
 **********************************************************************************/

void throwError (string prompt) {
    cout << "[!] " << prompt << endl;
}

void throwError (string prompt, string location) {
    cout << "[!] " << prompt << "(" << location << ")" << endl;
}

bool getChoice (string prompt) {
    char c;

    cout << prompt;
    for (cin >> c, c = upperCase(c); c != 'Y' && c != 'N'; cin >> c, c = upperCase(c))
        cout << "Please select a proper choose: ";

    return c == 'Y' ? true : false;
}

int getChoice (string prompt, int lb, int ub) {
    int r;
    
    cout << prompt;    
    for (cin >> r; r < lb || r > ub; cin >> r)
        cout << "Please select a proper choose: ";

    return r;    
}

int getChoice (string inPrompt, string errPrompt, int lb, int ub) {
    int r;    

    cout << inPrompt;
    for (cin >> r; r < lb || r > ub; cin >> r)
        cout << errPrompt << endl
             << "Please select a proper choose: ";
    return r;
}

bool isNumber (char c) {
    return '0' <= c && c <= '1';
}

bool isLetter (char c) {
    c = upperCase(c);
    return 'A' <= c && c <= 'Z';
}

char upperCase (char c) {
    return 'a' <= c && c <= 'z' ? 'A' + c - 'a' : c;
}

void convertUpperCase (string & s) {
    for (auto it = s.begin(); it != s.end(); ++it)
        *it = upperCase(*it); 
}