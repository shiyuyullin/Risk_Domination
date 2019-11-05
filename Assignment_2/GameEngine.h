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
	int* armyCnt;
	string* map_select;
	Maploader* map;
	static Map* gameMap;
	Deck* deck;

public:
	//CONSTRUCTOR 
	GameEngine();
	//DESTRUCTOR
	~GameEngine();
	vector<string> getListOfMaps();
	void startGame();
	string* selectMap();
	static Map* getMap();
	int selectNumPlayers();
	bool testVictoryCondition();
	//A2P2 START UP PHASE USAGE ONLY
	void map_assign_startUp();// call this first
	void placeArmies_startUpPhase();//then this one
	const int number_of_armies_given(int AmtOfPlayers);
	void testPart3AND4();
};

