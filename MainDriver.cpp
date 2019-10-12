#include <ostream>
#include "Dice.h"
#include <iostream>
#include "Player.h"
#include "Map.h"
using namespace std;

int main() {
	Dice test;
	cout << "Dice------------"<<endl;
	test.DiceMain();
	cout << "Player------------"<<endl;
	Player player1;
	player1.RollDice(3);
	player1.attack();
	player1.foritfy();
	player1.reinforce();
	player1.DisplayRollInfo(3);
	mapTestFunction();
	return 0;
}
