#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
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
	//Constructor
	Player();
	Player(int id, int armyCount);
	//Destructor
	~Player();
	//Getters
	int getNumOwnedCountry();
	int getPlayerID();
	int findIndex(int serialNum);//Finding the index of a country's serial number in the "indexOfCountryOwned"
	//Setters
	void setPlayerID(int id);
	//General Player functions
	void reinforce();
	void attack();
	void foritfy();
	//Dice Player association
	void RollDice(int n); //Test the dice obj for player
	void DisplayRollInfo(int n); // These two here are to be generally put together
	//Country Vector mods
	void incrementNumOfCountry();
	void decrementNumOfCountry();
	void setIndexOfCountry(int serialNum);//just pass in the countries serial number
	//A2P2 Ian start up phase function
	void placeArmy();
};
