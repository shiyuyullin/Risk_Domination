#pragma once
#include <iostream>
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include "D:\Visual Studio\WorkSpace\PlayerStrategies\PlayerStrategies.h"
#include <ostream>
#include <vector>
#include <algorithm>

class Map;
class GameEngine;

class Player {
private:
	Dice* dice;//player dices
	vector<int*> indexOfCountryOwned;
	Hand* hand;
	int* numberOfCountryOwned;
	int* playerId;
	int* armies;
	Strategy* playerStrategy;
	int* actionsDoneInStrat;

public:
	//Constructor
	Player();
	Player(int id, int armyCount);
	//Destructor
	~Player();
	//Getters
	int getNumOwnedCountry();
	int findIndex(int serialNum);//Finding the index of a country's serial number in the "indexOfCountryOwned"
	int getPlayerId();
	int getArmies();
	int getSerialAt(int index);
	const int getActionsInStrat();
	//Setters
	void setPlayerId(int id);
	void reinforce();
	void attack();
	void foritfy();
	void RollDice(int n); //Test the dice obj for player
	void DisplayRollInfo(int n); // These two here are to be generally put together
	void incrementNumOfCountry();
	void decrementNumOfCountry();
	void setIndexOfCountry(int serialNum);//just pass in the countries serial number
	void removeIndex(int index);
	//setStrategy will set the player to perform a specific behavior(human, aggressive, benevolent)
	void setStrategy(Strategy* newStrategy);
	//A2P2 Ian start up phase function
	void placeArmy();
	Hand* getHand();
	Dice* getDice();
	
	

};

