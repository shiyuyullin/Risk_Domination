#pragma once
#include "Player.h"
class GameEngine {
private:
	int turn_decider;//Ian
	std::vector<Player*> turns;//an array that keeps trak who goes when(1,2,3,...N)//Ian
	

public:
	void order_of_play();//Ian
	void map_assign();//Ian
	const int number_of_armies_given(int AmtOfPlayers);//Ian

};
