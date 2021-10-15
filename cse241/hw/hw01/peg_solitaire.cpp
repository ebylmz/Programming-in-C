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
        vector<vector<CellState>> b;
        
        // There are 6 different type of boards. Select one of them 
        btype = select_board_type();
        initBoard(b, btype);
        
        do {
            showBoard(b);
            // Get the movement
            // Check and apply the movement
        } while (isGameOver(b));

        // Ask for new game
        cout << "Do you want to play again(Y/N): ";
        cin >> new_game;
    } while ('Y' == new_game || 'y' == new_game);

}

void getMovement (vector<vector<CellState>> & b, string & mov) {
    // Define the movement bound for given board
    char colBound = 'A' + b.size();
    char rowBound = '0' + b[0].size();

    do {
        cin >> mov;
        //! Check the movement type for triangle
    } while (! ('A' <= mov[0] && mov[0] <= colBound &&
             '0' <= mov[1] && mov[1] <= rowBound &&
             mov[2] == 'U' || mov[2] == 'D' || mov[2] == 'R' || mov[2] == 'L'));
}

//! NOT IMPLEMENTED YET
void applyMovement () {
    //  B4-R
}

//! NOT IMPLEMENTED YET
bool isValidMovement () {
    // The game continues until there are no pegs to move legally.
}

//! NOT IMPLEMENTED YET
bool isGameOver (vector<vector<CellState>> & board) {
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
           throwError("Undefined board type\nBoard was unable to created correctly", "createBoard");
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

BoardType select_board_type () {
    int r;

    printAllBoards();
    r = getChoice("Select Your board type(1...6): ", 1, 6);

    return static_cast<BoardType>(r);
}

void printAllBoards () {
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