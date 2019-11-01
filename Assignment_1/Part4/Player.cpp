#include <iostream>
#include "Player.h"
#include "Part1/Map.h"

using namespace std;

Player::Player()
{
	dice = new Dice();
	hand = new Hand();
	playerId = new int(0);
	numOfCountriesOwned = new int(0);
	indexOfCountries = new int[70];
}

Player::Player(int id,int armyCount)
{
	dice = new Dice();
	hand = new Hand();
	playerId = new int(id);
	armies = new int(armyCount);
	numOfCountriesOwned = new int(0);
	indexOfCountries = new int[70];
}

Player::~Player()
{
	delete playerId, armies, dice;
	dice = NULL;
	playerId = NULL;
	delete[] indexOfCountries;
	delete numOfCountriesOwned;
}


// TOFIX TO ARGUMENTS 
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

void Player::setPlayerId(int id)
{
	*playerId = id;
}

int Player::getPlayerId()
{
	return *playerId;
}

bool operator==(const Player &otherPlayer) const
{
	return getPlayerId() == otherPlayer.getPlayerId();
}
