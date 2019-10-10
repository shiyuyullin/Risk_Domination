#include <iostream>
#include <cstdlib> //Rand and SRand functions for random numbers
#include <ctime>
#include "Dice.h"
using namespace std;

Dice::Dice(void) : value(0), TotalRolls(0),DiceValues{}, percentage{}{
	TotalRollsptr = &TotalRolls;
	valueptr = &value;
	DVptr = DiceValues;
	Pptr = percentage;
} //initialize variables for the class
//define roll method

 
void Dice::Roll(int n) {
	 //generating random number from 0-5 and then add 1
	for (int i = 0; i < n; i++) {
	TotalRolls++;
	//generate random number from 1-6
		value = (rand() % 6) + 1;
		DiceValues[i] = value;
		cout << "Value for die " << (i+1)<<": "<< value << endl;
		//store the dice values that have been rolled in an array for percentage
		percentage[(value - 1)]++;//increments the value of the die array (percentage)
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
