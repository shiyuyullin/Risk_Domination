#pragma once
#include <map>
#include <string>

using namespace std;

class Country
{
private:

	string* countryName;
	int* continent;
	int* nbOfArmies;
	int* owner;
	int* countryNumber;
	int* borders;//Boarders of a country. A pointer points to an array of ints
	int* numberOfBorders;//A counter for number of borders, may be used for iteration throw the borders[]

public:

	Country();
	Country(string n);
	Country(string n, int countNb, int cont, int own);
	Country(const Country& obj);
	~Country();
	int getCountryNumber();
	int getOwner();
	int getContinent();
	int getNbOfArmies();
	string getName();
	void setOwner(int otherOwner);
	void setContinent(int otherContinent);
	void setCountryName(string otherName);
	void setArmyNumber(int armNb);
};


class Continent {

	int* serialNumber;
	string* name;
	int* rewards;
	int* countryList;
	int* numberOfCountries;

public:
	Continent();
	void setserialNumber(int t);
	void setName(string t);
	void setRewards(int t);
	int getSerialNum();
	string getName();
	int getReward();
};




class Map {

private:
	Country* arrOfCountries;//Maploader will return you a Map which the arrOfCountries are all country objects, you may use them for your functions
	Continent* arrOfContinents;//arrOfContinents are all continents object 
	int* numberOfContinenrs;
	int* numberOfCountries;
	int** mapOfCountries;
	std::map <std::string, int>* continentRequirements;
	Country* listOfCountries;


public:
	Map();
	Map(int nbOfCountries);
	Map(string CountryNames[], int** adjacencyMatrix);
	Map(int** adjacencyMatrix, Country* Countries, int nbOfCountries);
	~Map();
	bool validateMap(int continentStart, int continentEnd);
	void printMap();
	int** getMapOfCountries();
	bool addEdge(int start, int destination);
};

void mapTestFunction();
