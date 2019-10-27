#pragma once
#include<string>
#include<iostream>
#include "D:\Visual Studio\WorkSpace\Map\Map.h"//The Map.h file's path
using namespace std;

class Maploader {
public:
	static Map* loadingMap(string fileName);
};