#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"

int main() {

	map loadedMap;

	loadedMap = Maploader::loadingMap("ameroki");
	cout << loadedMap.countries[0]->getSerialNumber() << endl;
	cout << loadedMap.countries[0]->getCountryName() << endl;
	cout << loadedMap.countries[0]->getContinent() << endl;
	loadedMap.countries[0]->displayBorders();//checking the contents

	loadedMap = Maploader::loadingMap("invMap");//invalid map

	map anotherMap1 = Maploader::loadingMap("luca");
	cout << anotherMap1.continents[0]->getSerialNum() << endl;
	cout << anotherMap1.continents[0]->getName() << endl;//checking the contents
	cout << anotherMap1.continents[0]->getReward() << endl;


	map anotherMap2 = Maploader::loadingMap("eurasien");
	map anotherMap3 = Maploader::loadingMap("roman_empire");








	
	return 0;

}