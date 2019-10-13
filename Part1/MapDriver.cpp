#include <string>
#include <iostream>
#include "Map.h"
using namespace std;



int main()
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

	if (testValid.validateMap(0, 3)) {
		cout << "\nValid map is Valid!\n";
	}
	else {
		cout << "\nValid map is Invalid!\n";
	}

	if (testInvalid.validateMap(0, 5)) {
		cout << "\nInvalid map is Valid!\n";
	}
	else {
		cout << "\nInvalid map is Invalid!\n";
	}


	Country testCountry("Test");
	Country testCountry2("Test",2,3,4);
	//cout << testCountry.getName();
	//cout << testCountry.getContinent();
	//cout << testCountry2.getCountryNumber();

}