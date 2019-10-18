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
void country::displayBorders() {
	int i = 0;
	while (*boarders[i] != 0) {
		cout << *boarders[i] << " ";
		i++;
	}
	cout << endl;
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

//Implementation of loading function
map Maploader::loadingMap(string fileName) {
	ifstream inputFileStream(fileName + ".txt");
	map resultMap;//The map that will be returned once the function resolves
	string temp = "";
	int numberOfCountries = 0;//keeping number of countries
	int numberOfContinents = 0;//keeping number of continents
	map empty;//an empty map to return if the file is invalid
	bool state = false;//Using for validating format of a map file
	while (!inputFileStream.eof()) {
		int j = 0;
		inputFileStream >> temp;
		if (temp == "[continents]") {
			int rewards = 0;
			int i = 0;
			while (temp != "[countries]") {
				continent* tempContinent = new continent();
				inputFileStream >> temp;//reading the continent's name
				if (temp == "[countries]") {//once all the contents belong to the continent part are read, the loop will proceed one more time
					break;					//then temp's value is [countries], and we break the loop.
				}
				tempContinent->setName(temp);
				inputFileStream >> rewards;//reading the rewards that are integers
				tempContinent->setRewards(rewards);
				tempContinent->setserialNumber(i+1);
				inputFileStream >> temp;//reading the color, will be ignored
				resultMap.setContinents(i, tempContinent);
				numberOfContinents++;
				i++;
			}
		}
		string serialNumS = "";
		if (temp == "[countries]") {
			int continentBelong = 0;
			int ignore = 0;
			int k = 0;//A counter, which will be used for store each country object into its corresponding index in the country array of map class.
			int serialNumN = 0;//Temporarily store the serial number of a country
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
				k++;//The kth country has been created and stored, increment k for the next iteration
				inputFileStream >> ignore;//The coordinate of a country is ignored
				inputFileStream >> ignore;//coordinate ex. 300 400
			}
		}
		int count = -1;
		if (serialNumS == "[borders]") {
			while (!inputFileStream.eof()) {
				int border = 0;
				string line = "";
				getline(inputFileStream, line);
				istringstream row(line);
				int i = 0;
				while (row >> border) {
					resultMap.countries[count]->setBoarders(i, border);
					i++;
				}
				count++;
			}
			state = true;//All needed information have been read from a map file, the file is valid and a map is successfully created.
		}
	}
	if (!state) {//If a map file is invalid then all of the previous conditions will not be satisified, and value of state stay false which means the map file is invalid.
		std::cout << "The format of the file "<< fileName <<" is invalid, loading unsuccessful." << std::endl;
		std::cout << "an empty map is returned" << std::endl;
		cout << endl;
		return empty;
	}
	std::cout << "The map "<< fileName <<" has been successfully loaded, enjoy your game!" << std::endl;
	cout << endl;
	inputFileStream.close();
	return(resultMap);
}