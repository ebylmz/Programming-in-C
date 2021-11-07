#include "pegSolitaire.h"

/***********************************************************************************
 *                                     Movement
 **********************************************************************************/

PegSolitaire::Movement::Movement (int rowValue, int colValue, Direction dir)
    : row(rowValue), col(colValue), direction(dir) {}

PegSolitaire::Movement::Movement () 
    : row(0), col(0), direction(Direction::none) {}

void PegSolitaire::Movement::setRand (int n) {
    srand(time(NULL));
    row =  rand() % n;
    col =  rand() % n;
    direction = static_cast<Direction>(rand() % 4);
}

/***********************************************************************************
 *                                     Cell
 **********************************************************************************/

inline PegSolitaire::Cell::Cell (const string & cellCol, int cellRow, CellValue cellValue) {
    setCol(cellCol);
    setRow(cellRow); 
    setValue(cellValue); 
}

inline PegSolitaire::Cell::Cell () {
    //! NOT IMPLEMENTED YET: No Parameter Constructor
}

/* =============================== Getters ============================== */

void PegSolitaire::Cell::getCell (string & cellCol, int & cellRow, CellValue & cellValue) const {
    cellCol = col; 
    cellRow = row; 
    cellValue = value; 
}

inline PegSolitaire::CellValue PegSolitaire::Cell::getValue () const {
    return value;
}

inline string PegSolitaire::Cell::getCol () const {
    return col;
}

inline int PegSolitaire::Cell::getRow () const {
    return row;
}

/* =============================== Setters ============================== */

inline void PegSolitaire::Cell::setCell (string cellCol, int cellRow, CellValue cellValue) {
    setCol(cellCol);
    setRow(cellRow); 
    setValue(cellValue); 
}

inline void PegSolitaire::Cell::setValue (CellValue cellValue) {
    if (cellValue == CellValue::peg || cellValue == CellValue::empty || cellValue == CellValue::out)
        value = cellValue;
    else {
        cerr << "(!) Invalid cell value: " << static_cast<char>(cellValue) << endl;
        exit(1);
    }
}

inline void PegSolitaire::Cell::setCol (string cellCol) {
    if (1)  
    //! validate the string col
        col = cellCol;
    else {
        cerr << "(!) Invalid cell coloumn: " << cellCol << endl;
        exit(1);
    }
}

inline void PegSolitaire::Cell::setRow (int cellRow) {
    if (cellRow >= 0)
        row = cellRow;
    else {
        cerr << "(!) Invalid cell row: " << cellRow << endl;
        exit(1);
    }
}

/* =============================== Utility ============================== */

int PegSolitaire::Cell::convertCellCol (const string & col) const {
    return col[0] - 'A' + (stoi(&col[1]) - 1) * 26;
}

string PegSolitaire::Cell::convertCellCol (int col) const {
    const int ENG_LETTER_NUM = 26;    // The number of letter in english alphabet
    string r;

    while (col > 0) {
        r.push_back('A' + col % ENG_LETTER_NUM);
        col /= ENG_LETTER_NUM;
    }
    
    int s = 0, e = r.size() - 1;

    // Reverse the string r
    while (s != e) {
        int tmp = r[s];
        r[s] = r[e];
        r[e] = tmp;
        ++s, --e;
    }
    
    return r;
}

/***********************************************************************************
 *                                  PegSolitaire
 **********************************************************************************/

PegSolitaire::PegSolitaire (const char * fileName) {
    load(fileName); // Load cheks if the given board size is proper
    startGame();
}

PegSolitaire::PegSolitaire (int boardType) {
    setBoard(boardType);
    startGame();
}

PegSolitaire::PegSolitaire () {
    //! Maybe some question can ask
    startGame();
}

void PegSolitaire::startGame () {
    // check the game mode is defined
    if (gameMode == GameMode::undefined) {
        cout << "0. Return Main Menu\n"
             << "1. Human Game\n"
             << "2. Computer Game\n";
        gameMode = static_cast<GameMode>(getChoice("Select the game type: ", 0, 2));
    }
    
    switch (gameMode) {
        case GameMode::computer:
            playGame();
            break;
        case GameMode::human:
            Movement mov;
            //! ımplement better getmovement functiıon
            do getMovement(mov);
            while (!isGameOver() || applyMovement(mov) != RETURN_SUCCESS);
            break;
        case GameMode::undefined:
            cout << "EXIT\n";
    }
}

PegSolitaire::Movement PegSolitaire::play () {
    Movement mov;
    
    do mov.setRand(boardSize);
    while (!isGameOver() && applyMovement(mov) != RETURN_SUCCESS);

    return mov;
}

void PegSolitaire::play (string col, int row, PegSolitaire::Direction dir) {
    // Movement mov(col, row, dir);
    // applyMovement(mov);
    //! NOT IMPLEMENTED YET   
}

void PegSolitaire::playGame () {
    //! NOT IMPLEMENTED YET   
    // selects the board type
    // Plays the game with random movements
    do { 
        Movement mov = play();
        // cout << mov;
        cout << "NOT IMPLEMENTED YET: OVERLOAD << FOR Movement\n";
    } while (! isGameOver());
}

void PegSolitaire::getMovement (Movement & mov) const {
    //! NOT IMPLEMENTED YET   
}

int PegSolitaire::applyMovement (const Movement & mov) {
    //! NOT IMPLEMENTED YET   
}

void PegSolitaire::load (const char * fileName) {
    //! NOT IMPLEMENTED YET   
}

void PegSolitaire::save (const char * fileName) const {
    //! NOT IMPLEMENTED YET   
}

void PegSolitaire::displayBoard () const {
    const int ENG_LETTER_NUM = 26;                  // The number of letter in english alphabet
    int margin = boardSize / ENG_LETTER_NUM  + 1;   // Define the space between coloumns

    // Print the coloumns
    for (int i = 0; i < boardSize; ++i) {
        cout << board[i][0].getCol();
        printn(' ', margin);
    }
    cout << endl;

    for (int i = 0; i < boardSize; ++i) {
        cout << 1 + i;
        printn(' ', margin);
        
        for (int j = 0; j < boardSize; ++j) {
            cout << static_cast<char>(board[i][j].getValue());
            printn(' ', margin);
        }
        cout << endl;
    }
}

bool PegSolitaire::isMovable (const Movement & mov) const {
    //! NOT IMPLEMENTED YET   
}

bool PegSolitaire::isGameOver () const {
    cout << "NOT IMPLEMENTED YET";
    return true;
}

void PegSolitaire::setBoard () {
    // Ask the board type and initialize the board
    printAllBoardTypes();
    cout << "0. Exit\n"
         << "1. French\n"
         << "2. German\n"
         << "3. Asymmetrical\n"
         << "4. English\n"
         << "5. Diamond\n"
         << "6. Triangle\n"
         << "7. Random Selection\n";
    int choice = getChoice("Select your board: ", 0, 7);
    
    // Select a random board
    if (choice == 7) {
        srand(time(NULL));
        choice = rand() % 6 + 1;
        cout << endl << choice << " board selected randomly\n";
    }
    setBoard(choice);
}

void PegSolitaire::setBoard (int boardType) {
    switch (boardType) {
        case 1:
            setBoardFrench();         break;
        case 2:
            setBoardGerman();         break;
        case 3:
            setBoardAsymmetrical();   break;
        case 4:
            setBoardEnglish();        break;
        case 5:
            setBoardDiamond();        break;
        case 6:
            setBoardTriangular();     break;
        default:
            cerr << "(!) Undefined board type. Board was unable to create correctly\n";
            exit(1);
    }
}

void PegSolitaire::setBoardFrench () {
    initBoard(7, 7, CellValue::peg);
    
    for (int i = 0, n = 2; i < 2; ++i, --n)
        for (int j = 0; j < n; ++j)
            board[i][j].setValue(CellValue::out);

    for (int i = 0, n = 5; i < 2; ++i, ++n)
        for (int j = n; j < 7; ++j)
            board[i][j].setValue(CellValue::out);

    for (int i = 5, n = 1; i < 7; ++i, ++n)
        for (int j = 0; j < n; ++j)
            board[i][j].setValue(CellValue::out);

    for (int i = 5, n = 6; i < 7; ++i, --n)
        for (int j = n; j < 7; ++j)
            board[i][j].setValue(CellValue::out);
    
    board[2][3].setValue(CellValue::empty);
}   

void PegSolitaire::setBoardGerman () {
    initBoard(9, 9, CellValue::peg);

    fillBoard(0, 3, 0, 3, CellValue::out);
    fillBoard(0, 3, 6, 9, CellValue::out);
    fillBoard(6, 9, 0, 3, CellValue::out);
    fillBoard(6, 9, 6, 9, CellValue::out);
    board[4][4].setValue(CellValue::empty);
}   

void PegSolitaire::setBoardAsymmetrical () {
    initBoard(8, 8, CellValue::peg);

    fillBoard(0, 3, 0, 2, CellValue::out);
    fillBoard(0, 3, 5, 8, CellValue::out);
    fillBoard(6, 8, 0, 2, CellValue::out);
    fillBoard(6, 8, 5, 8, CellValue::out);
    board[4][3].setValue(CellValue::empty);
}  

void PegSolitaire::setBoardEnglish () {
    initBoard(7, 7, CellValue::peg);

    fillBoard(0, 2, 0, 2, CellValue::out);
    fillBoard(0, 2, 5, 7, CellValue::out);
    fillBoard(5, 7, 0, 2, CellValue::out);
    fillBoard(5, 7, 5, 7, CellValue::out);
    board[3][3].setValue(CellValue::empty);
}   

void PegSolitaire::setBoardDiamond () {
    initBoard(9, 9, CellValue::peg);

    for (int i = 0, n = 4; i < 4; ++i, --n)
        for (int j = 0; j < n; ++j)
            board[i][j].setValue(CellValue::out);

    for (int i = 0, n = 5; i < 4; ++i, ++n)
        for (int j = n; j < 9; ++j)
            board[i][j].setValue(CellValue::out);

    for (int i = 5, n = 1; i < 9; ++i, ++n)
        for (int j = 0; j < n; ++j)
            board[i][j].setValue(CellValue::out);

    for (int i = 5, n = 8; i < 9; ++i, --n)
        for (int j = n; j < 9; ++j)
            board[i][j].setValue(CellValue::out);
    board[4][4].setValue(CellValue::empty);
}   

void PegSolitaire::setBoardTriangular () {
    initBoard(5, 5, CellValue::out);

    board[0][0].setValue(CellValue::empty);
    for (int i = 1; i < 5; ++i)
        for (int j = 0; j <= i; ++j)
            board[i][j].setValue(CellValue::peg);
}  

void PegSolitaire::initBoard (int row, int col, PegSolitaire::CellValue initValue) {
    board.resize(row);
    for (int i = 0; i < row; ++i) {
        string str_col("@");    // initialize from 'A' - 1

        board[i].resize(col);
        for (int j = 0; j < col; ++j) {
            ++str_col[str_col.size() - 1];

            /* Be sure str_col does not go outside from the alphabet
               A B C ... AA AB AC ... AAA AAB AAC ...   */
            for (int k = str_col.size() - 1; str_col[k] > 'Z'; --k) {
                str_col[k] = 'A';
                // Add new digit
                if (k == 0) 
                    str_col.push_back('A');
                else
                    ++str_col[k - 1];
            }

            board[i][j].setCol(str_col);
            board[i][j].setRow(i + 1); 
            board[i][j].setValue(initValue);
        }
    }
}

void PegSolitaire::fillBoard (int outStart, int outEnd, int inStart, int inEnd, CellValue v) {
    for (int i = outStart; i < outEnd; ++i)
        for (int j = inStart; j < inEnd; ++j)
            board[i][j].setValue(v);
}

void PegSolitaire::printIntro () const {
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
         << "|            WELCOME TO PEG SOLITAIRE             |\n"
         << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
}

void PegSolitaire::printGameRules () const {
    cout << "================ GAME RULES ================\n\n"
         << "Movement Directions\n"
         << "---------------------------------------------\n"
         << " U: Up                 U\n"
         << " D: Down           UL  |  UR\n"
         << " L: Left        L -----|----- R\n"
         << " R: Right          DL  |  DR\n"
         << "                       D\n\n";
    cout << "Triangular Board\n"
         << "---------------------------------------------\n"
         << "Interface                  Notation\n" 
         << "------------------         ------------------ \n"  
         << "         A\n"
         << "          B\n"
         << "1      .   C                       A1\n"
         << "2     P P   D                    A2  B2\n"
         << "3    P P P   E                 A3  B3  C3\n"
         << "4   P P P P                  A4  B4  C4  D4\n"
         << "5  P P P P P               A5  B5  C5  D5  E5\n\n"
         << "// U and D movements are invalid for triangular board\n\n";

    cout << "Non-Triangular Board\n"
         << "---------------------------------------------\n"
         << "Interface                  Notation\n" 
         << "------------------         ------------------\n"  
         << "   A B C D E F G\n\n"
         << "1      P P P                     C1 D1 E1\n"
         << "2    P P P P P                B2 C2 D2 E2 F2\n"
         << "3  P P P . P P P           A3 B3 C3 D3 E3 F3 G3\n"
         << "4  P P P P P P P           A4 B4 C4 D4 E4 F4 G4\n"
         << "5  P P P P P P P           A5 B5 C5 D5 E5 F5 G5\n"
         << "6    P P P P P                B6 C6 D6 E6 F6\n"
         << "7      P P P                     C7 D7 E7\n\n"
         << "// Diagonal movements(UL, DL, UR, DR) are invalid for non-triangular board\n\n";

    cout << "================ GAME MODES ================\n\n"
         << "// There are 2 type of games: Human mode and Computer mode\n"
         << "Human Mode\n"
         << "------------------\n"
         << "// All the movements done by the player\n"
         << "Computer Mode\n"
         << "------------------\n"
         << "// All the movements done by the computer\n\n";

    cout << "============= EXAMPLE MOVEMENTS ============\n\n"
         << "Diagonal Movements\n"
         << "------------------\n"
         << "A3-UR: Select cell at coloumn A, row 3 and move to the Up-Right\n"
         << "B3-DL: Select cell at coloumn B, row 3 and move to the Down-Left\n\n"
         << "Direct Movements:\n"
         << "------------------\n"
         << "C6-U : Select cell at coloumn C, row 6 and move to the Up\n"
         << "E5-R : Select cell at coloumn E, row 5 and move to the Right\n\n"
         << "EXIT Command:\n"
         << "------------------\n"
         << "// Type EXIT to exit the movement screen\n\n";
    
    cout << "================= COMMANDS ================\n\n"
         << "/****/ You can use these commands when you see terminal sign(>>)\n\n"
         << "// exit: Exits from current place\n"
         << "       usage: exit\n\n"
         << "// save: Saves the current progress of the game\n"
         << "       usage: save filename.txt\n\n"
         << "// load: Loads the spefic game\n"
         << "       usage: load filename.txt\n\n";

    cout << "Enter to continue ";
    cin.get();
}

void PegSolitaire::printGameResult (int score, int numberOfMovement) const {
    cout << "\n============== GAME IS OVER ==============\n" 
         << "\tNumber of Movement: " << numberOfMovement << endl
         << "\tScore: " << score << "\n"
         << "==========================================\n\n";
}

/***********************************************************************************
 *                                    Helper
 **********************************************************************************/

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

void printn (char c, int n) {
    for (int i = 0; i < n; ++i)
        cout << c;
}

bool getChoice (string prompt) {
    bool exit = false;
    string s;
    char c;

    cout << prompt;
    do {
        cin >> s;
        c = toupper(s[0]);
        
        if (c == 'Y' || c == 'N')
            exit = true;
        else
            cout << "Please select a proper choose: ";
    } while (exit == false);
    cin.get();  // consume \n
    return c == 'Y' ? true : false;
}

int getChoice (string prompt, int lb, int ub) {
    bool exit = false;
    string s;
    int r;
    
    cout << prompt;    
    do {
        cin >> s;
        r = strToInt(s);

        if (r != RETURN_FAILURE && isInRange(r, lb, ub))
            exit = true;
        else
            cout << "Please select a proper choose: ";
    } while (exit == false);
    cin.get();  // consume \n
    return r;    
}

int getChoice (string inPrompt, string errPrompt, int lb, int ub) {
    bool exit = false;
    string s;
    int r;
    
    cout << inPrompt;    
    do {
        cin >> s;
        r = strToInt(s);

        if (r != RETURN_FAILURE && isInRange(r, lb, ub))
            exit = true;
        else
            cout << errPrompt << endl
                 << "Please select a proper choose: ";
    } while (exit == false);
    cin.get();  // consume \n
    return r;
}

int strToInt (const string & s) {
    int r = 0;

    // RETURN_FAILURE is negative constant value
    for (int i = 0; i < s.length() && r != RETURN_FAILURE; ++i)
        if (isdigit(s[i]))
            r = r * 10 + s[i] - '0';
        else 
            r = RETURN_FAILURE;

    return r;
}

void strUp (string & s) {
    for (auto it = s.begin(); it != s.end(); ++it)
        *it = toupper(*it); 
}

bool isInRange (int n, int lb, int ub) {
    return lb <= n && n <= ub;
}