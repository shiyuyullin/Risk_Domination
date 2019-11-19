﻿#include "PlayerStrategies.h"
#include "D:\Visual Studio\WorkSpace\Player\Player.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"
#include "D:\Visual Studio\WorkSpace\GameEngine\GameEngine.h" 
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include "D:\Visual Studio\WorkSpace\a1_MapLoader\MapLoader.h"
#include <iostream>


int main() {
	GameEngine* p = new GameEngine(2);
	Map* gameMap = Maploader::loadingMap("ameroki.txt");
	p->setMap(gameMap);
	Player* a = new Player();
	a->setStrategy(new aggressivePlayer);
	Player* b = new Player();
	Country* temp = new Country();

	for (int i = 0; i < gameMap->getNumOfCountries(); i++) {
		if (i % 2 == 0) {
			temp = gameMap->getCountry(i);
			temp->setArmyNumber(5);
			temp->setOwner(a);
			a->setIndexOfCountry(temp->getCountryNumber());
			a->incrementNumOfCountry();
		}
		else {
			temp = gameMap->getCountry(i);
			temp->setArmyNumber(5);
			temp->setOwner(b);
			b->setIndexOfCountry(temp->getCountryNumber());
			b->incrementNumOfCountry();
		}
	}
	a->reinforce();
	a->attack();
	a->foritfy();
	Country* tempC;
	for (int i = 0; i < a->getNumOwnedCountry(); i++) {
		tempC = gameMap->getCountry(a->getSerialAt(i) - 1);
		cout << tempC->getCountryNumber() << " " << tempC->getCountryName() << " " << tempC->getNbOfArmies() << endl;
	}
	cout << endl;
	cout << endl;

	a->setStrategy(new beneloventPlayer);
	a->reinforce();
	a->attack();
	a->foritfy();
	for (int i = 0; i < a->getNumOwnedCountry(); i++) {
		tempC = gameMap->getCountry(a->getSerialAt(i) - 1);
		cout << tempC->getCountryNumber() << " " << tempC->getCountryName() << " " << tempC->getNbOfArmies() << endl;
	}



	return 0;
}