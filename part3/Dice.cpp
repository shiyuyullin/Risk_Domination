#include <iostream>
#include <cstdlib> //Rand and SRand functions for random numbers
#include <ctime>
#include "Dice.h"
using namespace std;
 //initialize variables for the class
Dice::Dice(void) : value(0), TotalRolls(0),DiceValues{}, percentage{}{
	TotalRollsptr = &TotalRolls;
	valueptr = &value;
	DVptr = DiceValues;
	Pptr = percentage;
}

//define roll method 
void Dice::Roll(int n) {
	 //generating random number from 0-5 and then add 1
	for (int i = 0; i < n; i++) {
	(*TotalRollsptr)++;
	//generate random number from 1-6
		value = (rand() % 6) + 1;
		DiceValues[i] = value;
		cout << "Value for die " << (i+1)<<": "<< *valueptr << endl;
		//store the dice values that have been rolled in an array for percentage
		percentage[(*valueptr - 1)]++;//increments the value of the die array (percentage)
	}
}


void Dice::Display(int rolls) {
	for (int i = 0; i < rolls; i++)
		cout << "Container value " << (i + 1) << ": " << *(DVptr + i) << endl;
		//cout << "Container value " << (i + 1) << ": " << DiceValues[i] << endl;
	
	for (int i = 0; i < 6; i++)
		cout << "Overall for Roll value " << (i + 1) << ": " << *(Pptr + i) << endl;
		//cout << "Overall for Roll value " << (i + 1) << ": " << percentage[i] << endl;

}


void Dice::Reset() {

	TotalRolls = 0;
}

void Dice::percentages()
{
	for (int i = 0; i < 6; i++)
		cout<<"Percentage for Dice Value "<< (i+1)<<": "<<(percentage[i] / TotalRolls)<<endl;
}

void Dice::DiceMain() //Testing the "main function" for Dice
{
	//seed the random number generator
//to generate diff values the application runs
//or else they stay the same
	srand(static_cast<unsigned int> (time(0)));
	Dice* MyDice1 = new Dice();
	int rolls = 0;
	while (rolls <= 0 || rolls > 100) {
		cout << "How many times would you like to roll? \nNumbers (1-3): " << endl;
		cin >> rolls;
		if (rolls <= 0 || rolls > 100)
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


