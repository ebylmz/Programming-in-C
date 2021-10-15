#ifndef peg_solitaire
#define peg_solitaire

using namespace std;

typedef enum {empty, peg, out} CellState;

typedef enum {french = 1, german = 2, asymmetrical = 3, english = 4, diamond = 5, triangular = 6} BoardType;


void peg_start ();
bool is_game_over (vector<vector<CellState>> & board);

void initBoard (vector<vector<CellState>>& b, BoardType btype);
void create_board (vector<vector<CellState>> & b, int row, int col, CellState c);
void show_board (const vector<vector<CellState>> & b);
BoardType select_board_type ();
void print_all_boards ();

// Takes an integer from console which is bounded as given inclusive lower and upper values  
void throw_error (string prompt, string location);
int get_choice (string prompt, int lb, int ub);
int get_choice (string in_prompt, string err_prompt, int lb, int ub);

#endif 