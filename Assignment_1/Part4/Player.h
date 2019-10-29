#pragma once
#include <iostream>
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include <ostream>
#include <vector>

class Player{
private:
	Dice* dice;//player dices
	int* indexOfCountryOwned;
	Hand* hand;
	int* numberOfCountryOwned;

public:
	Player();
	~Player();
	void reinforce();
	void attack();
	void foritfy();
	void RollDice(int n); //Test the dice obj for player
	void DisplayRollInfo(int n); // These two here are to be generally put together
	void incrementNumOfCountry();
};
