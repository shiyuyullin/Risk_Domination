#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"//The Map.h file's path

int main() {

	Map* loadedMap;

	loadedMap = Maploader::loadingMap("ameroki");
	cout << loadedMap->arrOfCountries[0]->getCountryNumber() << endl;
	cout << loadedMap->arrOfCountries[0]->getCountryName() << endl;
	cout << loadedMap->arrOfCountries[0]->getContinent() << endl;






	
	return 0;

}