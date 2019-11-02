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
	int* numOfPlayers=new int;
	string* map_select = new string;
	vector <Player*> players;
	Maploader* map;
	Map* gameMap;

public:
	
	vector<string> getListOfMaps();
	void startGame();
	string* selectMap();
	int selectNumPlayers();
	Map* getMap() { return aMap; };
	bool testVictoryCondition(Map* gameMap);
	int CalculatePlayerOwnership(int playerId);
	//Ian functions:
	void map_assign();// call this first
	void placeArmies(int n);//then this one
	const int number_of_armies_given(int AmtOfPlayers);
};
