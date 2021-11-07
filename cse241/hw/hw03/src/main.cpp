#include "pegSolitaire.h"


int main (void) {
    vector<PegSolitaire> game;  // Keeps all the games that currently playing
    
    bool exit = false;
    int choice;

    // welcomeGreet();
    cout << "\nEnter to start ";
    cin.get();
    // showGameRules();

    do {
        cout << "\n============ Main Menu ============\n"
             << "1. Start New Game\n"
             << "2. Load Game\n"
             << "3. Continue Active Game\n"
             << "4. Show Game Rules\n"
             << "0. Exit\n";
        choice = getChoice("Choose: ", 0, 3);
        switch (choice) {
            case 1: 
                game.push_back(PegSolitaire());
                break;
            case 2:
                char fileName[100];
                cout << "Enter the file name: ";
                cin  >> fileName;
                game.push_back(PegSolitaire(fileName));
                break;
            case 3:
                cout << "NOT IMPLEMENTED YET\n";
                // Select 
                break;
            case 0:
                exit = getChoice("\nAre you sure you want to exit the game? (y or n) "); break;
                break;
        }
    } while (! exit);
    cout << "======================== EXIT ========================\n";
}