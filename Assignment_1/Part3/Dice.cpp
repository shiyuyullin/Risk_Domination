#include <iostream>
#include <cstdlib> //Rand and SRand functions for random numbers
#include <ctime>
#include "Dice.h"
using namespace std;
//initialize variables for the class


Dice::Dice()
{
	valueptr = new int(0);
	TotalRollsptr = new int(0);
	*DiceValues = {};
	*percentage = {};
}

Dice::~Dice()
{
	delete valueptr;
	valueptr = NULL;
	delete TotalRollsptr;
	TotalRollsptr = NULL;
}

//define roll method 
void Dice::Roll(int n) {
	//generating random number from 0-5 and then add 1
	for (int i = 0; i < n; i++) {
		(*TotalRollsptr)++;
		//generate random number from 1-6
		*valueptr = (rand() % 6) + 1;
		DiceValues[i] = *valueptr;
		cout << "Value for die " << (i + 1) << ": " << *valueptr << endl;
		//store the dice values that have been rolled in an array for percentage
		percentage[(*valueptr - 1)]++;//increments the value of the die array (percentage)
	}
}


void Dice::Display(int rolls) {
	for (int i = 0; i < rolls; i++)
		cout << "Container value " << (i + 1) << ": " << DiceValues[i] << endl;
	//cout << "Container value " << (i + 1) << ": " << DiceValues[i] << endl;

	for (int i = 0; i < 6; i++)
		cout << "Overall for Roll value " << (i + 1) << ": " << percentage[i] << endl;
	//cout << "Overall for Roll value " << (i + 1) << ": " << percentage[i] << endl;

}


void Dice::Reset() {

	*TotalRollsptr = 0;
}

void Dice::percentages()
{
	for (int i = 0; i < 6; i++)
		cout << "Percentage for Dice Value " << (i + 1) << ": " << (percentage[i] / *TotalRollsptr) << endl;
}

const int Dice::get_value_at(int n)
{
	return DiceValues[n];
}
