#pragma once
#include <iostream>
#include "Dice.h"
#include <ostream>
#include <vector>
#include "Part1/Map.h"


class Player{
private:
	Dice* dice;//player dices
	//Countries needed
	Hand* hand;
	int* playerId;

public:
	Player();
	Player(int id);
	~Player();
	void reinforce();
	void attack();
	void foritfy();
	void RollDice(int n); //Test the dice obj for player
	void DisplayRollInfo(int n); // These two here are to be generally put together
	void setPlayerId(int id);
	int getPlayerId();
};
