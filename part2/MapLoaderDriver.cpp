#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"

int main() {

	map loadedMap;
	loadedMap = Maploader::loadingMap("ameroki.txt");

	return 0;

}