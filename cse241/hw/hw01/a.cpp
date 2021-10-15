#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef enum {empty, peg, hole, out} CellState;

void print_vector_2d (const vector<vector<CellState>> v);
void create_vector2d (vector<vector<CellState>> & v, int row, int col, CellState c);
vector<vector<CellState>> & create_vector2d(int row, int col, CellState c);
void show_vector_size (const vector<vector<CellState>> v);


int main (void) {
    vector<vector<CellState>> & v = create_vector2d(10, 10, empty);
    print_vector_2d(v);

    int n;
    cin >> n;
    return 0;
}


void print_vector_2d (const vector<vector<CellState>> v) {
    for (long unsigned int i = 0; i < v.size(); ++i) {
        for (auto it = v[i].begin(); it != v[i].end(); ++it) {
            switch (*it) {
                case empty:
                    cout << " . ";
                    break;
                case peg:
                    cout << "P ";
                    break;
                case hole:
                    cout << "  ";
                    break;
                case out:
                    cout << "  ";
                    break;
            }
        }
        cout << endl;
    }
}

void create_vector2d (vector<vector<CellState>> & v, int row, int col, CellState c) {
    v.resize(row);
    for (int i = 0; i < row; ++i) {
        v[i].resize(col);
        for (int j = 0; j < col; ++j)
            v[i][j] = c;
    }
}

vector<vector<CellState>> & create_vector2d(int row, int col, CellState c) {
    vector<vector<CellState>> v;
    v.resize(row);
    for (int i = 0; i < row; ++i) {
        v[i].resize(col);
        for (int j = 0; j < col; ++j)
            v[i][j] = c;
    }

    return v;
}

void show_vector_size (const vector<vector<CellState>> v) {
    cout    << "Size:     " << v.size() << endl
            << "Capacity: " << v.capacity() << endl;
}   