#pragma once 
#include <vector>
#include <string>
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
#include "D:\Visual Studio\WorkSpace\a1_MapLoader\MapLoader.h"
#include "D:\Visual Studio\WorkSpace\Player\Player.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"
using namespace std;

class GameEngine {
private:
	std::vector<Player*> players;//an array of player objects that will play per game
	int* numOfPlayers;
	string* map_select;
	Maploader* map;
	static Map* gameMap;

public:
	
	vector<string> getListOfMaps();
	void startGame();
	string* selectMap();
	int selectNumPlayers();
	static Map* getMap() {};
	bool testVictoryCondition(Map* gameMap);
	int CalculatePlayerOwnership(int playerId);
	//Ian functions:
	void map_assign();// call this first
	void placeArmies(int n);//then this one
	const int number_of_armies_given(int AmtOfPlayers);
};
