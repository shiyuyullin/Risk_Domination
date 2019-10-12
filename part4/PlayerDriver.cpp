#include <ostream>
#include "Dice.h"
#include <iostream>
#include "Player.h"
using namespace std;

int main() {
	Player player1;
	player1.RollDice(5);
	player1.attack();
	player1.foritfy();
	player1.reinforce();
	int NumberOfCountries = 42;
	Deck deck(NumberOfCountries);
	player1.hand->addToHand(deck.draw());
	player1.hand->addToHand(deck.draw());
	player1.hand->addToHand(deck.draw());
	player1.hand->showHand();

}
