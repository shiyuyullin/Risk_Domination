#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"
using namespace std;

//Implementation of loading function
Map* Maploader::loadingMap(string fileName) {
	ifstream inputFileStream;
	inputFileStream.open(fileName + ".txt");
	if (!inputFileStream.fail()) {
		Map* resultMap = new Map();//The map that will be returned once the function resolves
		string temp = "";
		int numberOfCountries = 0;//keeping number of countries
		int numberOfContinents = 0;//keeping number of continents
		Map* empty = new Map();//an empty map to return if the file is invalid
		bool state = false;//Using for validating format of a map file
		while (!inputFileStream.eof()) {
			int j = 0;
			inputFileStream >> temp;
			if (temp == "[continents]") {
				int rewards = 0;
				int i = 0;
				while (temp != "[countries]") {
					Continent* tempContinent = new Continent();
					inputFileStream >> temp;//reading the continent's name
					if (temp == "[countries]") {//once all the contents belong to the continent part are read, the loop will proceed one more time
						break;					//then temp's value is [countries], and we break the loop.
					}
					tempContinent->setName(temp);
					inputFileStream >> rewards;//reading the rewards that are integers
					tempContinent->setRewards(rewards);
					tempContinent->setserialNumber(i + 1);
					inputFileStream >> temp;//reading the color, will be ignored
					resultMap->setContinent(tempContinent);//Using setters for map 
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
					Country* tempCountry = new Country();
					serialNumN = std::stoi(serialNumS);
					tempCountry->setCountryNumber(serialNumN);
					inputFileStream >> temp;
					tempCountry->setCountryName(temp);
					inputFileStream >> continentBelong;//The continent number 1 here is actually the continent[0].
					tempCountry->setContinent(continentBelong);
					resultMap->setCountry(tempCountry);
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
						resultMap->setborder(count, i, border);
						i++;//Changing index for array of borders in country object
					}
					count++;//Changing index for array of countries
				}
				state = true;//All needed information have been read from a map file, the file is valid and a map is successfully created.
			}
		}
		if (!state) {//If a map file is invalid then all of the previous conditions will not be satisified, and value of state stay false which means the map file is invalid.
			std::cout << "The format of the file " << fileName << " is invalid, loading unsuccessful." << std::endl;
			std::cout << "an empty map is returned" << std::endl;
			cout << endl;
			return empty;
		}
		resultMap->setNumberOfCountries(numberOfCountries);
		resultMap->setNumberOfContinents(numberOfContinents);
		std::cout << "The map " << fileName << " has been successfully loaded, enjoy your game!" << std::endl;
		cout << endl;
		inputFileStream.close();
		return(resultMap);
	}
	else {
		cout << "Invalid file name, please program exit" << endl;
		exit(0);
	}
}