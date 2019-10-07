#pragma once
#include <map>
#include <string>

class Country
{
private:

	string *name;
	int *continent;
	int *nbOfArmies;
	int *owner;
	int *countryNumber;

public:

    Country();
    Country(string n);
    Country(string n, int countNb, int cont, int own);
	
	int getCountryNumber();
	int getOwner();
    int getContinent();
    int getNbOfArmies();
    string getName();
    
	void setArmyNumber(int armNb);
};

class Map {

private:
	int* numberOfCountries;
	int** mapOfCountries;
	map <string, int> *continentRequirements;
	Country* listOfCountries;


public:
	Map();
	~Map();
	bool Validate();
	void printMap();
	
	//private memeber fields
};
