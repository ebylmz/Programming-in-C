#include <iostream>
#include <vector>

using namespace std;

typedef enum {empty, peg} Board;

vector<vector<char>> init_board (int row, int col) {
    vector<vector<char>> b;
    
    b.resize(row);

    for (int i = 0; i < col; ++i) {
        b[i].resize(col);
        for (int j = 0; j < col; ++j)
            b[i][j] = 'o';
    }

    return b;
}

//! This code is wrong. Can you find the mistake
/*
void show_board (vector<vector<char>> b) {
    for (auto i = b.begin(); i != b.end(); ++i) {
        for (auto j = b[i].begin(); i != b[i].end(); ++j)
            cout << b[i][j] << " ";
        cout << endl;
    }
}
*/

void show_board (vector<vector<char>> b) {
    for (int i = 0; i < b.size(); ++i) {
        for (auto it = b[i].begin(); it != b[i].end(); ++it)
            cout << *it << "  ";
        cout << endl;
    }
}

int main (void) {
    vector<vector<char>> b;
    
    b = init_board(7, 7);
    show_board(b);

    return 0;
}
