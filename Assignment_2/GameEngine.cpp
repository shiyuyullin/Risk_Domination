#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <filesystem>
#include "GameEngine.h"

using namespace std;
namespace fs = filesystem;
Map* GameEngine::gameMap;

//Constructor
GameEngine::GameEngine()
{
	int choice = 0;

	//Do you want to start a new game?
	cout << "(1) START NEW GAME" << endl;
	cout << "(2) EXIT" << endl;
	cout << "--> ";
	while (choice < 1 || choice > 2)
	{
		cin >> choice;
		if (choice < 1 || choice > 2)
			cout << "Invalid Choice. Try again" << endl;
	}

	//if yes then start game
	if (choice == 1)
	{ //Prompt player to select map and store

		map_select = new string();
		map_select = selectMap();
		gameMap = map->loadingMap(*map_select);
		while (gameMap->validateMap() == false)
		{
			map_select = selectMap();
			gameMap = map->loadingMap(*map_select);

			if (gameMap->validateMap() == false)
				cout << endl
				<< "Invalid map. Map rejected. Select again.";
		}

		//create deck
		deck = new Deck(gameMap->getNumOfCountries());
		cout << endl
			<< "Number of cards in deck: ";
		cout << deck->sizeOfDeck() << endl;

		//Creating new playersfor the players vector
		numOfPlayers = new int();
		*numOfPlayers = selectNumPlayers(6);
		armyCnt = new int();
		*armyCnt = number_of_armies_given(*numOfPlayers);
		for (int i = 1; i <= *numOfPlayers; i++)
		{
			players.push_back(new Player(i, *armyCnt));
			players[(i - 1)]->setStrategy(new humanPlayer);
		}
		// Shuffle Player Vector To Randomly Determine the order of play
		for (int i = 0; i < players.size() - 1; i++)
		{
			int j = i + rand() % (players.size() - i);
			swap(players[i], players[j]);
		}
		//Just to test the turns
		for (int i = 0; i < players.size(); i++)
			std::cout << "Turn " << (i + 1) << " goes to player: " << players[i]->getPlayerId() << endl;
	}
	else
	{
		std::cout << "Exiting game, goodbye" << endl;
		exit(0);
	}
}

GameEngine::GameEngine(int i)
{
	numOfPlayers = new int(i);
}

//destructor
GameEngine::~GameEngine()
{

	for (int i = 0; i < *numOfPlayers; i++)
		delete players[i];
	delete numOfPlayers;
	delete armyCnt;
	delete map_select;
	delete map;
	delete gameMap;
	delete deck;
}
GameEngine::GameEngine(int numbOfMaps, int numbOfPlayers, int rounds, int maximumNumberOfTurns)
{
	numOfMaps = new int(numbOfMaps);
	maxNumberOfTurns = new int(maximumNumberOfTurns * numbOfPlayers);
	//mapsToBePlayed = selectMaps(numOfMaps);
	selectMaps(numbOfMaps);
	gamesPlayed = new int(rounds);
	numOfPlayers = new int(numbOfPlayers);
	armyCnt = new int(number_of_armies_given(numbOfPlayers));

	//Need to add Map Validation

	//this is the main game Loop

}

void GameEngine::startTournament()
{
	for (int i = 0; i < *numOfMaps; i++)
	{
		cout << "You are playing on " << mapsToBePlayed[i] << " map." << endl;

		for (int j = 0; j < *gamesPlayed; j++)
		{
			int counter = 0;
			for (int k = 1; k <= *numOfPlayers; k++)
			{
				Player* temp = new Player(k, *armyCnt);
				players.push_back(temp);
				players[(k - 1)]->setRandomStrategy();
				cout << players[(k - 1)]->getPlayerType() << " player type will be playing as player " + to_string(k) + "\n";
			}
			// Shuffle Player Vector To Randomly Determine the order of play
			for (int i = 0; i < players.size() - 1; i++)
			{
				int f = i + rand() % (players.size() - i);
				swap(players[i], players[f]);
			}

			for (int i = 0; i < players.size(); i++)
				std::cout << "Turn " << (i + 1) << " goes to player: " << players[i]->getPlayerId() << endl;

			gameMap = map->loadingMap(mapsToBePlayed[i]);
			deck = new Deck(gameMap->getNumOfCountries());
			cout << endl
				<< "Number of cards in deck: ";
			cout << deck->sizeOfDeck() << endl;

			map_assign_startUp(); //Assign random countries to the players, start up phase setting
			//string msg = "Initializing the game's startup phase...\n";
			//Notify(-1, 0, msg);
			placeArmies_startUpPhase(); //Place all of the player's army count around their countries
			bool gameIsFinished = false;
			while (!gameIsFinished )
			{

				for (int i = 0; i < *numOfPlayers; i++)
				{
					//OBSERVER CALL
					int playerTurn = players[i]->getPlayerId();//create a type for player like player is a cheater, or a aggressive instead of numeric
					//msg = "";
					//Notify(playerTurn, 1, msg);

					//REINFORCE AI
					//msg = players[i]->getPlayerType + " has " +
					//	to_string(players[i]->getNumOwnedCountry()) + " countries to reinforce for this phase and will now reinforce\n";
					//Notify(playerTurn, 1, msg);

					players[i]->reinforce();

					// 	//The player has done this this and this
					// 	//OBSERVER CALL
					//msg = players[i]->getPlayerType + " has " +
					//	to_string(players[i]->getNumOwnedCountry()) + " countries and reinforced " + to_string(players[i]->getActionsInStrat()) + " countries for this phase";
					//Notify(playerTurn, 1, msg);

					//OBSERVER CALL
					//msg = "";
					//Notify(playerTurn, 2, msg);

					//ATTACK PHASE
					//OBSERVER CALL
					//msg = "Player " + to_string(playerTurn) + " will  now attack for this phase\n";
					//Notify(playerTurn, 2, msg);

					players[i]->attack();
					// 	//OBSERVER CALL
					//msg = "Player " + to_string(playerTurn) + " succesfully attacked " + to_string(players[i]->getActionsInStrat()) + " countries and now owns: " + to_string(players[i]->getNumOwnedCountry()) + " countries";
					//Notify(playerTurn, 1, msg);

					// //OBSERVER CALL
					//msg = "";
					//Notify(playerTurn, 3, msg);

					// FORTIFICATION PHASE

					//msg = "Player " + to_string(playerTurn) + " will now fortify for this phase\n";
					//Notify(playerTurn, 3, msg);

					players[i]->foritfy();

					//Observer call
					//msg = "Player " + to_string(playerTurn) + " has now  finished their forticfication phase and has fortified " + to_string(players[i]->getActionsInStrat()) + " countries.";
					//Notify(playerTurn, 3, msg);
					counter++;
					cout << players[playerTurn - 1]->getPlayerType() << "\n";
					cout << "Your turn is coming to an end. " << endl;
					//msg = "Player " + to_string(playerTurn) + " has now  finished their turn for this phase...Moving on...";
					//Notify(playerTurn, -1, msg);
					if (testVictoryCondition() and counter == *maxNumberOfTurns) {
						cout << "The Game is Over, Player " << playerTurn << " wins!" << endl;
						gameIsFinished = true;
						winners.push_back(players[playerTurn - 1]->getPlayerType());
						for (int i = 0; i < players.size(); ++i) {
							cout << "BEFORE\n";
							delete players[i]; // Calls ~object and deallocates *tmp[i]
							cout << "AFTER\n";
						}
						players = vector<Player*>();
						break;
					}
					else if (testVictoryCondition()) {
						cout << "The Game is Over, Player " << playerTurn << " wins!" << endl;
						gameIsFinished = true;
						winners.push_back(players[playerTurn - 1]->getPlayerType());
						for (int i = 0; i < players.size(); ++i) {
							delete players[i]; // Calls ~object and deallocates *tmp[i]
						}
						players = vector<Player*>();
						break;
					}
					else if (counter == *maxNumberOfTurns) {
						cout << "The max number of turns has occured, the player who owns the most countries is the winner for this game is:\n";
						int max = 0;
						int index_of_winner = 0;
						for (int j = 0; j < players.size(); ++j)
						{
							if (players[j]->getNumOwnedCountry() > max) {
								max = players[j]->getNumOwnedCountry();
								index_of_winner = j;
							}
						}
						cout << players[index_of_winner]->getPlayerType() << endl;
						cout << "With " << players[index_of_winner]->getNumOwnedCountry() << " countries!\n";
						winners.push_back(players[index_of_winner]->getPlayerType());
						gameIsFinished = true;
						for (int i = 0; i < players.size(); ++i) {
							delete players[i]; // Calls ~object and deallocates *tmp[i]
						}
						players = vector<Player*>();
						break;
						//delete pointers restart
					}
				}
			}
		}
	}
}

void GameEngine::startGame()
{ //Observer call

	map_assign_startUp(); //Assign random countries to the players, start up phase setting
	string msg = "Initializing the game's startup phase...\n";
	Notify(-1, 0, msg);

	placeArmies_startUpPhase(); //Place all of the player's army count around their countries
	bool gameIsFinished = false;

	while (!gameIsFinished)
	{

		for (int i = 0; i < *numOfPlayers; i++)
		{
			//OBSERVER CALL
			int playerTurn = players[i]->getPlayerId();
			msg = "";
			Notify(playerTurn, 1, msg);

			// REINFORCE PHASE
			cout << "Would you like to Reinforce your board this turn, Yes(1) or No(2) ?: ";
			int choice = 0;
			while (choice < 1 || choice > 2)
			{
				cin >> choice;
				if (choice < 1 || choice > 2)
					cout << "Invalid Choice. Try again" << endl;
			}

			if (choice == 1)
			{
				//OBSERVER CALL
				msg = "Player " + to_string(playerTurn) + " has " +
					to_string(players[i]->getNumOwnedCountry()) + " countries to reinforce for this phase and will now reinforce\n";
				Notify(playerTurn, 1, msg);

				players[i]->reinforce();

				//The player has done this this and this
				//OBSERVER CALL
				msg = "Player " + to_string(playerTurn) + " has " +
					to_string(players[i]->getNumOwnedCountry()) + " countries and reinforced " + to_string(players[i]->getActionsInStrat()) + " countries for this phase";
				Notify(playerTurn, 1, msg);
			}
			else
			{
				cout << "On to the next step. " << endl;
			}

			//OBSERVER CALL
			msg = "";
			Notify(playerTurn, 2, msg);

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
			{ //OBSERVER CALL
				msg = "Player " + to_string(playerTurn) + " will  now attack for this phase\n";
				Notify(playerTurn, 2, msg);

				players[i]->attack();
				//OBSERVER CALL
				msg = "Player " + to_string(playerTurn) + " succesfully attacked " + to_string(players[i]->getActionsInStrat()) + " countries and now owns: " + to_string(players[i]->getNumOwnedCountry()) + " countries";
				Notify(playerTurn, 1, msg);
			}

			else
			{
				cout << "On to the next step. " << endl;
			}

			//OBSERVER CALL
			msg = "";
			Notify(playerTurn, 3, msg);

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
				//OBSERVER CALL
				msg = "Player " + to_string(playerTurn) + " will now fortify for this phase\n";
				Notify(playerTurn, 3, msg);

				players[i]->foritfy();

				//Observer call
				msg = "Player " + to_string(playerTurn) + " has now  finished their forticfication phase and has fortified " + to_string(players[i]->getActionsInStrat()) + " countries.";
				Notify(playerTurn, 3, msg);
			}
			else
			{
				cout << "Your turn is coming to an end. " << endl;
				msg = "Player " + to_string(playerTurn) + " has now  finished their turn for this phase...Moving on...";
				Notify(playerTurn, -1, msg);
			}
			if (testVictoryCondition())
			{
				cout << "The Game is Over, Player " << playerTurn << " wins!" << endl;
				gameIsFinished = true;
			}
		}
	}
}

string* GameEngine::selectMap()
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

void GameEngine::selectMaps(int numbOfMaps)
{

	vector<string>list = getListOfMaps();
	int choice = 0;
	cout << "Select " << numbOfMaps << " maps from the following list to play!" << endl;

	for (int i = 0; i < numbOfMaps; i++)
	{
		int x = 1;
		for (auto str : list)//display all available maps
			std::cout << "(" << x++ << ") " << str << std::endl;

		while (choice < 1 || choice >= x)
		{
			cout << endl
				<< "Enter Map choice: ";
			cin >> choice;
			if (choice < 1 || choice >= x)
				cout << "Invalid Option. Try again." << endl;
		}
		mapsToBePlayed.push_back(list[choice - 1]);
		cout << mapsToBePlayed[i] << " has been added to the playlist!" << endl;
		list.erase(list.begin() + (choice - 1));
		list.shrink_to_fit();
		choice = 0;
	}

}
vector<string> GameEngine::getListOfMaps()
{
	string dirPath = "./Map";

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
	catch (std::system_error& e)
	{
		std::cerr << "Exception : " << e.what();
	}
	return listOfFiles;
}

int GameEngine::selectNumPlayers(int maxNumberOfPlayers)
{
	int num = 0;
	cout << "========================" << endl;
	;
	cout << "Select Number of Players" << endl;
	cout << "========================" << endl;

	for (int i = 2; i <= maxNumberOfPlayers; i++)
	{
		cout << "(" << i << ")"
			<< "\t" << i << " Players" << endl;
	}

	while (num < 2 || num > maxNumberOfPlayers)
	{
		cout << "Enter Number of Players in this game: ";
		cin >> num;
		if (num < 2 || num > maxNumberOfPlayers)
			cout << "Invalid number of players. Try again." << endl;
	}

	return num;
}



const int GameEngine::number_of_armies_given(int AmtOfPlayers) //A2P2 IAN
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

void GameEngine::map_assign_startUp() //A2P2 IAN
{
	cout << "Assinging the start up countries of the game!" << endl;
	int player_tracker = 0;
	for (int i = 0; i < gameMap->getNumOfCountries(); i++)
	{
		gameMap->getCountry(i)->setOwner(players[player_tracker]);
		//ERRORS OCCUR HERE
		players[player_tracker]->setIndexOfCountry(gameMap->getCountry(i)->getCountryNumber());
		players[player_tracker]->incrementNumOfCountry();
		player_tracker++;
		if (player_tracker == players.size())
			player_tracker = 0;
	}
}
void GameEngine::placeArmies_startUpPhase() //A2P2 IAN
{
	//OBSERVER CALL
	string msg = "Assinging the start up countries of the game!\n";
	Notify(0, 0, msg);

	for (int i = 0; i < players.size(); i++)
	{
		players[i]->placeArmy();
	}
}

void GameEngine::setMap(Map* GameMap)
{
	gameMap = GameMap;
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

Map* GameEngine::getMap()
{
	return gameMap;
}