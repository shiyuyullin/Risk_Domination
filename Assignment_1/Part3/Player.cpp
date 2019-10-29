#include <iostream>
#include "Player.h"
using namespace std;
Player::Player()
{
	dice = new Dice();
	hand = new Hand();
	indexOfCountryOwned = new int[70];//Serial number of country 1,2,3..... corresponding to country[0], country[1],.....
	numberOfCountryOwned = new int(0);
}

Player::~Player()
{

	delete dice;
	dice = NULL;
	delete[] indexOfCountryOwned;
	delete numberOfCountryOwned;
}

void Player::reinforce()
{
	cout << "This method will reinforce"<<endl;
}

void Player::attack()
{
	Map* a = new Map();//A fake map that will be used temporarily, will be the map that has been selected.
	int state = 0;
	while (state != 1) {
		cout << "Welcome to the attack phase" << endl;
		cout << "Please choose the following options: 1. attack 2. not attack." << endl;
		cout << "if you want to attack, enter 1, if not enter 2: ";
		cin >> state;
		if (state == 1) {//enter the attack phase loop







		}
		else if (state == 2) {//return from method attack
			return;
		}
		else {//Invalid input
			cout << "Invalid input, please try again." << endl;

		}
	}


















}
 
void Player::foritfy()
{
	cout << "This method will fortify" << endl;
}

void Player::RollDice(int n)
{
	dice->Roll(n);
}

void Player::DisplayRollInfo(int n) //Displays: Roll values stored in the array and
									//Percentages
{
	dice->Display(n);
	dice->percentages();
}
void Player::incrementNumOfCountry() {
	numberOfCountryOwned++;
}


