#pragma once

#include <string>
#include <vector>
using namespace std;

//CARD CLASS
class Card {

public:
	Card(int t); //CARD CLASS ACCEPTING TYPE AS PARAMETER (0-INFANTRY, 1-ARTILLERY, 2-CAVALRY)
	string getType() { return *type; } //ACCESSOR FOR CARD
	void setType(string str) { *type = str; } //MUTATOR FOR CARD
	

private:
	string *type; //TYPE INSTANCE VARIABLE ******
};

//DECK CLASS
class Deck{

public:
	Deck(int n); //DECK CONSTRUCTOR ACCEPTING PARAMETER NUMBER OF CARDS 
	Card draw(); //DRAW CARD METHOD
	std::vector<Card> getDeck() { return deck; }  //ACCESSOR FOR DECK
	void showDeck(); //PRINT DECK METHOD
	int sizeOfDeck();
	

private: 
	std::vector<Card> deck; //DECK INSTANCE VARIABLE  *****
	void initializeDeck(int n); //INITIALIZE DECK 
	void shuffleDeck(); //SHUFFLE DECK
	
};


//HAND CLASS
class Hand {
public:
	Hand(); //HAND DEFAULT CONSTRUCTOR
	Hand(vector<Card> cards); // PARAMETERIZED HAND CONSTRUCTOR
	int exchange(); //EXCHANGE METHOD
	std::vector <Card> getHand() { return hand;} //ACCESSOR FOR HAND
	void setHand(Hand temp) {	// MUTATOR FOR HAND
		 hand = temp.getHand();
	}

	void addToHand(Card card); //ADD CARDS TO HAND METHOD
	void setArmies() { *armies += 5; } //SET NUMBER OF ARMIES (MUTATOR)
	int getArmies() { return *armies; } //RETURN NUMBER OF ARMIES (ACCESSOR)
	void showHand();
	
private:
	std::vector <Card> hand; //HAND INSTANCE VARIABLE ****
	int *armies; //ARMIES POINTER
	
};




