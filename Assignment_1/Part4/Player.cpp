#include "Player.h"
#include <iostream>
#include "Map.h"
#include "GameEngine.h" 

using namespace std;
Player::Player()
{
	//Actions done in the strategy object for every time a player does some action (like attack,reinforce, or fortify a country)
	actionsDoneInStrat = new int(0);
	
	dice = new Dice();
	hand = new Hand();
	numberOfCountryOwned = new int(0);
	playerId = new int(0);
	armies = new int();
}

Player::Player(int id, int armyCount)
{
	actionsDoneInStrat = new int(0);
	dice = new Dice();
	hand = new Hand();
	playerId = new int(id);
	armies = new int(armyCount);
	numberOfCountryOwned = new int(0);
}

Player::~Player()
{
	delete actionsDoneInStrat;
	delete dice;
	delete hand;
	delete numberOfCountryOwned;
	int temp = indexOfCountryOwned.size();
	for (int i = 0; i < temp; ++i) {
		delete indexOfCountryOwned[i];
	}
	delete armies;
	delete playerId;
}
//Strategy partten calling
void Player::reinforce() {
	this->playerStrategy->Reinforce(this);
}
void Player::attack() {
	this->playerStrategy->Attack(this);
}
void Player::foritfy() {
	this->playerStrategy->Fortify(this);
}


void Player::removeIndex(int index) {
	indexOfCountryOwned.erase((indexOfCountryOwned.begin() + index));
	indexOfCountryOwned.shrink_to_fit();
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

void Player::incrementNumOfCountry()
{
	*numberOfCountryOwned = *numberOfCountryOwned + 1;
}

void Player::decrementNumOfCountry()
{
	*numberOfCountryOwned = *numberOfCountryOwned - 1;
}

void Player::setIndexOfCountry(int serialNum)
{
	int* temp = new int(serialNum);
	indexOfCountryOwned.push_back(temp);
}

void Player::setStrategy(Strategy* newStrategy) {
	this->playerStrategy = newStrategy;
}


int Player::getPlayerId()
{
	return *playerId;
}
int Player::getNumOwnedCountry()
{
	return *numberOfCountryOwned;
}
int Player::getSerialAt(int index) {
	return *indexOfCountryOwned[index];
}
const int Player::getActionsInStrat()
{
	return playerStrategy->getAction();
}
int Player::getArmies() {

	return *armies;
}

//-------------IAN A2P2 
//THIS FUNCTION WILL PLACE THE PLAYER'S INITITAL ARMY COUNT SPREAD OUT EVENLY THROUGHOUT THEIR COUNTRIES
//START UP PHASE USAGE ONLY

void Player::placeArmy()
{
	cout << "Here are all the countries you own, now placing initial armies:" << endl;

	int index;
	for (int i = 0; *armies != 0; i++)
	{
		if (i == indexOfCountryOwned.size()) {
			i = 0;
		}
		index = *indexOfCountryOwned[i];
		cout << "index:" << index - 1 << endl;
		cout << "Armies:" << *armies << endl;
		cout << GameEngine::getMap()->getCountry(index - 1)->getCountryName() << "(" << (i + 1) << ") " << endl;
		GameEngine::getMap()->getCountry(index - 1)->setArmyNumber((GameEngine::getMap()->getCountry(index - 1)->getNbOfArmies()) + 1);
		cout << "has " << GameEngine::getMap()->getCountry(index - 1)->getNbOfArmies() << " armies. " << endl
			<< endl;
		*armies = (*armies - 1);
		cout << "Decremented armies:" << *armies << endl;
		cout << "Size:" << indexOfCountryOwned.size() << endl;

	}

}

int Player::findIndex(int serialNum)
{
	int none = -1;
	int tempsize = indexOfCountryOwned.size();
	for (int i = 0; i < tempsize; i++)
	{
		if (*indexOfCountryOwned[i] == serialNum)
		{
			return i;
		}
	}
	return (none);
}

Hand* Player::getHand()
{
	return hand;
}

Dice* Player::getDice() {
	return dice;
}

