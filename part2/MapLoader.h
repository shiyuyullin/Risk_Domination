#pragma once
#include<string>
#include<iostream>
using namespace std;

//The country,continent,map classes are just for the purpose of storing
//the data that has been read from the .map file and may not be a correct implementation of the actual map class. 
class country {
public:
	int* serialNum;
	string* countryName;
	int* continentBelong;
	int* boarders[10];
	country();
	void setSerialNum(int s);
	void setCountryName(string s);
	void setContinent(int s);
	void setBoarders(int index, int t);
	int getSerialNumber();
	string getCountryName();
	int getContinent();
	void displayBorders();
};

class continent {
public:
	int* serialNumber;
	string* name;
	int* rewards;
	continent();
	void setserialNumber(int t);
	void setName(string t);
	void setRewards(int t);
	int getSerialNum();
	string getName();
	int getReward();
};



class map {
public:
	country* countries[60];//array of pointers that point to country objects
	continent* continents[10];//array of pointers that point to continent objects
	map();
	void setCountries(int index, country* c);
	void setContinents(int index, continent* c);
};


class Maploader {
public:
	static map loadingMap(string fileName);//including validate the format of the file in the same time
};