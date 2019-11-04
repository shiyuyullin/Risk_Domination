#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <experimental/filesystem>
#include "GameEngine.h"

using namespace std;
namespace fs = std::experimental::filesystem;

#include <experimental/filesystem>
Map* GameEngine::gameMap; //This is extremely necessary to have if we declare a static variable in out .h file
//Constructor
GameEngine::GameEngine()
{
	//Initializing all data members 
	map_select = new string("");
	numOfPlayers = new int(0);
	//map_select = selectMap();
	//Creating new playersfor the players vector
	*numOfPlayers = selectNumPlayers();
	*armyCnt = number_of_armies_given(*numOfPlayers);
	gameMap = map->loadingMap(*map_select); //check for excepti
	for (int i = 1; i <= *numOfPlayers; i++)
		players.push_back(new Player(i,*armyCnt));
	// Shuffle Player Vector To Randomly Determine the order of play 
	// of the players. Uses Fisher–Yates shuffle. A2P2 Ian
	for (int i = 0; i < players.size() - 1; i++) {
		int j = i + rand() % (players.size() - i);
		swap(players[i], players[j]);
	}
	//Just to test the turns 
	for (int i = 0; i < players.size(); i++)
		cout << "Turn " << (i + 1) << " goes to: " << players[i]->getPlayerID() << endl;

}
//destructor
GameEngine::~GameEngine()
{
	for (int i = 0; i < *numOfPlayers; i++)
		delete players[i];
	delete numOfPlayers;
	delete map_select;
}

const int GameEngine::number_of_armies_given(int AmtOfPlayers)//A2P2 IAN
{

	switch (AmtOfPlayers)
	{
		std::cout << "Number of players: " << AmtOfPlayers << endl;
	case 2:
		std::cout << "Each player will have: 40 armies" << endl;
		return 40;
	case 3:
		std::cout << "Each player will have: 35 armies" << endl;
		return 35; 
	case 4: 
		std::cout << "Each player will have: 30 armies" << endl;
		return 30;
	case 5:
		std::cout << "Each player will have: 25 armies" << endl;
		return 25;
	case 6: 
		std::cout << "Each player will have: 20 armies" << endl;
		return 20; 
	default:
			return 0;
	}
}
void GameEngine::map_assign_startUp()//A2P2 IAN
{
	cout << "Assinging the start up countries of the game!"<<endl;
	int player_tracker = 0;
	for (int i = 0; i < gameMap->getNumOfCountries(); i++) {
		gameMap->getCountry(i)->setOwner(players[player_tracker]);
		players[player_tracker]->setIndexOfCountry(gameMap->getCountry(i)->getCountryNumber());
		players[player_tracker]->incrementNumOfCountry();
		player_tracker++;
		if (player_tracker == players.size())
			player_tracker = 0;
	}

}
void GameEngine::placeArmies_startUpPhase()//A2P2 IAN
{
	cout << "Each player must place their army (" << *armyCnt << ") in all of their coutries!" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << "Player " << players[i]->getPlayerId() << "!" << endl;
		players[i]->placeArmy();
		cout << "\n\n";
	}

}
void GameEngine::startGame()
{
	int choice = 0;

	//Do you want to start a new game?
	cout << "(1) START NEW GAME" << endl;
	cout << "(2) EXIT" << endl;

	while (choice < 1 || choice > 2)
	{
		cin >> choice;
		if (choice < 1 || choice > 2)
			cout << "Invalid Choice. Try again" << endl;
	}

	//if yes then start game
	if (choice == 1)
	{

		bool gameIsFinished = false;

		while (!gameIsFinished)
		{

			for (int i = 0; i < *numOfPlayers; i++)
			{

				int playerTurn = players[i]->getPlayerID();
				cout << "It is player " << playerTurn << "'s turn." << endl;

				// REINFORCE PHASE
				cout << "Would you like to Reinforce your board this turn, Yes(1) or No(2) ?: ";
				choice = 0;
				while (choice < 1 || choice > 2)
				{
					cin >> choice;
					if (choice < 1 || choice > 2)
						cout << "Invalid Choice. Try again" << endl;
				}

				if (choice == 1)
				{

					players[i]->reinforce();
				}
				else
				{
					cout << "On to the next step. " << endl;
				}

				// ATTACK PHASE
				choice = 0;

				cout << "Would you like to Attack this turn, Yes(1) or No(2) ?: ";
				while (choice < 1 || choice > 2)
				{
					cin >> choice;
					if (choice < 1 || choice > 2)
						cout << "Invalid Choice. Try again" << endl;
				}

				if (choice == 1)
				{
					players[i]->attack();
				}
				else
				{
					cout << "On to the next step. " << endl;
				}

				// FORTIFICATION PHASE
				choice = 0;

				cout << "Would you like to fortify your board this turn, Yes(1) or No(2) ?: ";
				while (choice < 1 || choice > 2)
				{
					cin >> choice;
					if (choice < 1 || choice > 2)
						cout << "Invalid Choice. Try again" << endl;
				}

				if (choice == 1)
				{
					players[i]->foritfy();
				}
				else
				{
					cout << "Your turn is coming to an end. " << endl;
				}
				if (testVictoryCondition())
				{
					cout << "The Game is Over, Player " << playerTurn << " wins!" << endl;;
					gameIsFinished = true;
				}
			}
		}
	}

	else
		exit(0);
}

vector<string> GameEngine::getListOfMaps()
{

	string dirPath = ".";

	vector<string> listOfFiles;
	try
	{

		if (fs::exists(dirPath))
		{
			fs::recursive_directory_iterator iter(dirPath);
			fs::recursive_directory_iterator end;

			while (iter != end)
			{
				listOfFiles.push_back(iter->path().stem().string());
				error_code ec;
				iter.increment(ec);
				if (ec)
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
			}
		}
		else
		{
			cout << "Error! This directory doesn't exist.";
		}
	}
	catch (std::system_error &e)
	{
		std::cerr << "Exception : " << e.what();
	}
	return listOfFiles;
}

string *GameEngine::selectMap()
{

	vector<string> list = getListOfMaps();
	int choice = 0;
	cout << "Select a map from the following list to play!" << endl;
	int i = 1;
	for (auto str : list)
		std::cout << "(" << i++ << ") " << str << std::endl;
	while (choice < 1 || choice >= i)
	{
		cout << endl
			 << "Enter Map choice: ";
		cin >> choice;
		if (choice < 1 || choice >= i)
			cout << "Invalid Option. Try again." << endl;
	}

	*map_select = list[choice - 1];

	return map_select;
}

int GameEngine::selectNumPlayers()
{
	int num = 0;
	cout << "========================" << endl;
	;
	cout << "Select Number of Players" << endl;
	cout << "========================" << endl;

	cout << "(2)	 2 Players" << endl;
	cout << "(3)	 3 Players" << endl;
	cout << "(4)	 4 Players" << endl;
	cout << "(5)	 5 Players" << endl;
	cout << "(6)	 6 Players" << endl;

	while (num < 2 || num > 6)
	{
		cout << "Enter Number of Players in this game: ";
		cin >> num;
		if (num < 2 || num > 6)
			cout << "Invalid number of players. Try again." << endl;
	}
	//Add code for exceptions

	return num;
}

const int GameEngine::number_of_armies_given(int AmtOfPlayers)
{

	switch (AmtOfPlayers)
	{
		std::cout << "Number of players: " << AmtOfPlayers << endl;
	case 2:
		std::cout << "Each player will have: 40 armies" << endl;
		return 40; break;
	case 3:
		std::cout << "Each player will have: 35 armies" << endl;
		return 35; break;
	case 4: 
		std::cout << "Each player will have: 30 armies" << endl;
		return 30; break;
	case 5:
		std::cout << "Each player will have: 25 armies" << endl;
		return 25; break;
	case 6: 
		std::cout << "Each player will have: 20 armies" << endl;
		return 20; break;
	}
}

bool GameEngine::testVictoryCondition()
{

	int numberOfCountries = gameMap->getNumOfCountries();
	Player* owner = gameMap->getCountry(0)->getOwner();

	for (int i = 1; i < numberOfCountries; i++)
	{

		Player* tempOwner = gameMap->getCountry(i)->getOwner();
		if (owner != tempOwner)
		{
			return false;
		}
	}

	return true;
}

int GameEngine::CalculatePlayerOwnership(int playerId){

	int controlledCountries = 0;
	int counter = gameMap->getNumOfCountries();
	for (int i = 0; i < counter; i++)
	{

		int tempOwner = gameMap->getCountry(i)->getOwner()->getPlayerID();
		if (playerId == tempOwner)
		{
			controlledCountries++;
		}
	}
	return controlledCountries;
}

Map* GameEngine::getMap() {
	return gameMap;
}
