#pragma once

#include <string>
#include <vector>
using namespace std;

//CARD CLASS
class Card {

public:
	Card(int t); //CARD CLASS ACCEPTING TYPE of card as int AS PARAMETER (0-INFANTRY, 1-ARTILLERY, 2-CAVALRY)
	~Card();
	string getType() { return *type; } //ACCESSOR FOR CARD type
	void setType(string str) { *type = str; } //MUTATOR FOR CARD type
	Card getCard() { return *this; } //accessor for card object



private:
	string* type; //TYPE INSTANCE VARIABLE 
};

//DECK CLASS
class Deck {

public:
	Deck(int n); //DECK CONSTRUCTOR ACCEPTING PARAMETER NUMBER OF CARDS 
	~Deck();
	Card draw(); //DRAW CARD METHOD
	std::vector<Card*> getDeck() { return deck; }  //ACCESSOR FOR DECK
	void showDeck(); //PRINT DECK METHOD
	int sizeOfDeck(); // size of deck (number of cards in deck) 
	int countArtillery(); //count artillery cards in deck
	int countCavalry(); //count cavalry cards in deck
	int countInfantry(); //count infantry cards in deck



private:
	//changes made here
	std::vector<Card* > deck; //DECK INSTANCE VARIABLE
	void initializeDeck(int n); //INITIALIZE DECK 
	void shuffleDeck(); //SHUFFLE DECK

};



//HAND CLASS
class Hand {
public:
	Hand(); //HAND DEFAULT CONSTRUCTOR
	~Hand();
	int exchange(); //EXCHANGE METHOD
	std::vector <Card*> getHand() { return hand; } //ACCESSOR FOR HAND
	void setHand(Hand temp); //Mutator for Hand object
	void addToHand(Card card); //ADD CARDS TO HAND METHOD
	void setArmies() { *armies += 5; } //SET NUMBER OF ARMIES (MUTATOR) increment by 5
	int getArmies() { return *armies; } //RETURN NUMBER OF ARMIES (ACCESSOR)
	void showHand(); //print all hand cards to the screen
	int getNumberOfCards();
	int countCavalry();
	int countInfantry();
	int countArtillery();

private:
	std::vector <Card*> hand; //HAND INSTANCE VARIABLE 
	int* armies; //ARMIES POINTER

};
