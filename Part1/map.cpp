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
		//const int size = sizeof(**mapOfCountries) / sizeof(*mapOfCountries);
		//cout << "\n" << size;
		//cout << 12;
	}

	~Map() {};

	bool validateMap(int continentNumber)
	{

		int size = *numberOfCountries;
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

		for (int t = 0; t < *numberOfCountries; t++)
		{
			for (int i = 0; i < *numberOfCountries; i++)
			{
				for (int j = 0; j < *numberOfCountries; j++)
				{
					for (int k = 0; k < *numberOfCountries; k++)
					{
						result[i][j] += mapOfCountries[i][k] * mapOfCountries[k][j];
					}
				}
			}
		}


		//JUST FOR TESTING
		for (int i = 0; i < 6; i++)
		{
			cout << "\n";
			for (int j = 0; j < 6; j++)
			{
				cout << result[i][j] << " ";
			}
		}

		bool connected;
		int sum;
		for (int j = 0; j < *numberOfCountries; j++)
		{
			connected = true;
			for (int k = 0; k < *numberOfCountries; k++)
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

	void addEdge(Country start, Country destination) {

	}



};

class Route
{
};


int main()
{

	int** mapOfCountries;
	mapOfCountries = new int* [6];

	for (int i = 0; i < 6; i++)
		mapOfCountries[i] = new int[6];

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapOfCountries[i][j] = 0;
		}
	}

	mapOfCountries[0][1] = 1;
	mapOfCountries[1][0] = 1;

	mapOfCountries[0][2] = 1;
	mapOfCountries[2][0] = 1;

	mapOfCountries[2][3] = 1;
	mapOfCountries[3][2] = 1;

	mapOfCountries[1][3] = 1;
	mapOfCountries[3][1] = 1;


	mapOfCountries[2][4] = 1;
	mapOfCountries[4][2] = 1;

	mapOfCountries[4][5] = 1;
	mapOfCountries[5][4] = 1;

	Country listOFCountries[] = {
		Country("England"),
		Country("Scotland"),
		Country("England"),
		Country("N_Ireland"),
		Country("Rep_Ireland"),
		Country("Wales"),
		Country("Belgum"),
		Country("Netherlands"),
		Country("Denmark"),
		Country("Germany"),
		Country("Poland"),
		Country("Czech_Rep"),
		Country("Slovakia"),
		Country("Hungary"),
		Country("Austria"),
		Country("Switzerland"),
		Country("Italy"),
		Country("Sicily"),
		Country("Sardinia"),
		Country("Corsica"),
		Country("Majorca"),
		Country("France"),
		Country("Spain"),
		Country("Portugal"),
		Country("Luxembourg")
	};

	// 1 England 1 164 126
	// 2 Scotland 1 158 44
	// 3 N_Ireland 1 125 70
	// 4 Rep_Ireland 1 106 90
	// 5 Wales 1 141 109
	// 6 Belgum 1 213 153
	// 7 Netherlands 1 226 128
	// 8 Denmark 2 275 76
	// 9 Germany 2 261 149
	// 10 Poland 2 346 141
	// 11 Czech_Rep 2 308 173
	// 12 Slovakia 2 356 190
	// 13 Hungary 3 347 220
	// 14 Austria 3 306 210
	// 15 Switzerland 3 233 217
	// 16 Italy 3 264 249
	// 17 Sicily 3 294 363
	// 18 Sardinia 3 240 321
	// 19 Corsica 3 242 286
	// 20 Majorca 4 184 319
	// 21 France 4 176 202
	// 22 Spain 4 96 285
	// 23 Portugal 4 38 290
	// 24 Luxembourg 4 227 172



//Map test(listOFCountries, mapOfCountries);
	Map test(mapOfCountries, listOFCountries, 6);
	//test.printMap();

	if (test.validateMap(0)) {
		cout << "\nMap is Valid!\n";
	}
	else {
		cout << "\nMap is Invalid!\n";
	}

}
