#pragma once
#include <map>
#include <string>

using namespace std;

class Country
{
private:

	string* name;
	int* continent;
	int* nbOfArmies;
	int* owner;
	int* countryNumber;

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

class Map {

private:
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