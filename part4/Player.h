#pragma once
#include <iostream>
#include "Dice.h"
#include <ostream>
#include <vector>
class Player{
private:
	Dice* dice;//player dices
	//Countries needed
	//Deck needed

public:
	Player();
	~Player();
	void reinforce();
	void attack();
	void foritfy();
	void RollDice(int n); //Test the dice obj for player
	void DisplayRollInfo(int n); // These two here are to be generally put together
};
