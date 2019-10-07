// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <array>
#include <map>
#include <iostream>

using namespace std;

class Country
{

private:
	string *name;
	int *continent;
	int *nbOfArmies;
	int *owner;
	int *countryNumber;

public:
	Country() {}

	Country(string n)
	{
		string *name = &n;
	}

	Country(string n, int countNb, int cont, int own)
	{
		*name = n;
		*countryNumber = countNb;
		*continent = cont;
		*nbOfArmies = 0;
		*owner = own;
	}

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
};

class Map
{

private:
	int *numberOfCountries;
	int **mapOfCountries;
	map<string, int> *continentRequirements;
	Country *listOfCountries;

public:
	Map() {}

	Map(int nbOfCountries)
	{
		numberOfCountries = new int;
		*numberOfCountries = nbOfCountries;
		// int** arr = new int*[nbOfCountries];
		mapOfCountries = new int *[nbOfCountries];
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

	Map(string CountryNames[], int **adjacencyMatrix)
	{
		*listOfCountries = *CountryNames;
		mapOfCountries = adjacencyMatrix;
	}

	~Map(){};

	bool validateMap(int continentNumber)
	{

		const int size = sizeof(**mapOfCountries) / sizeof(int);
		int result[size][size];

		for (int t = 0; t < *numberOfCountries; t++)
		{
			for (int i = 0; i < *numberOfCountries; i++)
			{
				for (int j = 0; j < *numberOfCountries; j++)
				{
					result[i][j] = 0;
					for (int k = 0; k < *numberOfCountries; k++)
					{
						result[i][j] += mapOfCountries[i][k] * mapOfCountries[k][j];
					}
				}
			}
		}

		bool connected = true;
		for (int j = 0; j < *numberOfCountries; j++)
		{
			for (int k = 0; k < *numberOfCountries; k++)
			{
				if (result[j][k] == 0)
				{
					connected = false;
				}
			}
		}

		return connected;
	}

	void printMap()
	{
		cout << "heelo\n";
		for (int i = 0; i < *numberOfCountries; i++)
		{
			cout << "\n";
			for (int j = 0; j < *numberOfCountries; j++)
			{
				cout << mapOfCountries[i][j] << "\n";
			}
		}
	}

	int **getMapOfCountries()
	{
		return mapOfCountries;
	}
};

class Route
{
};

int main()
{
	Map x(10);
	x.printMap();
}
