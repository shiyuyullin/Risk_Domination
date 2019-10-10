

#include "Cards.h";
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include <random>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <array>

using namespace std;


	
/*
Class Card Constructors
*/
Card::Card(int i) {
	
switch (i) {
case 0: setType("infantry");
		break;
case 1:setType("artillery");
	break;
case 2: setType("cavalry");
	break;
}

}


/*
Class Deck Constructor
*/

Deck::Deck(int n) {

initializeDeck(n);
shuffleDeck();
}

/*
DRAW CARD METHOD FROM DECK CLASS
*/
Card Deck::draw()
{

srand(time(NULL));
int random = rand() % deck.size();

Card draw = deck.at(random);
if(random>0)
deck.erase(deck.begin() + (random - 1));
else
deck.erase(deck.begin());
return draw;
}


/*
INITIALIZE DECK METHOD
*/
void Deck::initializeDeck(int n){
	
for (int i = 0; i < n; i++) {
int t = i % 3;
Card card(t);
deck.push_back(card);
}
	
}


/*
SHOW DECK METHOD (PRINTS CARDS TO SCREEN)
*/
void Deck :: showDeck() {
for (int i = 0; i < getDeck().size(); i++) {
	std::cout << getDeck().at(i).getType() << endl;
}
}

/*
SHUFFLE DECK METHOD
*/
void Deck::shuffleDeck()
{
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

int Deck::sizeOfDeck() {
	return deck.size();
}

/*
COUNT ARTILLERY CARDS METHOD
*/
static int countArtillery(vector <Card> cards) {
int count = 0;
for (int i = 0; i < cards.size(); i++) {
	if (cards.at(i).getType() == "artillery")
		count++;
}

return count;
}


/*
COUNT CAVALRY CARDS METHOD
*/
static int countCavalry(vector <Card> cards) {
int count = 0;
for (int i = 0; i < cards.size(); i++) {
	if (cards.at(i).getType() == "cavalry")
		count++;
}

return count;
}


/*
COUNT INFANTRY CARDS METHOD
*/
static int countInfantry(vector <Card> cards) {
int count = 0;
for (int i = 0; i < cards.size(); i++) {
	if (cards.at(i).getType() == "infantry")
		count++;
}

return count;
}


/*
Class Hand Constructors
*/
Hand::Hand(){
	armies = new int;
	*armies = 0;
}

Hand::Hand(vector<Card>cards) {
this->hand = cards;
armies = new int;
*armies = 0;
}

/*
REMOVE NULL CARDS METHOD (FOR EXCHANGE METHOD)
*/
static Hand removeNull(vector <Card> hand) {
	Hand temp;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i).getType() != "null") {
			temp.addToHand(hand.at(i));
		}
	}
	return temp;
}

/*
EXCHANGE CARDS IN HAND FOR ARMIES METHOD
*/
int Hand::exchange() {
	
	int count = 0;
	int handsize = hand.size();

if (countInfantry(hand) >= 3) {
	
	for (int i = 0; (i < handsize); i++) {
		if (hand.at(i).getType() == "infantry") {			
			hand.at(i).setType("null");
			count++;
			handsize = hand.size();

			if (count == 3)
				break;

		}			
	}
	Hand temp = removeNull(hand);

	setHand(temp);
	
	
	setArmies();
	std::cout << "Here are " << getArmies() << " armies!"<<endl;
	return getArmies();
}

if (countArtillery(hand) >= 3) {
	
	for (int i = 0; (i <handsize); i++) {
		if (hand.at(i).getType() == "artillery") {
			//hand.erase(hand.begin() + i);
			hand.at(i).setType("null");
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

if (countCavalry(hand) >= 3) {
	
	for (int i = 0;(i < handsize); i++) {
		if (hand.at(i).getType() == "cavalry") {
			hand.at(i).setType("null");
			count++;
			handsize = hand.size();

			if (count == 3)
				break;
		}
	}

	Hand temp = removeNull(hand);

	setHand(temp);

	
	setArmies();
	std::cout << "Here are " << getArmies() << " armies!"<<endl;
	return getArmies();
}

if (countInfantry(hand) >= 1 && countInfantry(hand) >= 1 && countArtillery(hand) >= 1) {
	
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i).getType() == "infantry") {
			hand.erase(hand.begin() + i);
			break;
		}
	}
		
		for (int i = 0; i < hand.size(); i++) {
			if (hand.at(i).getType() == "artillery") {
				hand.erase(hand.begin() + i);
				break;
			}
		}
			
			for (int i = 0; i < hand.size(); i++) {
				if (hand.at(i).getType() == "cavalry") {
					hand.erase(hand.begin() + i);
					break;
				}

	}
			
			setArmies();
			std::cout << "Here are " << getArmies() << " armies!"<<endl;
			return getArmies();
}	

std::cout << "You cannot make any exchanges yet. Insufficient/Invalid Cards.";
return 0;
}

void Hand::addToHand(Card card) {
hand.push_back(card);
	
}

void Hand::showHand() {
	int count = 0;
	for (int i = 0; i < getHand().size(); i++) {
		std::cout << getHand().at(i).getType() << endl;
		count++;
	}
}


//int main()
//{
	
// TESTING
//int n = 38;
//Deck aDeck= Deck(n);
//
//
//std::cout << "Original Deck:" << endl;
//aDeck.showDeck();
//std::cout << endl << "Cavalry: " << countCavalry(aDeck.getDeck()) << "   " << "Artillery: " << countArtillery(aDeck.getDeck()) << "       " << "Infantry: " << countInfantry(aDeck.getDeck());
//
//std::cout << endl;
////when you draw then push to hand
//Hand hand1;
//hand1.addToHand(aDeck.draw());
//hand1.addToHand(aDeck.draw());
//hand1.addToHand(aDeck.draw());
//hand1.addToHand(aDeck.draw());
//hand1.addToHand(aDeck.draw());
//hand1.addToHand(aDeck.draw());
//std::cout << endl << "Hand 1 has the following cards: " << endl;
//int count = 0;
//for (int i = 0; i < hand1.getHand().size(); i++) {
//	std::cout << hand1.getHand().at(i).getType() << endl;
//	count++;
//}
//std::cout << count << " cards..." << endl;
//std::cout << endl;
//
//hand1.exchange();
//
//std::cout << endl << "Here are the cards in hand1 after exchange()" << endl;
//count = 0;
//for (int i = 0; i < hand1.getHand().size(); i++) {
//	std::cout << hand1.getHand().at(i).getType() << endl;
//	count++;
//}
//std:: cout << "After exchange, hand1 has: " << count << endl;
//
//std::cout << endl<< "Deck at the end" << endl;;
//aDeck.showDeck();
//
//
//
//std::cout << endl << "Cavalry: " << countCavalry(aDeck.getDeck()) << "   " << "Artillery: " << countArtillery(aDeck.getDeck()) << "       " << "Infantry: " <<countInfantry(aDeck.getDeck());
//
//
//
//
//
//	
//
//
//
//
//return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
