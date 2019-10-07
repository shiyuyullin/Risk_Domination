#include <iostream>
#include "Player.h"
using namespace std;

Dice dice;
Player::Player()
{
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

void Player::RollDice()
{
	dice.Roll(2);
}

