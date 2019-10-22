#pragma once
#include <map>
#include <string>

using namespace std;

class Country
{
public:
	string* countryName;
	int* continent;
	int* nbOfArmies;
	int* owner;
	int* countryNumber;
	int* borders;//Boarders of a country. A pointer points to an array of ints
	int* numberOfBorders;//A counter for number of borders, may be used for iteration throw the borders[]
	Country();
	Country(string n);
	Country(string n, int countNb, int cont, int own);
	Country(const Country& obj);
	~Country();
	int getCountryNumber();
	int getOwner();
	int getContinent();
	int getNbOfArmies();
	string getCountryName();
	int getNumOfBorders();
	void setCountryNumber(int n);
	void setOwner(int otherOwner);
	void setContinent(int otherContinent);
	void setCountryName(string otherName);
	void setArmyNumber(int armNb);
	void setBorders(int index, int t);
	void setNumOfBorders(int t);
};


class Continent {
public:
	int* serialNumber;
	string* name;
	int* rewards;
	int* numberOfCountries;
	Continent();
	Continent(Continent& temp);
	void setserialNumber(int t);
	void setName(string t);
	void setRewards(int t);
	void setNumOfCountries(int n);
	int getSerialNum();
	string getName();
	int getReward();
	int getNumOfCountries();
	~Continent();
};




class Map {

public:
	Country* arrOfCountries[70];//Maploader will return you a Map which the arrOfCountries are all country objects, you may use them for your functions
	Continent* arrOfContinents[15];//arrOfContinents are all continents object 
	int* numberOfContinenrs;
	int* numberOfCountries;
	int** mapOfCountries;
	std::map <std::string, int>* continentRequirements;
	Country* listOfCountries;
	Map();
	Map(int nbOfCountries);
	Map(string CountryNames[], int** adjacencyMatrix);
	Map(int** adjacencyMatrix, Country* Countries, int nbOfCountries);
	~Map();
	void setContinent(int index, Continent* tempContinent);//setter for arrOfContinent
	void setCountry(int index, Country* tempCountry);//setter for arrOfCountry
	void setborder(int index, int indexBorders, int num);
	bool validateMap(int continentStart, int continentEnd);
	void printMap();
	int** getMapOfCountries();
	bool addEdge(int start, int destination);
	
};

void mapTestFunction();
