#include <iostream>
#include "Cards.h"
using namespace std;



int main() {

	//initialize number of countries and create deck with cards equaling number of countries
	int numberOfCountries = 42;
	Deck deck1(numberOfCountries);
	 
	//Show deck and number of cards in deck
	cout << "	DEMONSTRATING RISK CARDS" << endl<<endl;
	cout << "=============================================" << endl << "	1.SHOWING COMPOSITION OF DECK" << endl << "=============================================\n";
	deck1.showDeck();

	cout << "Number of cavalry: " << deck1.countCavalry()<<endl;
	cout << "Number of artillery: " << deck1.countArtillery()<<endl;
	cout << "Number of infantry: " << deck1.countInfantry()<<endl;
	cout << "Total number of cards in deck: " << deck1.sizeOfDeck() << endl;

	//Create a hand of cards and draw 5 cards from deck to hand
	cout << "_____________________________________________" << endl;
	cout << "Creating a hand from the deck.\n";
	Hand hand1;

	cout << "\n 	*Drawing FIVE cards from that hand";
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());
	hand1.addToHand(deck1.draw());

	//Showing number of cards in hand created
	cout << endl << "\nShowing hand: " << endl;
	hand1.showHand();

	//Showing cards left in deck after 5 draws 
	cout << "_____________________________________________";
	cout << "\nShowing cards in deck left: \n";
	deck1.showDeck();

	cout << "Number of cavalry: " << deck1.countCavalry()<<endl;
	cout << "Number of artillery: " << deck1.countArtillery()<<endl;
	cout << "Number of infantry: " << deck1.countInfantry()<<endl;
	cout << "Total number of cards in deck: " << deck1.sizeOfDeck() << endl;
	cout << "_____________________________________________";

	//Exchanging cards in deck for armies based on game rules
	cout << "\nExchanging cards from hand for armies...." << "\nArmies received: ";
	hand1.exchange();	

	//Showing cards in hand after exhange
	cout << "\nShowing cards in hand after exchange: " << endl;
	hand1.showHand();

	cout<<endl;
	cout<<endl;
	return 0;
}

