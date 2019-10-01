#include <ostream>
#include "Dice.h"
#include <iostream>
#include "Player.h"
using namespace std;

int main() {
	Player player1;

	player1.RollDice();
	
	/*
	Here we will implement later a test on implementing the countries and
	deck (cards)
	I propose a vector of countries with a certain set of reserved
	memory slots (for each country)

	the card count should reflect the deck count but i do not think that
	will apply to the player class but the deck class instead
	.h file contains my variable names for that
	*/

	player1.attack();
	player1.foritfy();
	player1.reinforce();

}