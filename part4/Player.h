#pragma once
#include <iostream>
#include "Dice.h"
#include <ostream>
#include <vector>
class Player{
protected:
	Dice dice;//player dices

	//Map class that will be implemented later and it'll have its countires the player owns
	/*std::vector<Map> countries;
	countries.reserve(20);
	*/
	
	//there must be a static counter to keep track on how many countries there are. This information is
	//needed to know how many cards there will be and how many spaces i can make in my array.
	//Deck deck

public:
	Player();
	void reinforce();
	void attack();
	void foritfy();
	void RollDice();
};