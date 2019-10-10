#include <ostream>
#include "Dice.h"
#include <cstdlib> //Rand and SRand functions for random numbers
#include <ctime>
#include <iostream>
using namespace std;

int main() {
	//seed the random number generator
	//to generate diff values the application runs
	//or else they stay the same
	srand(static_cast<unsigned int> (time(0)));
	Dice* MyDice1 = new Dice();
	int rolls = 0;
	while (rolls <= 0 || rolls > 3) {
		cout << "How many times would you like to roll? \nNumbers (1-3): " << endl;
		cin >> rolls;
		if (rolls <= 0 || rolls > 3)
			cout << "Invalid roll number.\n" << endl;
	}
	MyDice1->Roll(rolls);
	MyDice1->Display(rolls);

	cout << "Percentages of Dice Values (1-6) rolled\n";
	MyDice1->percentages();
	cout << "\nDICE 2 OBJECT with no pointers\n";
	Dice MyDice2;
	rolls = 0;
	while (rolls <= 0 || rolls > 3) {
		cout << "How many times would you like to roll? \nNumbers (1-3): " << endl;
		cin >> rolls;
		if (rolls <= 0 || rolls > 3)
			cout << "Invalid roll number.\n" << endl;
	}
	MyDice2.Roll(rolls);
	MyDice2.Display(rolls);
	MyDice2.percentages();
	delete MyDice1;
}

