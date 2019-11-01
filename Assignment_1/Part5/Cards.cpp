#include "Cards.h";
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <random>
#include <chrono>
#include <stdlib.h>
#include <time.h>

using namespace std;



/*
Class Card Constructors
One parameter int i  - an integer
if i=0 then card is infantry, if i=1 then card is artillery, if i=2 then card is cavalry
*/
Card::Card(int i) {
	type = new string;
	switch (i) {
	case 0: setType("infantry");
		break;
	case 1:setType("artillery");
		break;
	case 2: setType("cavalry");
		break;
	}

}

Card::~Card() {
	delete type;
	type = NULL;
}


/*
Class Deck Constructor
*/
Deck::Deck(int n) {

	initializeDeck(n);
	shuffleDeck();
}

Deck::~Deck() {
	for (int i = 0; i < deck.size(); i++) {
		delete deck.at(i);
		deck.at(i) = NULL;
	}
}
/*
DRAW CARD METHOD FROM DECK CLASS
*/
Card Deck::draw()
{
	if (deck.size() > 0) {
		srand(time(NULL)); //set setrand time to null
		int random = rand() % deck.size(); //generate random index based on deck size

		//changes made here
		Card draw = *deck.at(random); //draw a new card based on random and store card in a card object - draw 

		if (random > 0)
			deck.erase(deck.begin() + (random - 1));
		else
			deck.erase(deck.begin());
		return draw;
	}
}


/*
INITIALIZE DECK METHOD
*/
void Deck::initializeDeck(int n) {

	for (int i = 0; i < n; i++) {
		int t = i % 3;
		deck.push_back(new Card(t));
	}

}


/*
SHOW DECK METHOD (PRINTS CARDS TO SCREEN)
*/
void Deck::showDeck() {
	for (int i = 0; i < getDeck().size(); i++) {
		std::cout << deck[i]->getType() << endl;
	}
}

/*
SHUFFLE DECK METHOD
*/
void Deck::shuffleDeck()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // initialize seed
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed)); //randomize vector
}

/*
Size of deck method (number of cards in deck)
*/
int Deck::sizeOfDeck() {
	return deck.size();
}


/*
COUNT ARTILLERY CARDS METHOD
*/
int Deck::countArtillery() {
	int count = 0;
	for (int i = 0; i < deck.size(); i++) {
		if (deck.at(i)->getType() == "artillery")
			count++;
	}

	return count;
}


/*
COUNT CAVALRY CARDS in deck METHOD
*/
int Deck::countCavalry() {
	int count = 0;
	for (int i = 0; i < deck.size(); i++) {
		if (deck.at(i)->getType() == "cavalry") {
			count++;
		}
	}

	return count;
}


/*
COUNT INFANTRY CARDS in deck METHOD
*/
int Deck::countInfantry() {
	int count = 0;
	for (int i = 0; i < deck.size(); i++) {
		if (deck.at(i)->getType() == "infantry") {
			count++;
		}
	}

	return count;
}

/*
COUNT ARTILLERY CARDS IN HAND METHOD
*/
int Hand::countArtillery() {
	int count = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i)->getType() == "artillery")
			count++;
	}

	return count;
}


/*
COUNT CAVALRY CARDS  IN HAND METHOD
*/
int Hand::countCavalry() {
	int count = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i)->getType() == "cavalry")
			count++;
	}

	return count;
}


/*
COUNT INFANTRY CARDS IN HAND METHOD
*/
int Hand::countInfantry() {
	int count = 0;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i)->getType() == "infantry")
			count++;
	}

	return count;
}


/*
Class Hand Constructors
*/
Hand::Hand() {

	armies = new int;
	*armies = 0;
}

Hand::~Hand() {
	delete armies;
	armies = NULL;

	for (int i = 0; i < hand.size(); i++) {
		delete hand.at(i);
		hand.at(i) = NULL;
	}
}


void Hand::setHand(Hand temp) {
	hand = temp.getHand();
}
/*
REMOVE NULL CARDS METHOD (FOR EXCHANGE METHOD)
*/
static Hand removeNull(vector <Card*>hand) {
	Hand temp;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i)->getType() != "null") {
			temp.addToHand(hand.at(i)->getCard());
		}
	}
	return temp;
}

/*
EXCHANGE CARDS IN HAND FOR ARMIES METHOD
*/
int Hand::exchange() {

	//set count and hand size
	int count = 0;
	int handsize = hand.size();

	//rule 1 - exchange if three infantry cards exist
	if (countInfantry() >= 3) {

		for (int i = 0; (i < handsize); i++) {
			if (hand.at(i)->getType() == "infantry") {
				hand.at(i)->setType("null");
				count++;
				handsize = hand.size();

				if (count == 3)
					break;

			}
		}
		Hand temp = removeNull(hand);

		setHand(temp);


		setArmies();
		std::cout << "Here are " << getArmies() << " armies!" << endl;
		return getArmies();
	}

	//rule 2  - exchange if three artillery cards exist
	if (countArtillery() >= 3) {

		for (int i = 0; i < hand.size(); i++) {
			if (hand.at(i)->getType() == "artillery") {
				hand.at(i)->setType("null");
				count++;
				handsize = hand.size();

				if (count == 3)
					break;
			}
		}

		Hand temp = removeNull(hand);

		setHand(temp);


		setArmies();
		std::cout << "Here are " << getArmies() << " armies!" << endl;
		return getArmies();

	}

	//rule 3 - exchange if 3 cavalry cards exist
	if (countCavalry() >= 3) {

		for (int i = 0; (i < handsize); i++) {
			if (hand.at(i)->getType() == "cavalry") {
				hand.at(i)->setType("null");
				count++;
				handsize = hand.size();

				if (count == 3)
					break;
			}
		}

		Hand temp = removeNull(hand);

		setHand(temp);


		setArmies();
		std::cout << "Here are " << getArmies() << " armies!" << endl;
		return getArmies();
	}

	//rule 4  - exchange if one of each cards exist
	if (countInfantry() >= 1 && countInfantry() >= 1 && countArtillery() >= 1) {

		for (int i = 0; i < hand.size(); i++) {
			if (hand.at(i)->getType() == "infantry") {
				hand.erase(hand.begin() + i);
				break;
			}
		}

		for (int i = 0; i < hand.size(); i++) {
			if (hand.at(i)->getType() == "artillery") {
				hand.erase(hand.begin() + i);
				break;
			}
		}

		for (int i = 0; i < hand.size(); i++) {
			if (hand.at(i)->getType() == "cavalry") {
				hand.erase(hand.begin() + i);
				break;
			}

		}

		setArmies();
		std::cout << "Here are " << getArmies() << " armies!" << endl;
		return getArmies();
	}

	//Default message if rules are not met
	std::cout << "You cannot make any exchanges yet. Insufficient/Invalid Cards.";
	return 0;
}


/*
addtoHand method to add a card drawn fro deck to Hand
*/

void Hand::addToHand(Card card) {

	hand.push_back(new Card(card));
}

/*
Print all cards in hand to the screen
*/
void Hand::showHand() {
	int count = 0;
	for (int i = 0; i < hand.size(); i++) {
		std::cout << hand[i]->getType() << endl;
		count++;
	}
}
