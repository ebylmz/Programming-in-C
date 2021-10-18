#include <iostream>

using namespace std;

enum class Direction {up, down, right, left, upRight, upLeft, downRight, downLeft};
enum class Direction2 {up, down, right, left, upRight, upLeft, downRight, downLeft};

enum Color {red, green, blue};

int main (void) {

	Direction dir = Direction::upRight;
	// :: (scope resolution operator)
	// strongly enums have their own scope so Direction and Direction2
	// normaly invalid because they have same name for enumeration
	// but in strongly typed their scopes are different, so it's valid


	// Strongly typed enums are does not converted to int automaticly 
	cout << static_cast<int>(dir) << endl;

	Color c = red;
	cout << c << endl;
}