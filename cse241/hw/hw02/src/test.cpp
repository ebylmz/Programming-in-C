/**
 * @file    test.cpp
 * @author  Emirkan Burak Yilmaz (emirkanyilmaz2019@gtu.edu.tr)
 * @brief   Testing Peg Solitaire Game
 * @version 0.2
 * @date    2021-10-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "peg_solitaire.h"

using namespace std;

void test01 ();
// Tests LoadGame function

void readBoard (vector<vector<CellState>> b);
void printBoard (vector<vector<CellState>> b);

int main (void) {
    pegStart();
    return 0;
}


void test01 () {
    continueGame();
}