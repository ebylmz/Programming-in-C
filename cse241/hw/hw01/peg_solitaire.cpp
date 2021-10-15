#include <iostream>
#include <vector>
#include <string>
#include "peg_solitaire.h"

using namespace std;    // Should I put this in header file 

void peg_start () {
    char new_game;
    BoardType btype;

    // There are two types of game: human or computer

    do {
        // There are 6 different type of boards. Select one of them 
        vector<vector<CellState>> b;
        btype = select_board_type();
        initBoard(b, btype);
        
        do {
            // Get the movement
            // Check and apply the movement
            // Check if game is over
        } while (is_game_over(b, btype));

        // Ask for new game
        cout << "Do you want to play again(Y/N): ";
        cin >> new_game;
    } while ('Y' == new_game || 'y' == new_game);

}

BoardType select_board_type () {
    int r;

    u_print_boards();
    get_choice("Select Your board type(1...6): ", 1, 6);

    return static_cast<BoardType>(r);
}

// Takes the type of board
void initBoard (vector<vector<CellState>>& b, int type) {
    //! Board are not created yet
    switch (type) {
        case french:
            create_board(b, 7, 7, peg);
            b[0][1] = b[0][0] = b[1][0] = out;
            b[0][5] = b[0][6] = b[1][6] = out;
            b[5][0] = b[6][0] = b[6][1] = out;
            b[5][6] = b[6][5] = b[6][6] = out;
            // hole b[2][3]
            b[2][3] = hole;
            break;
        case german:
            create_board(b, 9, 9, peg);
            // hole b[4][4]
            break;
        case asymmetrical:
            create_board(b, 8, 8, peg);
            // hole b[4][3]
            break;
        case english:
            create_board(b, 7, 7, peg);
            // hole b[3][3]
            break;
        case diamond:
            create_board(b, 9, 9, peg);
            // hole b[4][4]
            break;
        case triangular:
            create_board(b, 5, 9, peg);
            // hole b[0][4]
            break;
        default:
           throw_error("Undefined board type\nBoard was unable to created correctly", "create_board");
    }
}

void create_board (vector<vector<CellState>> & b, int row, int col, CellState c) {
    b.resize(row);
    for (int i = 0; i < row; ++i) {
        b[i].resize(col);
        for (int j = 0; j < col; ++j)
            b[i][j] = c;
    }
}

void show_board (const vector<vector<CellState>> & b, BoardType type) {
    for (long unsigned int i = 0; i < b.size(); ++i) {
        for (auto it = b[i].begin(); it != b[i].end(); ++it) {
            switch (*it) {
                case peg:
                    cout << "P ";
                    break;
                case empty:
                    cout << ". ";
                    break;
                case hole:
                case out:
                    cout << "  ";
                    break;
            }
        }
        cout << endl;
    }
}

bool is_game_over (vector<vector<CellState>> & board, BoardType type) {
    bool r;

    return r;
}

void throw_error (string prompt, string location) {
    cout << "[!]" << prompt << "(" << location << ")" << endl;
}


int get_choice (string prompt, int lb, int ub) {
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

int get_choice (string in_prompt, string err_prompt, int lb, int ub) {
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

void u_print_boards () {
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