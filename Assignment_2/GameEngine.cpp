#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include "GameEngine.h"


using namespace std;
namespace fs = std::experimental::filesystem;

#include <experimental/filesystem>


void GameEngine::startGame() {
	int choice=0;

	//Do you want to start a new game?
	cout << "(1) START NEW GAME" << endl;
	cout << "(2) EXIT"<<endl;	

	while (choice < 1 || choice > 2) {
		cin>> choice;
		if (choice < 1 || choice > 2)
			cout << "Invalid Choice. Try again" << endl;
	}

	//if yes then start game
	if (choice == 1) {
		

		//1.select map method
		map_select = selectMap();
		//2.select number of players method
		*numOfPlayers = selectNumPlayers();
		//3. use map loader to loap selected map
		aMap = map->loadingMap(*map_select); //check for exceptions
		//4. create array of  players 
		for (int i = 1; i <= *numOfPlayers; i++) {
			players.push_back(new Player);
		}

		//5.create a deck of cards
		Deck deck(aMap->getNumOfCountries());
		//6.assign empty hands of cards to each player

		cout << "Success";
	}

	else		
		exit(0);
}

vector<string> GameEngine::getListOfMaps() {
	
	string dirPath = ".";


	vector<string> listOfFiles;
	try {

		if (fs::exists(dirPath)) {
			fs::recursive_directory_iterator iter(dirPath);
			fs::recursive_directory_iterator end;
			
			while (iter != end) {
				listOfFiles.push_back(iter->path().stem().string());
				error_code ec;
				iter.increment(ec);
				if (ec) 
					std::cerr << "Error While Accessing : " << iter->path().string() << " :: " << ec.message() << '\n';
				
			}

		}
		else {
			cout <<"Error! This directory doesn't exist.";
		}
	}
	catch (std::system_error& e)
	{
		std::cerr << "Exception : " << e.what();
	}
	return listOfFiles;
	
}

string* GameEngine::selectMap() {

	vector <string> list = getListOfMaps();
	int choice=0;
	cout << "Select a map from the following list to play!" << endl;
	int i = 1;
	for (auto str : list)
		std::cout <<"("<<i++<<") "<< str << std::endl;
	while (choice < 1 || choice >= i) {
		cout << endl<< "Enter Map choice: ";
		cin>>choice;
		if (choice < 1 || choice >= i) 
			cout << "Invalid Option. Try again." << endl;		
	}
	
	*map_select = list[choice-1];

	return map_select;
	
	


}

int GameEngine::selectNumPlayers() {
	int num=0;
	cout << "========================" << endl;;
	cout << "Select Number of Players" << endl;
	cout << "========================" << endl;

	cout << "(1)	 1 Player" << endl;
	cout << "(2)	 2 Players" << endl;
	cout << "(3)	 3 Players" << endl;
	cout << "(4)	 4 Players" << endl;
	cout << "(5)	 5 Players" << endl;
	cout << "(6)	 6 Players" << endl;
	
	while (num < 1 || num >6) {
		cout << "Enter Number of Players in this game: ";
		cin >> num;
		if (num < 1 || num >6)
			cout << "Invalid number of players. Try again." << endl;
	}
	//Add code for exceptions 

	return num;
}
