#include <iostream>
#include "MapLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include "MapLoader.h"
#include "Map.h"
using namespace std;

//Implementation of loading function
//Target of the Adapter pattern.
Map* Maploader::loadingMap(string fileName)
{
	ifstream inputFileStream;
	inputFileStream.open(fileName);
	if (!inputFileStream.fail())
	{
		Map* resultMap = new Map(); //The map that will be returned once the function resolves
		string temp = "";
		int numberOfCountries = 0;  //keeping number of countries
		int numberOfContinents = 0; //keeping number of continents
		Map* empty = new Map();		//an empty map to return if the file is invalid
		bool state = false;			//Using for validating format of a map file
		while (!inputFileStream.eof())
		{
			int j = 0;
			inputFileStream >> temp;
			if (temp == "[continents]")
			{
				int rewards = 0;
				int i = 0;
				while (temp != "[countries]")
				{
					Continent* tempContinent = new Continent();
					inputFileStream >> temp; //reading the continent's name
					if (temp == "[countries]")
					{		   //once all the contents belong to the continent part are read, the loop will proceed one more time
						break; //then temp's value is [countries], and we break the loop.
					}
					tempContinent->setName(temp);
					inputFileStream >> rewards; //reading the rewards that are integers
					tempContinent->setRewards(rewards);
					tempContinent->setserialNumber(i + 1);
					inputFileStream >> temp;				//reading the color, will be ignored
					resultMap->setContinent(tempContinent); //Using setters for map
					numberOfContinents++;
					i++;
				}
			}

			string serialNumS = "";
			if (temp == "[countries]")
			{
				int continentBelong = 0;
				int ignore = 0;
				int k = 0;			//A counter, which will be used for store each country object into its corresponding index in the country array of map class.
				int serialNumN = 0; //Temporarily store the serial number of a country
				while (serialNumS != "[borders]")
				{
					inputFileStream >> serialNumS;
					if (serialNumS == "[borders]")
					{
						break;
					}
					Country* tempCountry = new Country();
					serialNumN = std::stoi(serialNumS);
					tempCountry->setCountryNumber(serialNumN);
					inputFileStream >> temp;
					tempCountry->setCountryName(temp);
					inputFileStream >> continentBelong; //The continent number 1 here is actually the continent[0].
					tempCountry->setContinent(continentBelong);
					resultMap->setCountry(tempCountry);
					numberOfCountries++;
					k++;					   //The kth country has been created and stored, increment k for the next iteration
					inputFileStream >> ignore; //The coordinate of a country is ignored
					inputFileStream >> ignore; //coordinate ex. 300 400
				}
				resultMap->setNumberOfCountries(numberOfCountries);
			}
			int count = -1;
			if (serialNumS == "[borders]")
			{
				while (!inputFileStream.eof())
				{
					int border = 0;
					string line = "";
					getline(inputFileStream, line);
					istringstream row(line);
					int i = 0;
					while (row >> border)
					{
						resultMap->setborder(count, i, border);
						resultMap->addEdge(count, border - 1);

						i++; //Changing index for array of borders in country object
					}
					count++; //Changing index for array of countries
				}
				state = true; //All needed information have been read from a map file, the file is valid and a map is successfully created.
			}
		}
		if (!state)
		{ //If a map file is invalid then all of the previous conditions will not be satisified, and value of state stay false which means the map file is invalid.
			std::cout << "The format of the file " << fileName << " is invalid, loading unsuccessful." << std::endl;
			std::cout << "an empty map is returned" << std::endl;
			cout << endl;
			return empty;
		}
		resultMap->setNumberOfContinents(numberOfContinents);
		std::cout << "The map " << fileName << " has been successfully loaded, enjoy your game!" << std::endl;
		cout << endl;
		inputFileStream.close();
		return (resultMap);
	}
	else
	{
		cout << "Invalid file name, the program will now exit" << endl;
		exit(0);
	}
}

//Class that  reads from Conquest files to create a map.
//This class will be the Adaptee of the Adapter

Map* DominationMaploader::loadingMap(string fileName)
{

	ifstream inputFileStream;
	inputFileStream.open(fileName);

	if (!inputFileStream.fail())
	{

		Map* resultMap = new Map(); //The map that will be returned once the function resolves
		string temp = "";
		vector<string> tokens;
		int numberOfCountries = 0; //keeping number of countries
		int SerialNumber = 0;	  //continent Serial number
		int numberOfContinents = 0;
		int continentBelong = 0; //Continent Index
		Map* empty = new Map();  //an empty map to return if the file is invalid
		bool state = false;		 //Using for validating format of a map file
		vector<vector<string>> borders;
		vector<string> continentNames;
		vector<string> continentAttach;
		string line;
		int rewards = 0;
		int i = 0;
		int continentNumber = 0;

		while (getline(inputFileStream, line))
		{
			//cout << line << endl;

			//PARSE CONTINENT INFORMATION
			if (line == "[Continents]")
			{
				while (getline(inputFileStream, line))
				{
					rewards = 0;
					i = 0;
					if (line == "")
					{
						break;
					}
					Continent* tempContinent = new Continent();
					stringstream check1(line);
					string intermediate;
					while (getline(check1, intermediate, '='))
					{
						tokens.push_back(intermediate);
					}

					// cout << tokens[0] << " " << tokens[1] << endl;
					tempContinent->setName(tokens[0]); //sets Continent Name
					continentNames.push_back(tokens[0]);
					rewards = stoi(tokens[1]);

					tempContinent->setRewards(rewards);
					tempContinent->setserialNumber(numberOfContinents++);
					resultMap->setContinent(tempContinent); //Using setters for map
					tokens.clear();
				}
			} //END OF CONTINENT PARSING CODE

			if (line == "[Territories]")
			{
				for(int i = 0; i < continentNames.size(); i++){
					cout << continentNames[i] << endl;
				}
				while (getline(inputFileStream, line))
				{
					tokens.clear();

					if (line == "")
					{ //if there is an empty line it means that we changed continent
					}
					else
					{
						borders.push_back(vector<string>());
						stringstream check1(line);
						string intermediate;
						while (getline(check1, intermediate, ','))
						{
							tokens.push_back(intermediate);
						}

						// cout << "borders :: ";
						for (int i = 4; i < tokens.size(); i++)
						{
							borders[SerialNumber].push_back(tokens[i]);
							// cout << tokens[i] << ", ";
						}
						// cout << endl;

						Country* tempCountry = new Country();
						tempCountry->setCountryName(tokens[0]);
						
						// cout << tempCountry->getCountryName() << " ";
						tempCountry->setContinent(0);
						continentAttach.push_back(tokens[3]);
						// cout << continentBelong << " ";
						tempCountry->setCountryNumber(1 + SerialNumber++);
						// cout << tempCountry->getCountryNumber() << endl;
						resultMap->setCountry(tempCountry);
					}
				}
			}
		}
			resultMap->setNumberOfCountries(SerialNumber);
			resultMap->setNumberOfContinents(numberOfContinents);
			int continentIndex;
			for(int i = 0; i < continentAttach.size(); i++){
				string countriesContinent = continentAttach[i];

				for(int j = 0; j < continentNames.size(); j++){
					if(countriesContinent == continentNames[j]){
						continentIndex = j;
					}
				}
				resultMap->getCountry(i)->setContinentNumber(continentIndex+1);
			}


		vector<vector<int>> edges;
		for (int x = 0; x < borders.size(); x++)
		{
			edges.push_back(vector<int>());
			for (int y = 0; y < borders[x].size(); y++)
			{

				// cout << borders[x][y];
				int destination = resultMap->findIndex(borders[x][y]);
				edges[x].push_back(y);
				// cout << destination << endl;
				resultMap->setborder(x, y, destination);
				resultMap->addEdge(x, destination);
			}
		}

		for(int i = 0; i < continentNames.size(); i++){
			
			bool contains = false;
			for(int j = 0; j < continentAttach.size(); j++){
					if(continentNames[i] == continentAttach[j]){
						contains = true;
					}
			}
			if(contains == false){
				cout << "The format of the file " << fileName << " is invalid, loading unsuccessful." << endl;
				cout << "program is terminating" << endl;
				exit(0);
			}
		}
		//Sorts AND REMOVES DUPLICATES OF THE Attacjed Continent Names
		sort(continentAttach.begin(), continentAttach.end());
 		continentAttach.erase(std::unique(continentAttach.begin(), continentAttach.end()), continentAttach.end());

		if(continentAttach.size() != continentNames.size()){
			std::cout << "The format of the file " << fileName << " is invalid, loading unsuccessful." << endl;
				cout << "program is terminating" << endl;
			exit(0);
		}
		std::cout << "The map " << fileName << " has been successfully loaded, enjoy your game!" << std::endl;
		if(validateMap(edges)){
			return (resultMap);
		}else{
			cout << "The format of the file " << fileName << " is invalid, loading unsuccessful." << endl;
				cout << "program is terminating" << endl;
				exit(0);
		}
		
	}
	else
	{
		cout << "The format of the file " << fileName << " is invalid, loading unsuccessful." << endl;
		cout << "program is terminating" << endl;
		exit(0);
	}
}


//https://www.geeksforgeeks.org/implementation-of-bfs-using-adjacency-matrix/
bool DominationMaploader::validateMap(vector<vector <int>>& edges) {     

	int numberOfCountries = edges.size();
	bool *vis = new bool[numberOfCountries];
   	//for all vertex u as start point, check whether all nodes are visible or not
   	for(int u; u < numberOfCountries; u++) {
   	   for(int i = 0; i<numberOfCountries; i++)
   	      vis[i] = false; //initialize as no node is visited
   	      traverse(u, vis, numberOfCountries, edges);
   	   for(int i = 0; i<numberOfCountries; i++) {
   	      if(!vis[i]) //if there is a node, not visited by traversal, graph is not connected
   	         return false;
   	   }
   	}
   	return true;
}

void DominationMaploader::traverse(int u, bool visited[], int numberOfCountries, vector<vector <int>>& edges) {
   visited[u] = true; //mark v as visited
   for(int v = 0; v<numberOfCountries; v++) {
      if(edges[u][v]) {
         if(!visited[v])
            traverse(v, visited, numberOfCountries, edges);
      }
   }
}



//Subclass of the Target, includes an Adaptee as a data member
//overrides the method that is used to read Domination files

Map* MaploaderAdapter::loadingMap(string fileName)
{
	return mapLoaderAdaptee->loadingMap(fileName);
}
