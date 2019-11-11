#pragma once
#include<string>
#include<iostream>
#include "Map.h"//The Map.h file's path
using namespace std;

class Maploader {
public:
	static Map* loadingMap(string fileName);
};

class DominationMaploader {
public:
	static Map* loadingMap(string fileName);
};

class MaploaderAdapter {
public:
	static Map* loadingMap(string fileName);
};