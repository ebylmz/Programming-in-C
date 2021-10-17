#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "peg_solitaire.h"

using namespace std;  

/***********************************************************************************
 * Game Management
 **********************************************************************************/

void pegStart () {
    char new_game;
    BoardType btype;

    // There are two types of game: human or computer

    do {
        vector<vector<CellState>> board;
        int r = EXIT_SUCCESS;

        // There are 6 different type of boards. Select one of them 
        btype = selectBoardType();
        initBoard(board, btype);

        do {
            int startRow, startCol;
            Direction dir;

            if (r == EXIT_FAILURE) {
                throwError("Invalid Move");
                r = EXIT_SUCCESS;
            }
            else
                showBoard(board);

            getMovement(board, startRow, startCol, dir);
            r = applyMovement(board, startRow, startCol, dir);
        } while (r == EXIT_FAILURE || isGameOver(board) == false);

        // Ask for new game
        cout << "Do you want to play again(Y/N): ";
        cin >> new_game;
    } while ('Y' == new_game || 'y' == new_game);

}

void getMovement (const vector<vector<CellState>> & board, int & startRow, int & startCol, Direction & dir) {
    string mov;
    bool err;
    
    cout << "\nMovement: ";
    cin >> mov;
    convertUpperCase(mov);

    if (mov.length() <= 5 && mov[2] == '-') {
        startCol = mov[0] - 'A';
        startRow = mov[1] - '1';
        dir = getDirection(mov);
    }
    // throwError(".................", "getMovement");

    // Return ...
}

Direction getDirection (string & movement) {
    Direction dir = none_d;

    if (movement.length() == 4 || movement.length() == 5) {
        int x = 0, y = 0;
        bool err = false;
        
        for (int i = 3; i < movement.length() && err == false; ++i) {
            switch (movement[i]) {
                case 'U':
                    ++y;
                    break;
                case 'D':
                    --y;
                    break;
                case 'R':
                    ++x;
                    break;
                case 'L':
                    --x;
                    break;
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

int applyMovement (vector<vector<CellState>> & board, int startRow, int startCol, Direction dir) {
    int r = EXIT_FAILURE;

    // up/down movements are invalid for triangular board 
    // diagonal movements are invalid for all the boards except triangular board 
    if (dir != none_d &&
        ((isDiagonalMovement(dir) && isTriangularBoard(board)) ||
         (!isDiagonalMovement(dir) && !isTriangularBoard(board)))) {

        int jumpRow, jumpCol, targetRow, targetCol;
        r = getMoveCell(startRow, startCol, dir, jumpRow, jumpCol, targetRow, targetCol);

        // Check if movement is exceed board
        if (isMovable(board, startRow, startCol, dir)) {
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
    
    jumpRow = targetRow = startRow;
    jumpCol = targetCol = startCol;
    switch (dir) {
        case up_d:
            --jumpRow;
            targetRow -= 2;
            break;
        case down_d:
            ++jumpRow;
            targetRow += 2;
            break;
        case left_d:
            --jumpCol;
            targetCol -= 2;
            break;
        case right_d:
            ++jumpCol;
            targetCol += 2;
            break;
        case upRight_d:
            --jumpRow;
            ++jumpCol;
            targetRow -= 2;
            targetCol += 2;
            break;
        case upLeft_d:
            --jumpRow;
            --jumpCol;
            targetRow -= 2;
            targetCol -= 2;
            break;
        case downLeft_d:
            ++jumpRow;
            --jumpCol;
            targetRow += 2;
            targetCol -= 2;
            break;
        case downRight_d:
            ++jumpRow;
            ++jumpCol;
            targetRow += 2;
            targetCol += 2;
        default:
            r = EXIT_FAILURE;
    }

    return r;
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
        // For non-triangular boards try the for main direction
        r = isMovable(board, startRow, startCol, up_d)   ||
            isMovable(board, startRow, startCol, down_d) ||
            isMovable(board, startRow, startCol, left_d) ||
            isMovable(board, startRow, startCol, right_d);
    }

    return r;
}

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol, Direction dir) {
    int r, v, jumpRow, jumpCol, targetRow, targetCol;
    
    if (dir != none_d &&
        ((isDiagonalMovement(dir) && isTriangularBoard(board)) ||
         (!isDiagonalMovement(dir) && !isTriangularBoard(board)))) {
        
        v = getMoveCell(startRow, startCol, dir, jumpRow, jumpCol, targetRow, targetCol);
        
        r = v == EXIT_SUCCESS                                                           && 
            isInBoard(board, startRow, startCol) && board[startRow][startCol] == peg    &&
            isInBoard(board, jumpRow, jumpCol) && board[jumpRow][jumpCol] == peg        &&
            isInBoard(board, targetRow, targetCol) && board[targetRow][targetCol] == empty;
    } 
    return r;
}

bool isDiagonalMovement (Direction dir) {
    return dir == upRight_d || dir == upLeft_d || dir == downRight_d || dir == downLeft_d;
}

bool isGameOver (vector<vector<CellState>> & board) {
    bool r;
    
    // The game continues until there are no pegs to move legally.
    for (int i = 0, r = true; i < board.size() && r == true; ++i)
        for (int j = 0; j < board[i].size() && r == true; ++j)
            r = isMovable(board, i, j);

    return r;
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

BoardType selectBoardType () {
    int r;

    printAllBoardTypes();
    r = getChoice("Select Your board type(1...6): ", 1, 6);

    return static_cast<BoardType>(r);
}


bool isInBoard (const vector<vector<CellState>> & b, int row, int col) {
    // Define the movement bound for given board
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

int getChoice (string prompt, int lb, int ub) {
    int r;
    
    cout << prompt << endl;    
    do {
        cout << ">> ";
        cin >> r; 
        if (r < lb || r > ub)
            cout << "Your choose should be min " << lb << " and max " << ub << endl;
    } while (r < 0 || r > 6);
    return r;    
}

int getChoice (string in_prompt, string err_prompt, int lb, int ub) {
    int r;    
        
    cout << in_prompt << endl;
    do {
        cout << ">> ";
        cin >> r; 
        if (r < lb || r > ub)
            cout << err_prompt << endl;
    } while (r < 0 || r > 6);
    return r;
}

char upperCase (char c) {
    return 'a' <= c && c <= 'z' ? 'A' + c - 'a' : c;
}

void convertUpperCase (string & s) {
    for (auto it = s.begin(); it != s.end(); ++it)
        *it = upperCase(*it); 
}