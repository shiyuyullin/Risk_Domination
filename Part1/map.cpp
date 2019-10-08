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

	Map(int** adjacencyMatrix, Country *Countries, int nbOfCountries)
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
		for (int i = 0; i < 12; i++)
		{
			cout << "\n";
			for (int j = 0; j < 12; j++)
			{
				cout << result[i][j] << " ";
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

		for (int i = 0; i < size; i++)
			delete[] result[i];
		delete[] result;
		
		return connected;
	}

	void printMap()
	{
		cout << "\n--------------------------------\n";

		for (int i = 0; i < *numberOfCountries; i++)
		{
			cout << "\n";
			for (int j = 0; j < *numberOfCountries; j++)
			{
				cout << mapOfCountries[i][j] << " ";
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
	mapOfCountries = new int* [12];

	for (int i = 0; i < 12; i++)
		mapOfCountries[i] = new int[12];

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			mapOfCountries[i][j] = 0;
		}
	}

	mapOfCountries[0][0] = 1;
	mapOfCountries[1][1] = 1;
	mapOfCountries[2][2] = 1;
	mapOfCountries[3][3] = 1;
	mapOfCountries[4][4] = 1;
	mapOfCountries[5][5] = 1;
	mapOfCountries[6][6] = 1;
	mapOfCountries[7][7] = 1;
	mapOfCountries[8][8] = 1;
	mapOfCountries[9][9] = 1;
	mapOfCountries[10][10] = 1;
	mapOfCountries[11][11] = 1;

	mapOfCountries[0][1] = 1;
	mapOfCountries[0][2] = 1;
	mapOfCountries[0][4] = 1;
	mapOfCountries[0][5] = 1;


	mapOfCountries[1][0] = 1;
	mapOfCountries[1][2] = 1;

	mapOfCountries[2][0] = 1;
	mapOfCountries[2][1] = 1;
	mapOfCountries[2][3] = 1;


	mapOfCountries[3][2] = 1;
	mapOfCountries[3][4] = 1;

	mapOfCountries[4][0] = 1;
	mapOfCountries[4][3] = 1;

	mapOfCountries[5][6] = 1;
	mapOfCountries[5][7] = 1;

	mapOfCountries[6][5] = 1;
	mapOfCountries[6][7] = 1;
	mapOfCountries[6][11] = 1;

	mapOfCountries[7][5] = 1;
	mapOfCountries[7][6] = 1;
	mapOfCountries[7][8] = 1;
	mapOfCountries[7][10] = 1;
	mapOfCountries[7][11] = 1;

	mapOfCountries[8][7] = 1;
	mapOfCountries[8][9] = 1;

	mapOfCountries[9][8] = 1;

	mapOfCountries[10][7] = 1;
	mapOfCountries[10][11] = 1;

	mapOfCountries[11][6] = 1;
	mapOfCountries[11][7] = 1;
	mapOfCountries[11][10] = 1;


	for (int i = 0; i < 12; i++)
	{
		cout << "\n";
		for (int j = 0; j < 12; j++)
		{
			cout << mapOfCountries[i][j] << " ";
		}
	}


	Country listOFCountries[] = { Country("England"),
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
		Country("Slovakia")
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

		// 1  2 3 5 6
		// 2  1 3 
		// 3  1 2 4 
		// 4  3 5
		// 5  1 4
		// 6  7 8 
		// 7  6 8 12 
		// 8  6 7 9 11 12
		// 9  8 10 
		// 10  9
		// 11  8 12
		// 12  7 8 11 
		
	//Map test(listOFCountries, mapOfCountries);
	Map test(mapOfCountries, listOFCountries, 12);
	test.printMap();
	cout << test.validateMap(0);

	}
