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
        choice = getChoice("Select your board(0 for random board): ", 0, 6);
        
        if (choice == 0) {
            srand(time(NULL));
            choice = rand() % 6 + 1;
        }

        btype = static_cast<BoardType>(choice);
        initBoard(board, btype);

        // There are two types of game: human & computer
        cout << "______________________" << endl
             << "0. Exit\n"
             << "1. Human Game\n"
             << "2. Computer Game\n";
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
            cout << "______________________\n"
                 << "\nGame is Over!\n" 
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

        r = getMovement(startRow, startCol, dir);
        if (r == EXIT_SUDO)
            cout << "Game is ended\n";
        else {
            r = applyMovement(board, startRow, startCol, dir);

            if (r == EXIT_SUCCESS)
                showBoard(board);
            else
                throwError("Invalid Move");
        }
    } while (r != EXIT_SUDO && (r == EXIT_FAILURE || isGameOver(board) == false));
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

int getMovement (int & startRow, int & startCol, Direction & dir) {
    int r;
    string mov;
    do {
        cout << "\nMovement: ";
        cin >> mov;
        convertUpperCase(mov);

        if (mov == "EXIT")
            r = EXIT_SUDO;
        else {
            // Set failure flag up in case of an errror
            r = EXIT_FAILURE;

            // Check if entered movement is in a proper format
            if ((mov.length() == 4 || mov.length() == 5) && isLetter(mov[0]) && isNumber(mov[1]) && mov[2] == '-') {
                startCol = mov[0] - 'A';
                startRow = mov[1] - '1';

                dir = getDirection(mov);
                if (dir != Direction::none) r = EXIT_SUCCESS; 
            }
        }
        if (r == EXIT_FAILURE) throwError("Invalid movement format");
    } while (r == EXIT_FAILURE); 
    return r;
}

Direction getDirection (string & movement) {
    Direction dir = Direction::none;

    if (movement.length() == 4 || movement.length() == 5) {
        int x = 0, y = 0;
        bool err = false;
        
        /*  To find the direction, use 1x1 cordinate system.
            If given directions resulted in at orijin or CellState::out of cordinate system,
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
                dir = Direction::up;
            else if (x == 0 && y == -1)
                dir = Direction::down;
            else if (x == 1 && y == 0)
                dir = Direction::right;
            else if (x == -1 && y == 0)
                dir = Direction::left;
            else if (x == 1 && y == 1)
                dir = Direction::upRight;
            else if (x == -1 && y == 1)
                dir = Direction::upLeft;
            else if (x == 1 && y == -1)
                dir = Direction::downRight;
            else if (x == -1 && y == -1)
                dir = Direction::downLeft;
        }
    }

    return dir;
}

string dirToStr (Direction dir) {
    string s;

    switch (dir) {
        case Direction::up:
            s = "U";  break;
        case Direction::down:
            s = "D";  break;
        case Direction::left:
            s = "L";  break;
        case Direction::right:
            s = "R";  break;
        case Direction::upRight:
            s = "UR"; break;
        case Direction::upLeft:
            s = "UL"; break;
        case Direction::downLeft:
            s = "DL"; break;
        case Direction::downRight:
            s = "DR"; break;
        default:
            s = "NONE"; 
    }
    return s;
}

int applyMovement (vector<vector<CellState>> & board, int startRow, int startCol, Direction dir) {
    int r = EXIT_FAILURE;

    // up/down movements are invalid for triangular board 
    // diagonal movements are invalid for all the boards except triangular board 
    if (isProperDirection(board, dir)) {
        // Check if movement is exceed board
        if (isMovable(board, startRow, startCol, dir)) {
            int jumpRow, jumpCol, targetRow, targetCol;
            getMoveCell(startRow, startCol, dir, jumpRow, jumpCol, targetRow, targetCol);

            // Apply movement
            board[startRow][startCol] = CellState::empty;
            board[jumpRow][jumpCol] = CellState::empty;
            board[targetRow][targetCol] = CellState::peg;
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
        case Direction::up:
            moveUp(jumpRow, targetRow);    break;
        case Direction::down:
            moveDown(jumpRow, targetRow);  break;
        case Direction::left:
            moveLeft(jumpCol, targetCol);  break;
        case Direction::right:
            moveRight(jumpCol, targetCol); break;
        case Direction::upRight:
            moveUp(jumpRow, targetRow);
            moveRight(jumpCol, targetCol); break;
        case Direction::upLeft:
            moveUp(jumpRow, targetRow);
            moveLeft(jumpCol, targetCol);  break;
        case Direction::downLeft:
            moveDown(jumpRow, targetRow);
            moveLeft(jumpCol, targetCol);  break;
        case Direction::downRight:
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
        r = isMovable(board, startRow, startCol, Direction::upLeft)   ||
            isMovable(board, startRow, startCol, Direction::upRight)  ||
            isMovable(board, startRow, startCol, Direction::downLeft) ||
            isMovable(board, startRow, startCol, Direction::downRight);
    }
    else {
        // For other boards try the 4 main direction
        r = isMovable(board, startRow, startCol, Direction::up)   ||
            isMovable(board, startRow, startCol, Direction::down) ||
            isMovable(board, startRow, startCol, Direction::left) ||
            isMovable(board, startRow, startCol, Direction::right);
    }

    return r;
}

bool isMovable (const vector<vector<CellState>> & board, int startRow, int startCol, Direction dir) {
    int r; 
    
    if (isProperDirection(board, dir)) {
        int v, jumpRow, jumpCol, targetRow, targetCol;
        
        v = getMoveCell(startRow, startCol, dir, jumpRow, jumpCol, targetRow, targetCol);
        
        r = v == EXIT_SUCCESS                       &&
            isInBoard(board, startRow, startCol)    && 
            board[startRow][startCol] == CellState::peg        &&
            isInBoard(board, jumpRow, jumpCol)      && 
            board[jumpRow][jumpCol] == CellState::peg          &&
            isInBoard(board, targetRow, targetCol)  && 
            board[targetRow][targetCol] == CellState::empty;
    }
    else
        r = false; 
    return r;
}

bool isProperDirection (const vector<vector<CellState>> & board, Direction dir) {
    bool r;

    if (dir != Direction::none) {
        bool triangularBoard = isTriangularBoard(board);
        r =  triangularBoard  &&  isTriangularMovement(dir) ||
            !triangularBoard  && !isDiagonalMovement(dir)   ; 
    }
    else 
        r = false;
    return r;
}

bool isTriangularMovement (Direction dir) {
    return dir != Direction::none && dir != Direction::up && dir != Direction::down;
}

bool isDiagonalMovement (Direction dir) {
    return dir == Direction::upRight || dir == Direction::upLeft || dir == Direction::downRight || dir == Direction::downLeft;
}

bool isGameOver (const vector<vector<CellState>> & board) {
    bool r = true;
    
    // The game continues until there are no pegs to move legally.
    for (int i = 0; i < board.size() && r == true; ++i)
        for (int j = 0; j < board[i].size() && r == true; ++j)
            if (board[i][j] == CellState::peg)
                r = !isMovable(board, i, j);

    return r;
}

int calculateScore (vector<vector<CellState>> & board) {
    int score = 0;

    for (int i = 0; i < board.size(); ++i) 
        for (auto it = board[i].begin(); it != board[i].end(); ++it)
            if (*it == CellState::peg)
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
        case BoardType::french:
            initBoardFrench(b);         break;
        case BoardType::german:
            initBoardGerman(b);         break;
        case BoardType::asymmetrical:
            initBoardAsymmetrical(b);   break;
        case BoardType::english:
            initBoardEnglish(b);        break;
        case BoardType::diamond:
            initBoardDiamond(b);        break;
        case BoardType::triangular:
            initBoardTriangular(b);     break;
        default:
           throwError("Undefined board type. Board was unable to create correctly", "createBoard");
    }
}

void initBoardFrench(vector<vector<CellState>> & board) {
    createBoard(board, 7, 7, CellState::peg);

    for (int i = 0, n = 2; i < 2; ++i, --n)
        for (int j = 0; j < n; ++j)
            board[i][j] = CellState::out;

    for (int i = 0, n = 5; i < 2; ++i, ++n)
        for (int j = n; j < 7; ++j)
            board[i][j] = CellState::out;

    for (int i = 5, n = 1; i < 7; ++i, ++n)
        for (int j = 0; j < n; ++j)
            board[i][j] = CellState::out;

    for (int i = 5, n = 6; i < 7; ++i, --n)
        for (int j = n; j < 7; ++j)
            board[i][j] = CellState::out;
    
    board[2][3] = CellState::empty;
}   

void initBoardGerman(vector<vector<CellState>> & board) {
    createBoard(board, 9, 9, CellState::peg);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = CellState::out;

    for (int i = 0; i < 3; ++i)
        for (int j = 6; j < 9; ++j)
            board[i][j] = CellState::out;

    for (int i = 6; i < 9; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = CellState::out;

    for (int i = 6; i < 9; ++i)
        for (int j = 6; j < 9; ++j)
            board[i][j] = CellState::out;
    
    board[4][4] = CellState::empty;
}   

void initBoardAsymmetrical(vector<vector<CellState>> & board) {
    createBoard(board, 9, 8, CellState::peg);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 2; ++j)
            board[i][j] = CellState::out;

    for (int i = 0; i < 3; ++i)
        for (int j = 5; j < 8; ++j)
            board[i][j] = CellState::out;

    for (int i = 6; i < 9; ++i)
        for (int j = 0; j < 2; ++j)
            board[i][j] = CellState::out;

    for (int i = 6; i < 9; ++i)
        for (int j = 5; j < 8; ++j)
            board[i][j] = CellState::out;
    
    board[4][3] = CellState::empty;
}  

void initBoardEnglish(vector<vector<CellState>> & board) {
    createBoard(board, 7, 7, CellState::peg);

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            board[i][j] = CellState::out;

    for (int i = 0; i < 2; ++i)
        for (int j = 5; j < 7; ++j)
            board[i][j] = CellState::out;

    for (int i = 5; i < 7; ++i)
        for (int j = 0; j < 2; ++j)
            board[i][j] = CellState::out;

    for (int i = 5; i < 7; ++i)
        for (int j = 5; j < 7; ++j)
            board[i][j] = CellState::out;

    board[3][3] = CellState::empty;
}   

void initBoardDiamond(vector<vector<CellState>> & board) {
    createBoard(board, 9, 9, CellState::peg);

    for (int i = 0, n = 4; i < 4; ++i, --n)
        for (int j = 0; j < n; ++j)
            board[i][j] = CellState::out;

    for (int i = 0, n = 5; i < 4; ++i, ++n)
        for (int j = n; j < 9; ++j)
            board[i][j] = CellState::out;

    for (int i = 5, n = 1; i < 9; ++i, ++n)
        for (int j = 0; j < n; ++j)
            board[i][j] = CellState::out;

    for (int i = 5, n = 8; i < 9; ++i, --n)
        for (int j = n; j < 9; ++j)
            board[i][j] = CellState::out;

    board[4][4] = CellState::empty;
}   

void initBoardTriangular(vector<vector<CellState>> & board) {
    board.resize(5);

    for (int i = 0; i < 5; ++i) {
        board[i].resize(i + 1);
        for (int j = 0; j <= i; ++j)
            board[i][j] = CellState::peg;
    }
    board[0][0] = CellState::empty;
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
    if (isTriangularBoard(b))
        showTriangularBoard(b);
    else 
        showNonTriangularBoard(b);
}

void showTriangularBoard (const vector<vector<CellState>> & b) {
    cout << endl;

    for (int i = 0, n = 5 + b.size(); i < n; ++i)
        cout << " ";
    cout << "A\n";

    for (int i = 0, n = 5 + b.size() + 1; i < n; ++i)
        cout << "   ";
    cout << "B\n";

    for (int i = 0; i < b.size(); ++i) {
        cout << 1 + i << "  ";
        //! NOT IMPLEMENTED YET
    }
}

void showNonTriangularBoard (const vector<vector<CellState>> & b) {
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
                case CellState::peg:
                    cout << "P";
                    break;
                case CellState::empty:
                    cout << ".";
                    break;
                case CellState::out:
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
            b[row][col] != CellState::out;
}

bool isTriangularBoard (const vector<vector<CellState>> & b) {
    bool r = true;

    for (int i = 0; i < b.size() && r == true; ++i)
        r = b[i].size() == i + 1;
    return r;
}

void printAllBoardTypes () {
    cout    << "1- French                2- German\n"
            << "--------------------     --------------------\n"
            << "      P P P                      P P P\n"
            << "    P P P P P                    P P P\n"
            << "  P P P . P P P                  P P P\n"
            << "  P P P P P P P            P P P P P P P P P\n"
            << "  P P P P P P P            P P P P . P P P P\n"
            << "    P P P P P              P P P P P P P P P\n"
            << "      P P P                      P P P\n"
            << "                                 P P P\n"
            << "                                 P P P\n"
            << "\n";

    cout    << "3- Asymmetrical          4- English\n"
            << "--------------------     --------------------\n"
            << "      P P P                    P P P\n"
            << "      P P P                    P P P\n"
            << "      P P P                P P P P P P P\n"
            << "  P P P P P P P P          P P P . P P P\n"
            << "  P P P . P P P P          P P P P P P P\n"
            << "  P P P P P P P P              P P P\n"
            << "      P P P                    P P P\n"
            << "      P P P\n"
            << "\n";
    
    cout    << "5- Diamond               6- Triangle\n"
            << "--------------------     --------------------\n"
            << "          P                    .\n"
            << "        P P P                 P P\n"
            << "      P P P P P              P P P\n"
            << "    P P P P P P P           P P P P\n"
            << "  P P P P . P P P P        P P P P P\n"
            << "    P P P P P P P\n"
            << "      P P P P P\n"
            << "        P P P\n"
            << "          P\n"
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