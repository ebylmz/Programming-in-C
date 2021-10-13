#include <iostream>
#include <vector>
#include <string>
#include "peg_solitaire.h"

using namespace std;    // Should I put this in header file 

void start_peg_solitaire() {
    // There are two types of game: human or computer

    // There are 6 different type of boards. Select one of them 

    // Show/Print the board
    // Get the movement
    // Check and apply the movement
    // Check if game is over
    // Ask for new game
}

BoardType select_board_type () {
    //! NOT IMPLEMENTED YET
}

// Takes the type of board
vector<vector<char>> create_board (BoardType type) {
    vector<vector<char>> b;

    switch (type) {
        case french:
            b = create_vector2d(7, 7);
            // hole b[2][3]
            break;
        case german:
            b = create_vector2d(9, 9);
            // hole b[4][4]
            break;
        case asymmetrical:
            b = create_vector2d(8, 8);
            // hole b[4][3]
            break;
        case english:
            b = create_vector2d(7, 7);
            // hole b[3][3]
            break;
        case diamond:
            b = create_vector2d(9, 9);
            // hole b[4][4]
            break;
        case triangular:
            //! NOT IMPLEMENTED YET
            // hole b[?][?]
            b = create_vector2d(9, 9);
            break;
        default:
    }       throw_error("Undefined board type\nBoard was unable to created correctly", "create_board");
}


vector<vector<char>> create_vector2d (int row, int col) {
    vector<vector<char>> v;

    v.resize(row);
    for (int i = 0; i < row; ++i)
        v[i].resize(col);
    
    return v;
}

void show_board (vector<char> board, BoardType type) {

}

void is_game_over (vector<char> board) {}

void throw_error (string prompt, string location) {
    cout << "[!]" << prompt << "(" << location << ")" << endl;
}