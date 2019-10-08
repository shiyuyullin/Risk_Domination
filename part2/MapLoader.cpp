#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"
using namespace std;


//Constructor and destructor for country class
country::country() {
	serialNum = new int(0);
	countryName = new string("none");
	continentBelong = new int(-1);
	for (int i = 0; i < 10; ++i) {
		boarders[i] = new int(0);
	}
}
//Setters for country class
void country::setSerialNum(int t) {
	*serialNum = t;
}
void country::setCountryName(string s) {
	*countryName = s;
}
void country::setContinent(int t) {
	*continentBelong = t;
}
void country::setBoarders(int index, int t) {
	*boarders[index] = t;
}
//Getters for country class
int country::getSerialNumber() {
	return *serialNum;
}
string country::getCountryName() {
	return *countryName;
}
int country::getContinent() {
	return *continentBelong;
}
int country::getBoarders(int index) {
	return *boarders[index];
}

//Constructor and destructor for continent class
continent::continent() {
	serialNumber = new int(-1);
	name = new string("none");
	rewards = new int(0);
}

//Setters for continent class
void continent::setserialNumber(int t) {
	*serialNumber = t;
}
void continent::setRewards(int t) {
	*rewards = t;
}
void continent::setName(string s) {
	*name = s;
}
//Getters for continent class
string continent::getName() {
	return *name;
}
int continent::getSerialNum() {
	return *serialNumber;
}
int continent::getReward() {
	return *rewards;
}

//Constructor and destructor for map class
map::map() {
	for (int i = 0; i < 60; ++i) {
		countries[i] = new country();
	}
	for (int i = 0; i < 10; ++i) {
		continents[i] = new continent;
	}
}
//Setters for map class
void map::setContinents(int index, continent* c) {
	continents[index] = c;
}
void map::setCountries(int index, country* c) {
	countries[index] = c;
}


//Implementation of validating function
//bool MapLoader::validator(string fileName) {

//}

//Implementation of loading function
map Maploader::loadingMap(string fileName) {
	ifstream inputFileStream(fileName);
	map resultMap;
	string temp = "";
	int numberOfCountries = 0;
	int numberOfContinents = 0;
	while (!inputFileStream.eof()) {
		int j = 0;
		inputFileStream >> temp;
		if (temp == "[continents]") {
			int rewards = 0;
			int i = 0;
			while (temp != "[countries]") {
				continent* tempContinent = new continent();
				inputFileStream >> temp;
				if (temp == "[countries]") {
					break;
				}
				tempContinent->setName(temp);
				inputFileStream >> rewards;
				tempContinent->setRewards(rewards);
				tempContinent->setserialNumber(i);
				inputFileStream >> temp;
				resultMap.setContinents(i, tempContinent);
				numberOfContinents++;
				i++;
			}
		}//All good until here 10.7 22:13

		string serialNumS = "";
		if (temp == "[countries]") {
			int continentBelong = 0;
			int ignore = 0;
			int k = 0;
			int serialNumN = 0;
			while (serialNumS != "[borders]") {
				inputFileStream >> serialNumS;
				if (serialNumS == "[borders]") {
					break;
				}
				country* tempCountry =  new country();
				serialNumN = std::stoi(serialNumS);
				tempCountry->setSerialNum(serialNumN);
				inputFileStream >> temp;
				tempCountry->setCountryName(temp);
				inputFileStream >> continentBelong;//The continent number 1 here is actually the continent[0].
				tempCountry->setContinent(continentBelong);
				resultMap.setCountries(k, tempCountry);
				numberOfCountries++;
				k++;
				inputFileStream >> ignore;
				inputFileStream >> ignore;
			}
		}
		int count = -1;
		if (serialNumS == "[borders]") {
			while (!inputFileStream.eof()) {
				int border = 0;
				string line = "";
				getline(inputFileStream, line);
				istringstream row(line);
				//cout << line << endl;
				int i = 0;
				while (row >> border) {
					resultMap.countries[count]->setBoarders(i, border);
					i++;
				}
				count++;
			}
		}

	}
	cout << "The map has been successfully loaded, enjoy your game!" << endl;
	inputFileStream.close();
	return(resultMap);
}