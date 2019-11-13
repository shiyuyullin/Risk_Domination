#pragma once
#include<string>
#include<iostream>
#include "Map.h"//The Map.h file's path
using namespace std;

//Target of the Adapter pattern.
class Maploader {
public:
	static Map* loadingMap(string fileName);
};

//Class that  reads from Conquest files to create a map.
class DominationMaploader {
public:
	static Map* loadingMap(string fileName);
};

class MaploaderAdapter : public Maploader {
public:

	static DominationMaploader* mapLoaderAdaptee;
	static Map* loadingMap(string fileName);
};