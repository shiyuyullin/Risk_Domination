#include <iostream>
#include "Player.h"
#include "Part1/Map.h"

using namespace std;

Player::Player()
{
	dice = new Dice();
	hand = new Hand();
	playerId = new int(0);
	//Countries needed here
}

Player::Player(int id)
{
	dice = new Dice();
	hand = new Hand();
	playerId = new int(id);
	//Countries needed here
}


Player::~Player()
{

	delete dice;
	dice = NULL;
	delete hand;
	hand = NULL;
}

void Player::reinforce(Country *toReinfoce, int numberOfArmies)
{

	int currentNumberOfArmies = toReinfoce->getNbOfArmies() + numberOfArmies;
	toReinfoce->setArmyNumber(currentNumberOfArmies);
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

void Player::setPlayerId(int id){
	*playerId = id;
}

int Player::getPlayerId(){
	return *playerId;
}
