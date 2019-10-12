// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <array>
#include <map>
#include <iostream>
#include <Map.h>

using namespace std;


//
class Country
{

private:
	string* name;
	int* continent;
	int* nbOfArmies;
	int* owner;
	int* countryNumber;

public:
	Country() {}

	Country(string n)
	{
		string* name = &n;
	}

	//Copy Constructor
	Country(const Country& obj)
	{
		name = new string;
		*name = *obj.name;
		continent = new int;
		*continent = *obj.continent;
		nbOfArmies = new int;
		*nbOfArmies = *obj.nbOfArmies;
		owner = new int;
		*owner = *obj.owner;
		countryNumber = new int;
		*countryNumber = *obj.countryNumber;
	}

	Country(string n, int countNb, int cont, int own)
	{
		*name = n;
		*countryNumber = countNb;
		*continent = cont;
		*nbOfArmies = 0;
		*owner = own;
	}

	~Country() {};

	int getCountryNumber()
	{
		return *countryNumber;
	}

	int getContinent()
	{
		return *continent;
	}

	int getNbOfArmies()
	{
		return *nbOfArmies;
	}

	int getOwner()
	{
		return *owner;
	}

	string getName()
	{
		return *name;
	}

	void setArmyNumber(int armNb)
	{
		*nbOfArmies = armNb;
	}

	void setCountyName(string otherName)
	{
		*name = otherName;
	}

	void setOwner(int otherOwner)
	{
		*owner = otherOwner;
	}

	void setContinent(int otherContinent)
	{
		*continent = otherContinent;
	}
};


//MAP CLASS ENCOMPASSES THE TOTALITY OF THE GAME BOARD INCLUDING
//ALL THE COUNTRIES AND THE EDGES BETWEEN THEM ARE STORED IN A 
//ADJACENCY MATRIX.
class Map
{

private:
	int* numberOfCountries;
	int** mapOfCountries;
	map<string, int>* continentRequirements;
	Country* listOfCountries;

public:

	Map() {}

	Map(int nbOfCountries)
	{
		numberOfCountries = new int;
		*numberOfCountries = nbOfCountries;
		// int** arr = new int*[nbOfCountries];
		mapOfCountries = new int* [nbOfCountries];
		for (int i = 0; i < nbOfCountries; i++)
			mapOfCountries[i] = new int[nbOfCountries];

		for (int i = 0; i < *numberOfCountries; i++)
		{
			for (int j = 0; j < *numberOfCountries; j++)
			{
				mapOfCountries[i][j] = 0;
			}
		}
	}

	Map(int** adjacencyMatrix, Country* Countries, int nbOfCountries)
	{
		mapOfCountries = adjacencyMatrix;
		numberOfCountries = new int;
		*numberOfCountries = nbOfCountries;
		mapOfCountries = new int* [nbOfCountries];
		for (int i = 0; i < nbOfCountries; i++)
			mapOfCountries[i] = new int[nbOfCountries];

		for (int i = 0; i < nbOfCountries; i++)
		{
			for (int j = 0; j < nbOfCountries; j++)
			{
				mapOfCountries[i][j] = adjacencyMatrix[i][j];
			}
		}

		listOfCountries = Countries;
	}

	~Map() {};


	//VALIDATE MAP USING THE FACT THAT (ADJ + I)^N 
	//WILL GIVE YOU THE NUMBER OF PATHS BETWEEN TO VERTICES
	//IF N = THE SIZE OF ADJ, THEN IF THERE ISN'T A ROW OR COLUMN
	//THAT IS COMPLETY FULL THEN THE GRAPH IS INVALID.
	bool validateMap(int continentStart, int continentEnd)
	{
		int size = continentEnd - continentStart + 1;
		cout << size;
		int** result = new int* [size];
		for (int i = 0; i < size; i++)
			result[i] = new int[size];

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				result[i][j] = 0;
			}
		}

		//ADD IDENTITY MATRIX TO THE ADJACENCY MATRIX
		for (int x = 0; x < *numberOfCountries; x++)
		{
			mapOfCountries[x][x] = 1;
		}

		for (int t = 0; t < size; t++)
		{
			for (int i = continentStart; i <= continentEnd; i++)
			{
				for (int j = continentStart; j <= continentEnd; j++)
				{
					for (int k = continentStart; k <= continentEnd; k++)
					{
						result[i][j] += mapOfCountries[i][k] * mapOfCountries[k][j];
					}
				}
			}
		}


		//JUST FOR TESTING
		for (int i = continentStart; i <= continentEnd; i++)
		{
			cout << "\n";
			for (int j = continentStart; j <= continentEnd; j++)
			{
				cout << result[i][j] << " ";
			}
		}

		bool connected;
		int sum;
		for (int j = continentStart; j <= continentEnd; j++)
		{
			connected = true;
			for (int k = continentStart; k <= continentEnd; k++)
			{
				if (result[j][k] == 0)
				{
					connected = false;
				}
			}
			if (connected) {
				return true;
			}
		}

		for (int i = 0; i < size; i++)
			delete[] result[i];
		delete[] result;

		return false;
	}

	void printMap()
	{
		cout << "\n--------------------------------\n";

		for (int i = 0; i < *numberOfCountries; i++)
		{
			cout << "\n\n";
			for (int j = 0; j < *numberOfCountries; j++)
			{
				cout << mapOfCountries[i][j] << "  ";
			}
		}

		cout << "\n--------------------------------\n";
	}

	int** getMapOfCountries()
	{
		return mapOfCountries;
	}

	bool addEdge(int start, int destination) {

		if (start < 0 || start > * numberOfCountries ||
			destination < 0 || destination > * numberOfCountries) {
			return false;
		}

		mapOfCountries[start][destination] = 1;
		mapOfCountries[destination][start] = 1;
		return true;
	}
};


void mapTestFunction()
{

	int** mapOfCountriesValid;
	mapOfCountriesValid = new int* [6];
	int** mapOfCountriesInvalid;
	mapOfCountriesInvalid = new int* [6];

	for (int i = 0; i < 6; i++) {
		mapOfCountriesValid[i] = new int[6];
		mapOfCountriesInvalid[i] = new int[6];
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapOfCountriesValid[i][j] = 0;
			mapOfCountriesInvalid[i][j] = 0;
		}
	}

	mapOfCountriesValid[0][1] = 1;
	mapOfCountriesValid[1][0] = 1;
	mapOfCountriesValid[0][2] = 1;
	mapOfCountriesValid[2][0] = 1;
	mapOfCountriesValid[2][3] = 1;
	mapOfCountriesValid[3][2] = 1;
	mapOfCountriesValid[1][3] = 1;
	mapOfCountriesValid[3][1] = 1;
	mapOfCountriesValid[2][4] = 1;
	mapOfCountriesValid[4][2] = 1;
	mapOfCountriesValid[4][5] = 1;
	mapOfCountriesValid[5][4] = 1;

	mapOfCountriesInvalid[0][1] = 1;
	mapOfCountriesInvalid[1][0] = 1;
	mapOfCountriesInvalid[2][3] = 1;
	mapOfCountriesInvalid[3][2] = 1;
	mapOfCountriesInvalid[4][5] = 1;
	mapOfCountriesInvalid[5][4] = 1;


	Country listOFCountries[] = {
		Country("England"),
		Country("Scotland"),
		Country("England"),
		Country("N_Ireland"),
		Country("Rep_Ireland"),
		Country("Wales"),
		Country("Belgum"),
		Country("Netherlands"),
	};




	//Map test(listOFCountries, mapOfCountries);
	//Continent test
	Map testValid(mapOfCountriesValid, listOFCountries, 6);
	Map testInvalid(mapOfCountriesInvalid, listOFCountries, 6);
	//test.printMap();

	if (testValid.validateMap(0,3)) {
		cout << "\nValid map is Valid!\n";
	}
	else {
		cout << "\nValid map is Invalid!\n";
	}

	if (testInvalid.validateMap(0,5)) {
		cout << "\nInvalid map is Valid!\n";
	}
	else {
		cout << "\nInvalid map is Invalid!\n";
	}


}


