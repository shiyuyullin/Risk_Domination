#pragma once
#include <iostream>
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"//Path on my computer change it if needed
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"//Path on my computer change it if needed
#include <ostream>
#include <vector>
#include <algorithm>
class Map;
class GameEngine;

class Player{
private:
	Dice* dice;//player dices
	vector<int> indexOfCountryOwned;
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
	void setIndexOfCountry(int serialNum);//just pass in the countries serial number
};
