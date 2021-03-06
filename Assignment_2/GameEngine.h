#pragma once 
#include <vector>
#include <string>

#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
#include "D:\Visual Studio\WorkSpace\a1_MapLoader\MapLoader.h"
#include "D:\Visual Studio\WorkSpace\Player\Player.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"
#include "D:\Visual Studio\WorkSpace\ObserverForGame\GameObservers.h"




using namespace std;

class GameEngine : public Subject {
private:
	vector<Player*> players;//an array of player objects that will play per game
	int* numOfPlayers;
	int* armyCnt;
	string* map_select;
	Maploader* map;
	static Map* gameMap;
	Deck* deck;
	vector<string> mapsToBePlayed;
	int* numOfMaps;
	int* gamesPlayed;
	int* maxNumberOfTurns;
	vector<string> winners;

public:
	//CONSTRUCTOR 
	GameEngine();
	GameEngine(int i);
	//Constructor to start a tournaments
	GameEngine(int numOfMaps, int numOfPlayers, int gamesPlayed, int maximumNumberOfTurns);
	//DESTRUCTOR
	~GameEngine();
	vector<string> getListOfMaps();
	void startGame();
	void startTournament();
	string* selectMap();
	void selectMaps(int numbOfMaps);
	static Map* getMap();
	int selectNumPlayers(int maxNumberOfPlayers);
	bool testVictoryCondition();
	//A2P2 START UP PHASE USAGE ONLY
	void map_assign_startUp();// call this first
	void placeArmies_startUpPhase();//then this one
	void setMap(Map* GameMap);//For testing purpose
	const int number_of_armies_given(int AmtOfPlayers);
	vector<Player*>getPlayers() { return players; }  //Accessor for vector of players in game (used in GameStatisticsObserver)
	vector<string> getWinners() { return winners; }
	inline const int getWinnerCount() { return winners.size(); }
	int getNumOfPlayers() { return *numOfPlayers; };
};