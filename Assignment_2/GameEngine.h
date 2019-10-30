#pragma once 
#include <vector>
#include <string>
#include "Cards.h"
#include "Dice.h"
#include "MapLoader.h"
#include "Player.h"
#include "Map.h"
using namespace std;

class GameEngine {
private:
	int turn_decider;
	std::vector<Player*> turns;//an array that keeps trak who goes when(1,2,3,...N)
	std::vector<Player*> players;//an array of player objects that will play per game
	
	int* numOfPlayers=new int;
	string* map_select = new string;
	vector <Player*> players;
	Maploader* map;
	Map* aMap;

public:
	void order_of_play();
	void map_assign();
	const int number_of_armies_given(int AmtOfPlayers);
	
	vector<string> getListOfMaps();
	void startGame();
	string* selectMap();
	int selectNumPlayers();

};
