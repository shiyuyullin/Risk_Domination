#pragma once
#include<string>
#include<iostream>
using namespace std;


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
	int getBoarders(int index);
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
	country* countries[60];
	continent* continents[10];
	map();
	void setCountries(int index, country* c);
	void setContinents(int index, continent* c);

};


class Maploader {
public:
	static map loadingMap(string fileName);
	//bool validator(string fileName);
};