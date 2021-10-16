#include <iostream>
#include <vector>
#include <string>
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
        Movement mov;

        // There are 6 different type of boards. Select one of them 
        btype = selectBoardType();
        initBoard(board, btype);
        
        do {
            showBoard(board);
            getMovement(board, mov);
            applyMovement(board, mov);
        } while (isGameOver(board));

        // Ask for new game
        cout << "Do you want to play again(Y/N): ";
        cin >> new_game;
    } while ('Y' == new_game || 'y' == new_game);

}

void getMovement (const vector<vector<CellState>> & board, Movement & mov) {
    bool err;

    do {
        string s;
        cout << "\nMovement: ";
        cin >> s;
        
        if (s.length() == 4 || s.length() == 5) {
            err = false;
            
            mov.target.row = mov.jump.row = mov.source.row = s[0] - 'A';
            mov.target.col = mov.jump.col = mov.source.col = s[1] - '1';

            //! NOT IMPLEMENTED YET
            // up/down movements are invalid for triangular board 
            // diagonal movements are invalid for all the boards except triangular board 

            for (int i = 3; i < s.length() && err == false; ++i) {
                if (i == 4 && s[3] == s[4])
                    err = true;
                else {
                    switch (s[i]) {
                        case 'U':
                        case 'u':
                            --mov.jump.row;  
                            mov.target.row -= 2;  
                            break;
                        case 'D':
                        case 'd':
                            ++mov.jump.row;  
                            mov.target.row += 2;  
                            break;
                        case 'R':
                        case 'r':
                            ++mov.jump.col;
                            mov.target.col += 2;
                            break;
                        case 'L':
                        case 'l':
                            --mov.jump.col;
                            mov.target.col -= 2;
                            break;
                        default:
                            err = true;
                    }
                }
            }
        }
        else
            err = true;
        
        if (err == true)
            throwError(".................", "getMovement");
    } while (err == true || isValidMovement(board, mov) == false);
}

bool isValidMovement (const vector<vector<CellState>> & board, Movement & m) {
    return
        isInBoard(board, m.source.row, m.source.col)  &&
        board[m.source.row][m.source.col] == peg      &&
        isInBoard(board, m.jump.row, m.jump.col)      &&
        board[m.jump.row][m.jump.col] == peg          &&
        isInBoard(board, m.target.row, m.target.col)  && 
        board[m.target.row][m.target.col] == empty    ;
}

void applyMovement (vector<vector<CellState>> & b, Movement & mov) {
    // First check the movement direction is valid for the current board
    b[mov.source.row][mov.source.col] = empty;    
    b[mov.jump.row][mov.jump.col]     = empty;    
    b[mov.target.row][mov.target.col] = peg;    
}

//! NOT IMPLEMENTED YET
bool isGameOver (vector<vector<CellState>> & board) {
    // The game continues until there are no pegs to move legally.
    bool r;
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
    cout << "    ";
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
    cout << "[!]" << prompt << endl;
}

void throwError (string prompt, string location) {
    cout << "[!]" << prompt << "(" << location << ")" << endl;
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
