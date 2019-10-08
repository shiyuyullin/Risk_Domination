#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"

int main() {

	map loadedMap;
	loadedMap = Maploader::loadingMap("ameroki.txt");
	cout << loadedMap.countries[0]->getBoarders(0) << endl;
	return 0;

}