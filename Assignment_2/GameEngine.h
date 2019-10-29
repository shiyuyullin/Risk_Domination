#pragma once
#include "Player.h"
class GameEngine {
private:
	int turn_decider;
	std::vector<Player*> turns;//an array that keeps trak who goes when(1,2,3,...N)
	std::vector<Player*> players;//an array of player objects that will play per game

public:
	void order_of_play();
	void map_assign();
	const int number_of_armies_given(int AmtOfPlayers);

};
