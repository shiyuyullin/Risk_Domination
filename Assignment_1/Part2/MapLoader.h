#pragma once
#include<string>
#include<iostream>
#include "Map.h"//The Map.h file's path
using namespace std;

//Target of the Adapter pattern.
class Maploader {
public:
	Map* loadingMap(string fileName);
	bool validateMap(vector<vector <int>>& edges);
	void traverse(int u, bool visited[], int numberOfCountries, vector<vector <int>>& edges);
};

//Class that  reads from Conquest files to create a map.
class DominationMaploader {
public:
	Map* loadingMap(string fileName);
	bool validateMap(vector<vector <int>>& edges);
	void traverse(int u, bool visited[], int numberOfCountries, vector<vector <int>>& edges);
};

class MaploaderAdapter : public Maploader {
public:

	DominationMaploader* mapLoaderAdaptee;
	Map* loadingMap(string fileName);
};
