#pragma once
#include <map>
#include <string>
#include "D:\Visual Studio\WorkSpace\Player\Player.h"

using namespace std;

class Country
{
	string *countryName;
	int *continent;
	int *nbOfArmies;
	Player *owner;
	int *countryNumber;
	int *borders;		  //Boarders of a country. A pointer points to an array of ints
	int *numberOfBorders; //A counter for number of borders, may be used for iteration throw the borders[]
public:
	Country();
	Country(string n);
	Country(string n, int countNb, int cont, int own);
	Country(const Country &obj);
	~Country();
	int getCountryNumber();
	int getContinent();
	int getNbOfArmies();
	string getCountryName();
	int getNumOfBorders();
	int *getBorders();
	Player *getOwner();
	void setCountryNumber(int n);
	void setContinent(int otherContinent);
	void setCountryName(string otherName);
	void setArmyNumber(int armNb);
	void setBorders(int index, int t);
	void setNumOfBorders(int t);
	void setOwner(Player *p);
};

class Continent
{
	int *serialNumber;
	string *name;
	int *rewards;
	int *numOfCountries;

public:
	Continent();
	Continent(Continent &temp);
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

class Map
{

	Country *arrOfCountries[70];	//Maploader will return you a Map which the arrOfCountries are all country objects, you may use them for your functions
	Continent *arrOfContinents[15]; //arrOfContinents are all continents object
	int *numberOfContinents;
	int *numberOfCountries;
	int **mapOfCountries;
	Country *listOfCountries;
	createAdjacencyMatrix();

public:
	Map();
	Map(int nbOfCountries);
	Map(string CountryNames[], int **adjacencyMatrix);
	Map(int **adjacencyMatrix, Country *Countries, int nbOfCountries);
	~Map();
	void setContinent(int index, Continent *tempContinent); //setter for arrOfContinent
	void setCountry(int index, Country *tempCountry);		//setter for arrOfCountry
	void setborder(int index, int indexBorders, int num);   //setter for country's borders
	void setNumberOfCountries(int numberOfCountries);		//setter to set number of countries
	void setNumberOfContinents(int numberOfContinents);		//setter to set number of continents
	bool validateMap(int continentStart, int continentEnd);
	void printMap();
	int **getMapOfCountries();
	int getNumOfCountries();
	int getNumOfContinents();
	Country *getCountry(int index);
	Continent *getContinent(int index);
	void addEdge(int start, int destination);
};

void mapTestFunction();
