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
	{//Prompt player to select map and store


		map_select = new string();
		map_select = selectMap();
		gameMap = map->loadingMap(*map_select);
		while (gameMap->validateMap()==false) {
		map_select = selectMap();
		gameMap = map->loadingMap(*map_select);
		
		if (gameMap->validateMap() == false)
			cout << endl<<"Invalid map. Map rejected. Select again.";
	}


	//create deck
		deck = new Deck(gameMap->getNumOfCountries());
		cout << endl << "Number of cards in deck: ";
		cout << deck->sizeOfDeck() << endl;

		//Creating new playersfor the players vector
		numOfPlayers = new int();
		*numOfPlayers = selectNumPlayers();
		armyCnt = new int();
		*armyCnt = number_of_armies_given(*numOfPlayers);
		for (int i = 1; i <= *numOfPlayers; i++) {
		players.push_back(new Player(i, *armyCnt));
		players[(i-1)]->setStrategy(new humanPlayer);
		}
		// Shuffle Player Vector To Randomly Determine the order of play
		for (int i = 0; i < players.size() - 1; i++) {
			int j = i + rand() % (players.size() - i);
			swap(players[i], players[j]);
		}
		//Just to test the turns 
		for (int i = 0; i < players.size(); i++)
			std::cout << "Turn " << (i + 1) << " goes to player: " << players[i]->getPlayerId() << endl;
	}
	else {
		std::cout << "Exiting game, goodbye" << endl;
		exit(0);
	}



}

GameEngine::GameEngine(int i) {
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


void GameEngine::startGame()
{	//Observer call
		
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
					msg = "Player " + to_string(playerTurn)+" has " +
						to_string(players[i]->getNumOwnedCountry())
						+" countries to reinforce for this phase and will now reinforce\n";
					Notify(playerTurn, 1, msg);
					
					players[i]->reinforce();

					//The player has done this this and this
					//OBSERVER CALL
					msg = "Player " + to_string(playerTurn) + " has " +
						to_string(players[i]->getNumOwnedCountry())
						+ " countries and reinforced " + to_string(players[i]->getActionsInStrat())
						+ " countries for this phase" ;
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
				{//OBSERVER CALL
					msg = "Player " + to_string(playerTurn) + " will  now attack for this phase\n";
					Notify(playerTurn, 2, msg);
					
					players[i]->attack();
					//OBSERVER CALL
					msg = "Player " + to_string(playerTurn) + " succesfully attacked "
						+ to_string(players[i]->getActionsInStrat()) +" countries and now owns: "
						+ to_string(players[i]->getNumOwnedCountry()) + " countries";
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
					msg = "Player " + to_string(playerTurn) + " has now  finished their forticfication phase and has fortified "
						+ to_string(players[i]->getActionsInStrat()) + " countries.";
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


string* GameEngine::selectMap() {

	vector <string> list = getListOfMaps();
	int choice = 0;
	cout << "Select a map from the following list to play!" << endl;
	int i = 1;
	for (auto str : list)
		std::cout << "(" << i++ << ") " << str << std::endl;

	while (choice < 1 || choice >= i) {
		cout << endl << "Enter Map choice: ";
		cin >> choice;
		if (choice < 1 || choice >= i)
			cout << "Invalid Option. Try again." << endl;
	}

	*map_select = list[choice - 1];

	return map_select;
}

vector<string> GameEngine::getListOfMaps()
{
	string dirPath = "./Maps";

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

int GameEngine::selectNumPlayers() {
	int num = 0;
	cout << "========================" << endl;;
	cout << "Select Number of Players" << endl;
	cout << "========================" << endl;


	cout << "(2)	 2 Players" << endl;
	cout << "(3)	 3 Players" << endl;
	cout << "(4)	 4 Players" << endl;
	cout << "(5)	 5 Players" << endl;
	cout << "(6)	 6 Players" << endl;

	while (num < 2 || num >6) {
		cout << "Enter Number of Players in this game: ";
		cin >> num;
		if (num < 2 || num >6)
			cout << "Invalid number of players. Try again." << endl;
	}


	return num;
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
	for (int i = 0; i < getMap()->getNumOfCountries(); i++) {
		getMap()->getCountry(i)->setOwner(players[player_tracker]);
		players[player_tracker]->setIndexOfCountry(gameMap->getCountry(i)->getCountryNumber());
		players[player_tracker]->incrementNumOfCountry();
		player_tracker++;
		if (player_tracker == players.size())
			player_tracker = 0;
	}


}
void GameEngine::placeArmies_startUpPhase()//A2P2 IAN
{
	//OBSERVER CALL
	string msg = "Assinging the start up countries of the game!\n";
	Notify(0, 0, msg);
	
	int player_tracker = 0;
	for (int i = 0; i < getMap()->getNumOfCountries(); i++) {
		getMap()->getCountry(i)->setOwner(players[player_tracker]);
		players[player_tracker]->setIndexOfCountry(gameMap->getCountry(i)->getCountryNumber());
		players[player_tracker]->incrementNumOfCountry();
		player_tracker++;
		if (player_tracker == players.size())
			player_tracker = 0;
	}

}

void GameEngine::setMap(Map* GameMap) {
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




Map* GameEngine::getMap() {
	return gameMap;
}


void GameEngine::testPart3AND4() {
	//Part3 And 4
// 	//FOR TESTING PURPOSES----------------------------------------------------------------
	Map* testMap = new Map();
	Player* testPlayer = new Player();
	testPlayer->setPlayerId(1);

	Country* tempCountry1 = new Country();
	tempCountry1->setCountryName("Canada");
	tempCountry1->setCountryNumber(1);
	tempCountry1->setOwner(testPlayer);
	testMap->setCountry(tempCountry1);

	Country* tempCountry2 = new Country();
	tempCountry2->setCountryName("USA");
	tempCountry2->setCountryNumber(2);
	tempCountry2->setOwner(testPlayer);
	testMap->setCountry(tempCountry2);

	Country* tempCountry3 = new Country();
	tempCountry3->setCountryName("Mexico");
	tempCountry3->setCountryNumber(2);
	tempCountry3->setOwner(testPlayer);
	testMap->setCountry(tempCountry3);

	Country* tempCountry4 = new Country();
	tempCountry4->setCountryName("France");
	tempCountry4->setCountryNumber(3);
	tempCountry4->setOwner(testPlayer);
	testMap->setCountry(tempCountry4);

	Country* tempCountry5 = new Country();
	tempCountry5->setCountryName("England");
	tempCountry5->setCountryNumber(4);
	tempCountry5->setOwner(testPlayer);
	testMap->setCountry(tempCountry5);

	Country* tempCountry6 = new Country();
	tempCountry6->setCountryName("Spain");
	tempCountry6->setCountryNumber(5);
	tempCountry6->setOwner(testPlayer);
	testMap->setCountry(tempCountry6);

	int numberOfCountries = testMap->getNumOfCountries();
	Player* owner = testMap->getCountry(0)->getOwner();
	bool finsihed = true;

	for (int i = 1; i < numberOfCountries; i++)
	{

		Player* tempOwner = testMap->getCountry(i)->getOwner();
		if (owner != tempOwner)
		{
			finsihed = false;
			break;
		}
	}

	cout << finsihed << endl;

	//FOR TESTING PURPOSES----------------------------------------------------------------

	Card* card1 = new Card(1);
	Card* card2 = new Card(1);
	Card* card3 = new Card(1);
	Card* card4 = new Card(1);
	Card* card5 = new Card(1);
	Card* card6 = new Card(2);
	Card* card7 = new Card(2);
	Card* card8 = new Card(2);
	Card* card9 = new Card(2);
	Card* card10 = new Card(3);
	Card* card11 = new Card(3);
	Card* card12 = new Card(3);
	Card* card13 = new Card(3);
	Card* card14 = new Card(3);
	Card* card15 = new Card(3);
	
	testPlayer->getHand()->addToHand(card1);
	testPlayer->getHand()->addToHand(card2);
	testPlayer->getHand()->addToHand(card3);
	testPlayer->getHand()->addToHand(card4);
	testPlayer->getHand()->addToHand(card5);
	testPlayer->getHand()->addToHand(card6);
	testPlayer->getHand()->addToHand(card7);
	testPlayer->getHand()->addToHand(card8);
	testPlayer->getHand()->addToHand(card9);
	testPlayer->getHand()->addToHand(card10);
	testPlayer->getHand()->addToHand(card11);
	testPlayer->getHand()->addToHand(card12);
	testPlayer->getHand()->addToHand(card13);
	testPlayer->getHand()->addToHand(card14);
	testPlayer->getHand()->addToHand(card15);

	testPlayer->reinforce();
}

