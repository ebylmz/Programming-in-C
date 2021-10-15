#ifndef peg_solitaire
#define peg_solitaire

using namespace std;

typedef enum {empty, peg, hole, out} CellState;

typedef enum {french, german, asymmetrical, english, diamond, triangular} BoardType;

void peg_start ();
void u_print_boards ();
void initBoard (vector<vector<CellState>>& b, int type);
BoardType select_board_type ();
void create_board (vector<vector<CellState>> & b, int row, int col, CellState c);
void show_board (const vector<vector<CellState>> & b, BoardType type);
bool is_game_over (vector<vector<CellState>> & board, BoardType);
void throw_error (string prompt, string location);

// Takes an integer from console which is bounded as given inclusive lower and upper values  
int get_choice (string prompt, int lb, int ub);
int get_choice (string in_prompt, string err_prompt, int lb, int ub);

#endif 