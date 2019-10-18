#include <iostream>
#include "Player.h"
using namespace std;
Player::Player()
{
	dice = new Dice();
	hand = new Hand();
	//Countries needed here
}

Player::~Player()
{

	delete dice;
	dice = NULL;
}

void Player::reinforce()
{
	cout << "This method will reinforce"<<endl;
}

void Player::attack()
{
	cout << "This method will attack" << endl;
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


