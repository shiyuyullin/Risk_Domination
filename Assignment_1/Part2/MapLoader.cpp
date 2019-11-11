#include <iostream>
#include "MapLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include "MapLoader.h"
#include "Map.h"
using namespace std;

//Implementation of loading function
Map* Maploader::loadingMap(string fileName) {
	ifstream inputFileStream;
	inputFileStream.open(fileName);
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
				resultMap->setNumberOfCountries(numberOfCountries);
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
						resultMap->addEdge(count, border - 1);

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


Map* DominationMaploader::loadingMap(string fileName) {

	ifstream inputFileStream;
	inputFileStream.open(fileName);
	

	if (!inputFileStream.fail()) {
		Map* resultMap = new Map();//The map that will be returned once the function resolves
		string temp = "";
		vector <string> tokens;
		int numberOfCountries = 0;//keeping number of countries
		int numberOfContinents = 0;//keeping number of continents
		int SerialNumber = 0; //continent Serial number
		Map* empty = new Map();//an empty map to return if the file is invalid
		bool state = false;//Using for validating format of a map file
		vector<vector<string> > borders;
		string line;

		while (getline(inputFileStream, line)) {
			
			if (line == "[Continents]") {
				while (getline(inputFileStream, line)) {
					
					if (line == "[Territories]")
						break;

					Continent* tempContinent = new Continent();
					stringstream check1(line);
					string intermediate;
					while (getline(check1, intermediate, '='))
					{
						tokens.push_back(intermediate);
					}

					tempContinent->setName(tokens[0]); //sets Continent Name
					int rewards = stoi(tokens[1]);
					tempContinent->setRewards(rewards);
					tempContinent->setserialNumber(SerialNumber + 1);
					inputFileStream >> temp;//reading the color, will be ignored
					resultMap->setContinent(tempContinent);//Using setters for map 
					numberOfContinents++;
					SerialNumber++;
					tokens.clear();

				}
			}
			int serialNum = 0;
			int continentBelong = 0;
			tokens.clear();
			while (getline(inputFileStream, line)) {
				
				if (line == "") {//if there is an empty line it means that we changed continent
					continentBelong++;
				}
				else {

					borders.push_back( vector<string>());
					stringstream check1(line);
					string intermediate;
					while (getline(check1, intermediate, ','))
					{
						tokens.push_back(intermediate);
					}
					Country* tempCountry = new Country();
					borders[continentBelong].push_back(tokens[0]);
					tempCountry->setCountryName(tokens[0]);
					tempCountry->setContinent(continentBelong);
					tempCountry->setCountryNumber(serialNum);

					resultMap->setCountry(tempCountry);
					serialNum++;
					tokens.clear();
				}
			}
			resultMap->setNumberOfCountries(serialNum + 1);
			inputFileStream.close();
			break;
		}

		for (int x = 0; x < borders.size() ; x++){
			for (int y = 0; y < borders[x].size(); y++){
			
				int destination = resultMap->findIndex(borders[x][y]);
				resultMap->setborder(x, y, destination);
				resultMap->addEdge(x, destination);
			}
		}

	}
	else {
		cout << "Invalid file name, please program exit" << endl;
		exit(0);
	}
}

Map* MaploaderAdapter::loadingMap(string fileName) {

	ifstream inputFileStream;
	inputFileStream.open(fileName);
	bool riskFile = true;
	string line;

	if (!inputFileStream.fail()) {

		while (getline(inputFileStream, line)) {

			size_t found = line.find("[Territories]");
			if (found != string::npos) {
				riskFile = false;
			}

		}
		inputFileStream.close();
		if (riskFile) {
			return Maploader().loadingMap(fileName);
		}
		else {
			return DominationMaploader().loadingMap(fileName);
		}
	}
	else {
		cout << "Invalid file name, please program exit" << endl;
		exit(0);
	}
}
