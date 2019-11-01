#pragma once
#include <iostream>
#include "Dice.h"
#include "Cards.h"
#include <ostream>
#include <vector>
class Map;

class Player{
private:
	Dice* dice;//player dices
	int* indexOfCountryOwned;
	Hand* hand;
	int* numberOfCountryOwned;
	int* playerId;
	int* armies;

public:
	Player();
	Player(int id, int armyCount);
	~Player();
	int getNumOwnedCountry();
	int findIndex(int serialNum);//Finding the index of a country's serial number in the "indexOfCountryOwned"
	int getPlayerID();
	void setPlayerID(int id);
	void reinforce();
	void attack();
	void foritfy();
	void RollDice(int n); //Test the dice obj for player
	void DisplayRollInfo(int n); // These two here are to be generally put together
	void incrementNumOfCountry();
	void decrementNumOfCountry();
	void setIndexOfCountry(int serialNum);
	void reOrganize();//if a player losses one of its country, reorganize his "indexOfCountryOwned"
};
