#include <iostream>
#include "Cards.h"
using namespace std;


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




int main() {

	int numberOfCountries = 23;
	Deck deck1(numberOfCountries);

	cout << "	DEMONSTRATING RISK CARDS" << endl<<endl;
	cout << "=============================================" << endl << "	1.SHOWING COMPOSITION OF DECK" << endl << "=============================================\n";
	deck1.showDeck();

	cout << "Number of cavalry: " << countCavalry(deck1.getDeck())<<endl;
	cout << "Number of artillery: " << countArtillery(deck1.getDeck())<<endl;
	cout << "Number of infantry: " << countInfantry(deck1.getDeck())<<endl;
	cout << "Total number of cards in deck: " << deck1.sizeOfDeck() << endl;

	cout << "_____________________________________________" << endl;
	cout << "Creating a hand from the deck.\n";
	Hand hand1;

	cout << "\n 	*Drawing FIVE cards from that hand";
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());

	cout << endl << "\nShowing hand: " << endl;
	hand1.showHand();

	cout << "_____________________________________________";
	cout << "\nShowing cards in deck left: \n";
	deck1.showDeck();

	cout << "Number of cavalry: " << countCavalry(deck1.getDeck())<<endl;
	cout << "Number of artillery: " << countArtillery(deck1.getDeck())<<endl;
	cout << "Number of infantry: " << countInfantry(deck1.getDeck())<<endl;
	cout << "Total number of cards in deck: " << deck1.sizeOfDeck() << endl;
	cout << "_____________________________________________";

	cout << "\nExchanging cards from hand for armies...." << "\nArmies received: ";
	hand1.exchange();	

	cout << "\nShowing cards in hand after exchange: " << endl;
	hand1.showHand();

	cout<<endl;
	cout<<endl;
	return 0;
}

