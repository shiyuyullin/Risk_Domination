#include "PlayerStrategies.h"
#include "D:\Visual Studio\WorkSpace\Player\Player.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"
#include "D:\Visual Studio\WorkSpace\GameEngine\GameEngine.h" 
#include "D:\Visual Studio\WorkSpace\Dice\Dice.h"
#include "D:\Visual Studio\WorkSpace\Deck\Cards.h"
#include <iostream>
#include <ctime>
#include <random>
using namespace std;


Strategy::~Strategy() {
	delete actionsdonehere;
}

//Implementing Human Player Strategy
//Reinforce:
void humanPlayer::Reinforce(Player* p) {
	Map* gameMap = GameEngine::getMap();
	int tempUsing = p->getNumOwnedCountry();
	int controlledCountries = tempUsing / 3;
	int choice = 0;
	int exchangeBonus = 0;
	Hand* hand = p->getHand();
	//Calculate Player Continent Bonus
	int continentBonus = 0;
	int numberOfCountries;
	int countryCounter = 0;
	for (int i = 0; i < gameMap->getNumOfContinents(); i++)
	{
		numberOfCountries = gameMap->getContinent(i)->getNumOfCountries();
		bool ownsAll = true;
		for (int j = 0; j < numberOfCountries; j++)
		{
			tempUsing = p->getPlayerId();
			if (tempUsing != gameMap->getCountry(countryCounter)->getOwner()->getPlayerId())
			{
				ownsAll = false;
			}
			countryCounter++;
		}
		if (ownsAll)
		{
			continentBonus += gameMap->getContinent(i)->getReward();
		}
	}

	if (hand->getNumberOfCards() > 5) {
		cout << "You have to exchange some cards" << endl;
		exchangeBonus = hand->exchange();
		cout << "You've received an additionnal " << exchangeBonus << " armies" << endl;
	}
	else {
		if (hand->getNumberOfCards() > 0) {
			cout << "Would you like to exchange your cards, Yes(1) or No(2): ";
			while (choice < 1 || choice > 2) {
				cin >> choice;
			}

			cout << endl;

			if (choice == 1) {
				exchangeBonus = hand->exchange();
				cout << "You've received an additional " << exchangeBonus << " armies" << endl;
			}
		}
	}

	int armiesToDistribute = controlledCountries + continentBonus + exchangeBonus;
	cout << "This turn you shall receive an additional " << armiesToDistribute << " armies" << endl;
	cout << controlledCountries << " from your occupied countries" << endl;
	cout << exchangeBonus << " from exchanging cards" << endl;
	cout << continentBonus << " from continent bonuses" << endl;

	cout << "You have: " << hand->getNumberOfCards() << " cards and " << p->getArmies() << " armies." << endl << endl;


	if (armiesToDistribute > 0)
	{
		(*actionsdonehere) = 0;

		cout << "Here are all the countries you control:" << endl << endl;

		for (int i = 0; i < gameMap->getNumOfCountries(); i++)
		{
			Country* temp1 = gameMap->getCountry(i);//Using for outputing information purpose
			if (gameMap->getCountry(i)->getOwner()->getPlayerId() == (p->getPlayerId())) {
				cout << temp1->getCountryNumber() << ". " << temp1->getCountryName() << ", number of armies: " << temp1->getNbOfArmies() << endl;
			}
		}

		cout << "Now input the country you'd like to to add armies followed by the" << endl;
		cout << "number of armies you'd like to add to the tile seperated by a space: " << endl;

		int armies = 0;
		int tile = -1;
		bool owns = false;
		while (armiesToDistribute > 0)
		{
			cout << endl;
			cin >> tile >> armies;
			int counter = 0;
			for (int i = 0; i < p->getNumOwnedCountry(); i++) {
				if (tile == p->getSerialAt(i)) {
					counter++;
				}
			}
			if (tile >= 1 && counter ==1 && armies > 0 && armies <= armiesToDistribute)
			{
				gameMap->getCountry(tile - 1)->addArmies(armies);
				cout << endl;
				cout << gameMap->getCountry(tile - 1)->getCountryName() << " now has ";
				cout << gameMap->getCountry(tile - 1)->getNbOfArmies() << " armies" << endl << endl;
				(*actionsdonehere)++;
				armiesToDistribute -= armies;
				if (armiesToDistribute > 0)
				{
					cout << "You still have " << armiesToDistribute << " armies to distribute." << endl;
					cout << "like before enter the country number and armies to distribute: ";
					cout << endl;
				}
				else
				{
					cout << "You've finished your reinforcement phase. This is how your countries stand: " << endl << endl;

					for (int i = 0; i < gameMap->getNumOfCountries(); i++)
					{
						Country* temp2 = gameMap->getCountry(i);//Using for outputing information purpose
						if (gameMap->getCountry(i)->getOwner()->getPlayerId() == (p->getPlayerId())) {
							cout << temp2->getCountryNumber() << ". " << temp2->getCountryName() << ", number of armies: " << temp2->getNbOfArmies() << endl;
						}
					}
				}
			}
			else
			{
				cout << "That's an invalid input, try again!" << endl;

			}
		}
	}
	else
	{
		cout << "You have no armies to distribute.";
	}
}


//Attack():
void humanPlayer::Attack(Player* p) {
	*actionsdonehere = 0;
	Map* a = GameEngine::getMap();
	//Map* a = gameMap;
	int state = 0;
	Country* tempCountry = new Country();//Country to attack from
	Country* tempCountryToAtt = new Country(); //Country that will be attacked
	Player* Attacker = p;//The player who is attacking
	Dice* attackerDice = p->getDice();
	Player* Defender = new Player();//The player who is attacked
	Dice* defenderDice = new Dice();
	while (state != 2)
	{
		cout << endl;
		cout << "Please choose the following options: 1. attack 2. not attack." << endl;
		cout << "if you want to attack, enter 1, if not enter 2: ";
		cin >> state;
		if (state == 1)
		{ //enter the attack phase loop
			int numArmAtt = 0;
			int numArmDef = 0;
			int tempValue = 0;
			bool state2 = true;
			cout << endl;
			cout << "Welcome to the attack phase!" << endl;
			while (state2)
			{
				bool state1 = true;
				cout << "Please choose one of the following country to attack from(The integer value before the country name):" << endl;
				cout << "You own: " << endl;
				for (int i = 0; i < (p->getNumOwnedCountry()); ++i)
				{
					tempCountry = a->getCountry((p->getSerialAt(i) - 1));
					cout << tempCountry->getCountryNumber() << ". " << tempCountry->getCountryName() << ", number of armies: " << tempCountry->getNbOfArmies() << endl;
				}
				//Validating the attacking country(it has at least 2 armies)
				while (state1)
				{
					cin >> tempValue;
					int countSerial = 0;
					for (int i = 0; i < Attacker->getNumOwnedCountry(); ++i) {
						if (tempValue != (p->getSerialAt(i))) {
							countSerial++;
						}
					}
					if (countSerial == Attacker->getNumOwnedCountry()) {
						cout << "You don't own this country, please enter a valid serial number: " << endl;
					}
					else {
						tempCountry = a->getCountry(tempValue - 1); //get the country to attack from
						int tempComparing = tempCountry->getNbOfArmies();
						if (tempComparing < 2)
						{
							cout << "The attacking country has less than 2 armies, it cannot be used for attacking, please select another country: " << endl;
						}
						else
						{
							state1 = false;
						}
					}
				}
				numArmAtt = tempCountry->getNbOfArmies(); //Getting number of armies on attacking country
				//Validating the attacking path
				//first, get the borders of the selected country
				int* bordersTemp = tempCountry->getBorders();
				int counter = 0;
				int validAttackCountry = 0;
				int serialOfChosenCountry;
				cout << "You can attack:" << endl;
				while (bordersTemp[counter] != -1)
				{ //Validating each border
					tempCountryToAtt = a->getCountry(bordersTemp[counter] - 1);
					Defender = tempCountryToAtt->getOwner();
					if (tempCountry != tempCountryToAtt)
					{
						if (Attacker != Defender)
						{
							cout << tempCountryToAtt->getCountryNumber() << ". " << tempCountryToAtt->getCountryName() << endl;
							validAttackCountry++;
						}
					}
					counter++;
				}
				if (validAttackCountry != 0)
				{
					cout << "Please select a country to attack to(enter the number before the country's name): ";
					cin >> serialOfChosenCountry;
					tempCountryToAtt = a->getCountry(serialOfChosenCountry - 1); //Getting the country which will be attacked
					Defender = tempCountryToAtt->getOwner();					 //Getting the defender
					defenderDice = Defender->getDice();							 //Getting the dice for defender
					numArmDef = tempCountryToAtt->getNbOfArmies();				 //Getting number of armies on the country which will be attacked
					cout << endl;
					state2 = false;
				}
				else
				{
					cout << endl;
					cout << "There is no valid country to attack from the selected country." << endl;
					cout << "Try another country" << endl;
					cout << endl;
				}
			}
			//Attack between two players
			//Attack phase ends when one of the countries has zero armies on it
			int numberOfDicesAtt = 0;
			//Choosing number of dices for attacker
			if (tempCountry->getNbOfArmies() == 2)
			{
				cout << "The Attacker can use only one dice, for attacking." << endl;
				numberOfDicesAtt = 1;
			}
			else if (tempCountry->getNbOfArmies() == 3)
			{
				while (true)
				{
					cout << "Attacker, Please choose how many dice you want to use(1 or 2):";
					cin >> numberOfDicesAtt;
					cout << endl;
					if (numberOfDicesAtt < 1 || numberOfDicesAtt > 2)
					{
						cout << "Invalid number of dices, please try again." << endl;
						continue;
					}
					break;
				}
			}
			else
			{
				while (true)
				{
					cout << "Atacker, Please choose number of dice you want to use(1,2,or3): ";
					cin >> numberOfDicesAtt;
					cout << endl;
					if (numberOfDicesAtt < 1 || numberOfDicesAtt > 3)
					{
						cout << "Invalid number of dices, please try again." << endl;
						continue;
					}
					break;
				}
			}
			//Choosing number of dices for defender
			int numberOfDiceDef = 0;
			if (tempCountryToAtt->getNbOfArmies() == 1)
			{
				cout << "The defender can only use 1 dice, for defending." << endl;
				numberOfDiceDef = 1;
			}
			if (tempCountryToAtt->getNbOfArmies() >= 2)
			{
				while (true)
				{
					cout << "Defender, please choose number of dice you want to use(1 or 2): ";
					cin >> numberOfDiceDef;
					cout << endl;
					if (numberOfDiceDef < 1 || numberOfDiceDef > 2)
					{
						cout << "Invalid number of dice, please try again." << endl;
						continue;
					}
					break;
				}
			}
			//Starting the actual attack
			while (tempCountry->getNbOfArmies() != 0 && tempCountryToAtt->getNbOfArmies() != 0)
			{
				Attacker->RollDice(numberOfDicesAtt);
				Defender->RollDice(numberOfDiceDef);
				int tempValForAtt[3];
				int tempValForDef[3];
				//getting all values rolled
				for (int i = 0; i < 3; ++i)
				{
					tempValForAtt[i] = attackerDice->get_value_at(i);
					cout << "Dice " << i << " : " << tempValForAtt[i] << endl;
					tempValForDef[i] = defenderDice->get_value_at(i);
					cout << "Dice " << i << " : " << tempValForDef[i] << endl;
				}
				//Sorting values from highest to lowest for both array
				int tempForSorting = 0;
				for (int i = 0; i < 3; ++i)
				{
					for (int j = i + 1; j < 3; ++j)
					{
						if (tempValForAtt[i] < tempValForAtt[j])
						{
							tempForSorting = tempValForAtt[i];
							tempValForAtt[i] = tempValForAtt[j];
							tempValForAtt[j] = tempForSorting;
						}
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					for (int j = i + 1; j < 3; ++j)
					{
						if (tempValForDef[i] < tempValForDef[j])
						{
							tempForSorting = tempValForDef[i];
							tempValForDef[i] = tempValForDef[j];
							tempValForDef[j] = tempForSorting;
						}
					}
				}
				//Comparing and changing number of armies based on rolled values
				if (numberOfDicesAtt == numberOfDiceDef)
				{
					for (int i = 0; i < numberOfDicesAtt; ++i)
					{
						if (tempValForAtt[i] > tempValForDef[i])
						{
							--numArmDef;
							tempCountryToAtt->setArmyNumber(numArmDef);
						}
						if (tempValForAtt[i] <= tempValForDef[i])
						{
							--numArmAtt;
							tempCountry->setArmyNumber(numArmAtt);
						}
					}
				}
				if (numberOfDicesAtt < numberOfDiceDef)
				{
					if (tempValForAtt[0] > tempValForDef[0])
					{
						--numArmDef;
						tempCountryToAtt->setArmyNumber(numArmDef);
					}
					if (tempValForAtt[0] <= tempValForDef[0])
					{
						--numArmAtt;
						tempCountry->setArmyNumber(numArmAtt);
					}
				}
				if (numberOfDicesAtt > numberOfDiceDef)
				{
					for (int i = 0; i < numberOfDiceDef; ++i)
					{
						if (tempValForAtt[i] > tempValForDef[i])
						{
							--numArmDef;
							tempCountryToAtt->setArmyNumber(numArmDef);
						}
						if (tempValForAtt[i] <= tempValForDef[i])
						{
							--numArmAtt;
							tempCountry->setArmyNumber(numArmAtt);
						}
					}
				}
			}
			//After one of the country run out of armies, find out which play win tha round
			//modifying all corresponding attributes
			int indextoSet = 0;
			if (numArmAtt == 0)
			{
				cout << "Your attack is unsuccessful." << endl;
			}
			else if (numArmDef == 0)
			{
				int moveArmies = 0;								//keep number of arm the player want to move
				int totalArmies = tempCountry->getNbOfArmies(); //Keep total number of arm in the attacking country
				cout << "Congratulation! Your attack is successful, now you own the attacked country." << endl;
				(*actionsdonehere)++;
				//Changing owner of the attacked country, changing player's state
				//state change on defender
				Defender->decrementNumOfCountry();
				int tempSer = tempCountryToAtt->getCountryNumber();
				int indexSerial = Defender->findIndex(tempSer);
				Defender->removeIndex(indexSerial);
				//statechange on attacker
				tempCountryToAtt->setOwner(Attacker);
				Attacker->setIndexOfCountry(tempCountryToAtt->getCountryNumber());
				Attacker->incrementNumOfCountry();

				while (true)
				{
					cout << "You can move armies from attacking country(from 1 to total armies - 1)" << endl;
					cout << "You now have: " << tempCountry->getNbOfArmies() << " armies in your attacking country" << endl;
					if (tempCountry->getNbOfArmies() == 1)
					{
						cout << "You cannot move any army to the attacked country." << endl;
						break;
					}
					cout << "Please enter number of armies you want to move to your new country: ";
					cin >> moveArmies;
					if (moveArmies < 1 || moveArmies > totalArmies - 1)
					{
						cout << "Invalid number of armies, please try again." << endl;
					}
					else
					{
						tempCountryToAtt->setArmyNumber(moveArmies);
						tempCountry->setArmyNumber(totalArmies - moveArmies);
						break;
					}
				}
			}
		}
		else if (state == 2)
		{ //return from method attack
			return;
		}
		else
		{ //Invalid input
			cout << "Invalid input, please try again." << endl;
		}
	}
}

void humanPlayer::Fortify(Player* p) {
	*actionsdonehere = 0;
	Map* a = GameEngine::getMap();
	//Map* a = gameMap;
	Country* sourceCountry;
	Country* targetCountry;
	Player* tempPlayer = p; //Get the player who calls this method
	int numOfArmiesMove = 0;
	int serialNumOfTargetCountry = -1;
	int serialNumOfSourceCountry = -1;
	int originalArmOnSource = 0;
	int originArmOnTarget = 0;
	bool state1 = true;
	bool state2 = true;
	cout << "Welcome to the Fortify phase" << endl;
	while (state1)
	{
		cout << "Please select one of your owned country as source country: " << endl;
		//Displaying all of the owned countries
		for (int i = 0; i < tempPlayer->getNumOwnedCountry(); ++i)
		{
			int serialNum = tempPlayer->getSerialAt(i);
			Country* disPlay = a->getCountry(serialNum - 1);
			cout << disPlay->getCountryNumber() << ". " << disPlay->getCountryName() << " Armies: " << disPlay->getNbOfArmies() << endl;
		}
		while (true)
		{
			cout << "Enter the serial number(number before the country's name): ";
			cin >> serialNumOfSourceCountry;
			int counterSerial = 0;//Counter to count 
			for (int i = 0; i < tempPlayer->getNumOwnedCountry(); ++i) {
				if (serialNumOfSourceCountry != (p->getSerialAt(i))) {
					counterSerial++;
				}
			}
			cout << endl;
			if (counterSerial == tempPlayer->getNumOwnedCountry()) {
				cout << "You don't own this country, please enter a valid serial number: ";
				cout << endl;
			}
			else {
				sourceCountry = a->getCountry(serialNumOfSourceCountry - 1); //Getting the source country
				originalArmOnSource = sourceCountry->getNbOfArmies();		 //Getting original armies on source country
				if (originalArmOnSource <= 1)
				{
					cout << "Sorry, you cannot select this country as source country because its armies are smaller that or equal to 1." << endl;
					cout << "Please try again" << endl;
					continue;
				}
				break;
			}
		}
		//Getting the borders of the source country and find whether it is adjacent to source country
		int* tempBorders = sourceCountry->getBorders();
		//Checking which country can be reached from the source country(could be none)
		int counter = 0;
		int countValidCountry = 0;
		while (tempBorders[counter] != -1)
		{ //Getting one of its borders
			for (int j = 0; j < tempPlayer->getNumOwnedCountry(); ++j)
			{ //loop through all countries that own by the player
				//if the players owns that country and the country is not itself
				if (tempBorders[counter] == (p->getSerialAt(j)))
				{
					if (tempBorders[counter] != sourceCountry->getCountryNumber())
					{
						//Display the target country information
						Country* tempUsing = a->getCountry(tempBorders[counter] - 1);
						cout << "You may fortify to countries(country): " << endl;
						cout << tempUsing->getCountryNumber() << ". " << tempUsing->getCountryName() << endl;
						countValidCountry++;
					}
				}
			}
			counter++;
		}
		if (countValidCountry == 0)
		{
			cout << "Sorry, there is no valid target countries that can be reached from the source country." << endl;
			cout << "Please select another source country." << endl;
		}
		else
		{
			state1 = false;
			cout << "Please enter the serial number of the target country(the number before the country name): ";
			cin >> serialNumOfTargetCountry;
			cout << endl;
			targetCountry = a->getCountry(serialNumOfTargetCountry - 1); //Getting the target country
			originArmOnTarget = targetCountry->getNbOfArmies();			 //Getting original armies on target country
			while (state2)
			{
				cout << "Please enter number of armies you want to move from source country: " << endl;
				cout << "You have: " << sourceCountry->getNbOfArmies() << " in the source country" << endl;
				cin >> numOfArmiesMove;
				if (numOfArmiesMove < 1 || numOfArmiesMove >(sourceCountry->getNbOfArmies() - 1))
				{
					cout << "Invalid number of armies, please try again";
				}
				else
				{
					state2 = false;
					sourceCountry->setArmyNumber(originalArmOnSource - numOfArmiesMove);
					targetCountry->setArmyNumber(originArmOnTarget + numOfArmiesMove);
					(*actionsdonehere)++;
				}
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------
//Implementing behavior for aggressive player
void aggressivePlayer::Reinforce(Player* p) {
	Map* gameMap = GameEngine::getMap();
	int tempUsing = p->getNumOwnedCountry();
	int controlledCountries = tempUsing / 3;
	int exchangeBonus = 0;
	Hand* hand = p->getHand();
	//Calculate Player Continent Bonus
	int continentBonus = 0;
	int numberOfCountries;
	int countryCounter = 0;
	for (int i = 0; i < gameMap->getNumOfContinents(); i++)
	{
		numberOfCountries = gameMap->getContinent(i)->getNumOfCountries();
		bool ownsAll = true;
		for (int j = 0; j < numberOfCountries; j++)
		{
			tempUsing = p->getPlayerId();
			if (tempUsing != gameMap->getCountry(countryCounter)->getOwner()->getPlayerId())
			{
				ownsAll = false;
			}
			countryCounter++;
		}
		if (ownsAll)
		{
			continentBonus += gameMap->getContinent(i)->getReward();
		}
	}
	//Exchange for armies if the aggressive player has cards
	if (hand->getNumberOfCards() > 0) {
		exchangeBonus = hand->exchange();
	}
	//Number of armies that can be distributed for each round
	int armiesToDistribute = controlledCountries + continentBonus + exchangeBonus;
	//Giving armies to the strongest country
	if (armiesToDistribute > 0)
	{
		//Finding the strongest country(the country with greatest number of armies):
		int counter = p->getNumOwnedCountry();
		int maxCountrySerial = p->getSerialAt(0);//Serial number of the strongest country, initially the serial number at index 0
		Country* strongestCountry = gameMap->getCountry(maxCountrySerial - 1);
		for (int i = 1; i < counter; i++) {
			int tempCompare = p->getSerialAt(i);
			Country* tempCompareCountry = gameMap->getCountry(tempCompare - 1);
			if (strongestCountry->getNbOfArmies() < tempCompareCountry->getNbOfArmies()) {
				maxCountrySerial = tempCompareCountry->getCountryNumber();
				strongestCountry = tempCompareCountry;
			}
		}
		//Giving all armies to the strongest country
		int originalArmies = strongestCountry->getNbOfArmies();
		strongestCountry->setArmyNumber(originalArmies + armiesToDistribute);
	}
}

void aggressivePlayer::Attack(Player* p) {
	Map* a = GameEngine::getMap();
	//Map* a = gameMap;
	Country* tempCountry = new Country();
	Country* tempCountryToAtt = new Country();
	Player* Attacker = p;//Attacker
	Dice* attackerDice = Attacker->getDice();//Dice for attacker
	Player* Defender = new Player();
	Dice* defenderDice = Defender->getDice();
	//Find the strongest country
	int maxCountrySerial = p->getSerialAt(0);//Serial number of the strongest country, initially the serial number at index 0
	tempCountry = a->getCountry(maxCountrySerial - 1);//the strongest country for attacker
	for (int i = 1; i < p->getNumOwnedCountry(); i++) {
		int tempCompare = p->getSerialAt(i);
		Country* tempCompareCountry = a->getCountry(tempCompare - 1);
		if (tempCountry->getNbOfArmies() < tempCompareCountry->getNbOfArmies()) {
			maxCountrySerial = tempCompareCountry->getCountryNumber();
			tempCountry = tempCompareCountry;
		}
	}
	int numArmAtt = tempCountry->getNbOfArmies();//number of armies on attacking country
	int* bordersTemp = tempCountry->getBorders();
	int counter = 0;
	//After the strongest country has been found, check if it satisifies the condition
	//Must have at least 2 armies
	if (tempCountry->getNbOfArmies() >= 2) {//Keep attacking until the country has less than 2 armies
		//Validating borders
		while (bordersTemp[counter] != -1)
		{
			//Validating each border
			//Once a validate country is found, attack it immediately
			tempCountryToAtt = a->getCountry(bordersTemp[counter] - 1);//Getting the defending country
			Defender = tempCountryToAtt->getOwner();//Getting the defender
			defenderDice = Defender->getDice();//Getting the dice for defender
			int numArmDef = tempCountryToAtt->getNbOfArmies();
			if (tempCountry->getNbOfArmies() >= 2)
			{
				if (tempCountry != tempCountryToAtt)
				{
					if (Attacker != Defender)
					{

						//Start attacking
						//Attack between two players
						//Attack phase ends when one of the countries has zero armies on it
						int numberOfDicesAtt = 0;
						//Choosing number of dices for attacker
						if (tempCountry->getNbOfArmies() == 2)
						{
							numberOfDicesAtt = 1;
						}
						else if (tempCountry->getNbOfArmies() == 3)
						{
							numberOfDicesAtt = 2;
						}
						else
						{
							numberOfDicesAtt = 3;
						}
						//Choosing number of dices for defender
						int numberOfDiceDef = 0;
						if (tempCountryToAtt->getNbOfArmies() == 1)
						{
							numberOfDiceDef = 1;
						}
						if (tempCountryToAtt->getNbOfArmies() >= 2)
						{
							numberOfDiceDef = 2;
						}
						//Starting the actual attack
						while (tempCountry->getNbOfArmies() != 0 && tempCountryToAtt->getNbOfArmies() != 0)
						{
							Attacker->RollDice(numberOfDicesAtt);
							Defender->RollDice(numberOfDiceDef);
							int tempValForAtt[3];
							int tempValForDef[3];
							//getting all values rolled
							for (int i = 0; i < 3; ++i)
							{
								tempValForAtt[i] = attackerDice->get_value_at(i);
								tempValForDef[i] = defenderDice->get_value_at(i);
							}
							//Sorting values from highest to lowest for both array
							int tempForSorting = 0;
							for (int i = 0; i < 3; ++i)
							{
								for (int j = i + 1; j < 3; ++j)
								{
									if (tempValForAtt[i] < tempValForAtt[j])
									{
										tempForSorting = tempValForAtt[i];
										tempValForAtt[i] = tempValForAtt[j];
										tempValForAtt[j] = tempForSorting;
									}
								}
							}
							for (int i = 0; i < 3; ++i)
							{
								for (int j = i + 1; j < 3; ++j)
								{
									if (tempValForDef[i] < tempValForDef[j])
									{
										tempForSorting = tempValForDef[i];
										tempValForDef[i] = tempValForDef[j];
										tempValForDef[j] = tempForSorting;
									}
								}
							}
							//Comparing and changing number of armies based on rolled values
							if (numberOfDicesAtt == numberOfDiceDef)
							{
								for (int i = 0; i < numberOfDicesAtt; ++i)
								{
									if (tempValForAtt[i] > tempValForDef[i])
									{
										--numArmDef;
										tempCountryToAtt->setArmyNumber(numArmDef);
									}
									if (tempValForAtt[i] <= tempValForDef[i])
									{
										--numArmAtt;
										tempCountry->setArmyNumber(numArmAtt);
									}
								}
							}
							if (numberOfDicesAtt < numberOfDiceDef)
							{
								if (tempValForAtt[0] > tempValForDef[0])
								{
									--numArmDef;
									tempCountryToAtt->setArmyNumber(numArmDef);
								}
								if (tempValForAtt[0] <= tempValForDef[0])
								{
									--numArmAtt;
									tempCountry->setArmyNumber(numArmAtt);
								}
							}
							if (numberOfDicesAtt > numberOfDiceDef)
							{
								for (int i = 0; i < numberOfDiceDef; ++i)
								{
									if (tempValForAtt[i] > tempValForDef[i])
									{
										--numArmDef;
										tempCountryToAtt->setArmyNumber(numArmDef);
									}
									if (tempValForAtt[i] <= tempValForDef[i])
									{
										--numArmAtt;
										tempCountry->setArmyNumber(numArmAtt);
									}
								}
							}
						}
						//After one of the country run out of armies, find out which player wins the round
						//modifying all corresponding attributes
						int indextoSet = 0;
						if (numArmAtt == 0)
						{
							break;
						}
						else if (numArmDef == 0)
						{
							int moveArmies = 0;								//keep number of arm the player want to move
							int totalArmies = tempCountry->getNbOfArmies(); //Keep total number of arm in the attacking country
							//Changing owner of the attacked country, changing player's state
							//state change on defender
							Defender->decrementNumOfCountry();
							int tempSer = tempCountryToAtt->getCountryNumber();
							int indexSerial = Defender->findIndex(tempSer);
							Defender->removeIndex(indexSerial);
							//statechange on attacker
							tempCountryToAtt->setOwner(Attacker);
							Attacker->setIndexOfCountry(tempCountryToAtt->getCountryNumber());
							Attacker->incrementNumOfCountry();
							//Moving armies from attacking country to attacked country
							if (tempCountry->getNbOfArmies() == 1)
							{
								//do nothing
							}
							else {//move only 1 army to the attacked country
								moveArmies = 1;
								tempCountryToAtt->setArmyNumber(moveArmies);
								tempCountry->setArmyNumber(totalArmies - moveArmies);
							}
						}
					}
				}
			}
			counter++;
		}
	}
}

void aggressivePlayer::Fortify(Player* p) {
	Map* a = GameEngine::getMap();
	//Map* a = gameMap;
	Country* sourceCountry;
	Country* targetCountry;
	Player* tempPlayer = p; //Get the player who calls this method
	int numOfArmiesMove = 0;
	int originalArmOnSource = 0;
	int originArmOnTarget = 0;
	int* tempBorders;
	int validSourceCountry = 0;
	//aggregrating armies
	//Selecting the source country:
	for (int i = 0; i < (tempPlayer->getNumOwnedCountry()); i++) {
		sourceCountry = a->getCountry((tempPlayer->getSerialAt(i) - 1));
		originalArmOnSource = sourceCountry->getNbOfArmies();
		if (originalArmOnSource >= 2) {
			//start fortifying from the source country
			tempBorders = sourceCountry->getBorders();
			//validating borders
			int counter = 0;
			while (tempBorders[counter] != -1)
			{ //Getting one of its borders
				for (int j = 0; j < tempPlayer->getNumOwnedCountry(); ++j)
				{ //loop through all countries that own by the player
					//if the players owns that country and the country is not itself
					if (tempBorders[counter] == (p->getSerialAt(j)))
					{
						if (tempBorders[counter] != sourceCountry->getCountryNumber())
						{
							targetCountry = a->getCountry(tempBorders[counter] - 1);
							originArmOnTarget = targetCountry->getNbOfArmies();
							if (originalArmOnSource <= originArmOnTarget) {
								targetCountry->setArmyNumber(originArmOnTarget + (originalArmOnSource - 1));
								sourceCountry->setArmyNumber(originalArmOnSource - (originalArmOnSource - 1));
								return;
							}
						}
					}
				}
				counter++;
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------
//The benevolent computer player will always reinforce its weakest country(the country with smallest number of armies)
void beneloventPlayer::Reinforce(Player* p) {
	Map* gameMap = GameEngine::getMap();
	int tempUsing = p->getNumOwnedCountry();
	int controlledCountries = tempUsing / 3;
	int exchangeBonus = 0;
	Hand* hand = p->getHand();
	//Calculate Player Continent Bonus
	int continentBonus = 0;
	int numberOfCountries;
	int countryCounter = 0;
	for (int i = 0; i < gameMap->getNumOfContinents(); i++)
	{
		numberOfCountries = gameMap->getContinent(i)->getNumOfCountries();
		bool ownsAll = true;
		for (int j = 0; j < numberOfCountries; j++)
		{
			tempUsing = p->getPlayerId();
			if (tempUsing != gameMap->getCountry(countryCounter)->getOwner()->getPlayerId())
			{
				ownsAll = false;
			}
			countryCounter++;
		}
		if (ownsAll)
		{
			continentBonus += gameMap->getContinent(i)->getReward();
		}
	}
	//Exchange for armies if the benelovent player has cards
	if (hand->getNumberOfCards() > 0) {
		exchangeBonus = hand->exchange();
	}
	//Number of armies that can be distributed for each round
	int armiesToDistribute = controlledCountries + continentBonus + exchangeBonus;
	//Giving armies to the weakest country
	if (armiesToDistribute > 0)
	{
		//Finding the weakest country(the country with smallest number of armies):
		int counter = p->getNumOwnedCountry();
		int CountrySerial = p->getSerialAt(0);//Serial number of the weakest country, initially the serial number at index 0
		Country* weakestCountry = gameMap->getCountry(CountrySerial - 1);
		for (int i = 1; i < counter; i++) {
			int tempCompare = p->getSerialAt(i);
			Country* tempCompareCountry = gameMap->getCountry(tempCompare - 1);
			if (weakestCountry->getNbOfArmies() > tempCompareCountry->getNbOfArmies()) {
				CountrySerial = tempCompareCountry->getCountryNumber();
				weakestCountry = tempCompareCountry;
			}
		}
		//Giving all armies to the weakest country
		int originalArmies = weakestCountry->getNbOfArmies();
		int newArmies = originalArmies + armiesToDistribute;
		weakestCountry->setArmyNumber(newArmies);
	}
}

//The attack for benelovent players does nothing
//Because the benolovent players never attack
void beneloventPlayer::Attack(Player* p) {
	return;
}

//Fortify for benelovent players
//Move armies to weaker countries
void beneloventPlayer::Fortify(Player* p) {
	Map* a = GameEngine::getMap();
	Player* tempPlayer = p;
	Country* sourceCountry;
	Country* targetCountry;
	int originArmiesOnSource = 0;
	int originArmiesOnTarget = 0;
	int* tempBorders;

	//Selecting source country
	for (int i = 0; i < tempPlayer->getNumOwnedCountry(); i++) {
		sourceCountry = a->getCountry((tempPlayer->getSerialAt(i) - 1));
		originArmiesOnSource = sourceCountry->getNbOfArmies();
		//if the number of armies on source country is >= 2 then it is a valid source, else go check the next country
		if (originArmiesOnSource >= 2) {
			//Getting borders of sourceCountry
			tempBorders = sourceCountry->getBorders();
			int counter = 0;
			while (tempBorders[counter] != -1) {
				for (int i = 0; i < tempPlayer->getNumOwnedCountry(); i++) {
					if (tempBorders[counter] == tempPlayer->getSerialAt(i)) {
						if (tempBorders[counter] != sourceCountry->getCountryNumber()) {
							//Here a valid target country is found
							targetCountry = a->getCountry(tempBorders[counter] - 1);
							originArmiesOnTarget = targetCountry->getNbOfArmies();
							//There are three cases:
							//1.Both the source country and the target country have the same number of armies;
							//we will just go to the next adjacent country
							if (originArmiesOnSource == originArmiesOnTarget) {
								break;
							}
							//2. if the source country has more amies than target country:
							//it will send armies to the target country(weaker country)
							//and balance the armies on both countries
							if (originArmiesOnSource > originArmiesOnTarget) {
								while (originArmiesOnSource > originArmiesOnTarget) {
									originArmiesOnSource--;
									originArmiesOnTarget++;
								}
								sourceCountry->setArmyNumber(originArmiesOnSource);
								targetCountry->setArmyNumber(originArmiesOnTarget);
								return;
							}
							//3. if the source country has less armies than target country:
							//Should just do nothing and go to the next border
							if (originArmiesOnSource < originArmiesOnTarget) {
								break;
							}
						}
					}
				}
				counter++;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------
//Implementation for cheater player
//The reinforce function for cheater will double the armies on all its countries
void cheaterPlayer::Reinforce(Player* p) {
	Map* gameMap = GameEngine::getMap();
	Country* tempCountry;
	Player* tempPlayer = p;
	for (int i = 0; i < tempPlayer->getNumOwnedCountry(); i++) {//Doubling number of armies on all cheater's countries
		int countrySerial = tempPlayer->getSerialAt(i);//Getting the serial number of the country
		tempCountry = gameMap->getCountry(countrySerial - 1);//Getting a pointer to the actual country object
		int originalArmies = tempCountry->getNbOfArmies();//Getting the original number of armies
		tempCountry->setArmyNumber(originalArmies * 2);//Double the number of armies on that country
	}
}

//The attack function for cheater will automatically conquer all the neighbors of all its countries
void cheaterPlayer::Attack(Player* p) {
	Map* gameMap = GameEngine::getMap();
	Country* tempCountry;//The country to attack from
	Country* defCountry;//The country which is attacked
	Player* cheater = p;
	for (int i = 0; i < cheater->getNumOwnedCountry(); i++) {
		int countrySerial = p->getSerialAt(i);
		tempCountry = gameMap->getCountry(countrySerial - 1);
		int* tempBorders = tempCountry->getBorders();
		int counter = 0;
		while (tempBorders[counter] != -1) {
			defCountry = gameMap->getCountry(tempBorders[counter] - 1);
			if (tempCountry->getOwner() != defCountry->getOwner()) {
				defCountry->setOwner(cheater);
				cheater->setIndexOfCountry(defCountry->getCountryNumber());
				cheater->incrementNumOfCountry();
			}
			counter++;
		}
	}
}

void cheaterPlayer::Fortify(Player* p) {
	Map* gameMap = GameEngine::getMap();
	Country* tempCountry;
	Player* cheater = p;
	Country* otherCountry;//Another pointer to country, for checking purpose
	for (int i = 0; i < cheater->getNumOwnedCountry(); i++) {
		int countrySerial = p->getSerialAt(i);
		tempCountry = gameMap->getCountry(countrySerial - 1);
		int* tempBorders = tempCountry->getBorders();
		int counter = 0;
		int neighborsDif = 0;
		while (tempBorders[counter] != -1) {
			otherCountry = gameMap->getCountry(tempBorders[counter] - 1);
			if (otherCountry->getOwner() != cheater) {
				neighborsDif++;
			}
			counter++;
		}
		if (neighborsDif > 0) {
			int originArmies = tempCountry->getNbOfArmies();
			tempCountry->setArmyNumber(originArmies * 2);
		}
	}
}

//----------------------------------------------------------------------------------------------
//Random player

void randomPlayer::Reinforce(Player* p) {
	Map* gameMap = GameEngine::getMap();
	int tempUsing = p->getNumOwnedCountry();
	int controlledCountries = tempUsing / 3;
	int choice = 0;
	int exchangeBonus = 0;
	Hand* hand = p->getHand();
	//Creating a random generator
	std::mt19937 generator;
	generator.seed(std::time(0));
	//Calculate Player Continent Bonus
	int continentBonus = 0;
	int numberOfCountries;
	int countryCounter = 0;
	for (int i = 0; i < gameMap->getNumOfContinents(); i++)
	{
		numberOfCountries = gameMap->getContinent(i)->getNumOfCountries();
		bool ownsAll = true;
		for (int j = 0; j < numberOfCountries; j++)
		{
			tempUsing = p->getPlayerId();
			if (tempUsing != gameMap->getCountry(countryCounter)->getOwner()->getPlayerId())
			{
				ownsAll = false;
			}
			countryCounter++;
		}
		if (ownsAll)
		{
			continentBonus += gameMap->getContinent(i)->getReward();
		}
	}

	if (hand->getNumberOfCards() > 5) {
		exchangeBonus = hand->exchange();
	}
	else {
		if (hand->getNumberOfCards() > 0) {
			std::uniform_int_distribution<int> one_or_two(1, 2);
			choice = one_or_two(generator);
			if (choice == 1) {
				exchangeBonus = hand->exchange();
			}
		}
	}
	//Total number of armies to be distributed from continent bonus and card exchange bonus and contry control
	int armiesToDistribute = controlledCountries + continentBonus + exchangeBonus;
	
	if (armiesToDistribute > 0)
	{
		(*actionsdonehere) = 0;

		int armies = 0;
		int tile = -1;
		bool owns = false;
		std::uniform_int_distribution<int> GenerCountrySerial(0, (p->getNumOwnedCountry() - 1));
		while (armiesToDistribute > 0)
		{
			std::uniform_int_distribution<int> GenerArmy(1, armiesToDistribute);
			//Generating a random contry serial number
			int randomCountryIndex = GenerCountrySerial(generator);
			tile = p->getSerialAt(randomCountryIndex);//tile contains the random generated country serial number
			//Generating random number of armies to distribute
			int randomArmyNumber = GenerArmy(generator);
			armies = randomArmyNumber;
			if (tile >= 1 && armies > 0 && armies <= armiesToDistribute)
			{
				gameMap->getCountry(tile - 1)->addArmies(armies);
				(*actionsdonehere)++;
				armiesToDistribute -= armies;
			}
		}
	}
}

void randomPlayer::Attack(Player* p) {
	*actionsdonehere = 0;
	Map* a = GameEngine::getMap();
	//Map* a = gameMap;
	int state = 0;
	Country* tempCountry = new Country();//Country to attack from
	Country* tempCountryToAtt = new Country(); //Country that will be attacked
	Player* Attacker = p;//The player who is attacking
	Dice* attackerDice = p->getDice();
	Player* Defender = new Player();//The player who is attacked
	Dice* defenderDice = new Dice();
	//Creating random number generator
	std::mt19937 generator;
	generator.seed(std::time(0));

	while (state != 2)
	{
		std::uniform_int_distribution<int> att_natt(1, 2);
		state = att_natt(generator);
		if (state == 1)
		{ //enter the attack phase loop
			int numArmAtt = 0;
			int numArmDef = 0;
			int tempValue = 0;
			bool state2 = true;
			while (state2)
			{
				bool state1 = true;
				//Validating the attacking country(it has at least 2 armies)
				while (state1)
				{
					std::uniform_int_distribution<int> randomIndex(0, (Attacker->getNumOwnedCountry() - 1));
					int CountryIndex = randomIndex(generator);//Generating a random index
					tempValue = Attacker->getSerialAt(CountryIndex);//Getting the serial number for the country to attack from
					tempCountry = a->getCountry(tempValue - 1); //get the country to attack from
					int tempComparing = tempCountry->getNbOfArmies();
					if (tempComparing < 2)
					{
						continue;
					}
					else
					{
						state1 = false;
					}
					
				}
				numArmAtt = tempCountry->getNbOfArmies(); //Getting number of armies on attacking country
				//Validating the attacking path
				//first, get the borders of the selected country
				int* bordersTemp = tempCountry->getBorders();
				int counter = 0;
				int validAttackCountry = 0;
				int serialOfChosenCountry;
				while (bordersTemp[counter] != -1)
				{ //Validating each border
					tempCountryToAtt = a->getCountry(bordersTemp[counter] - 1);
					Defender = tempCountryToAtt->getOwner();
					if (tempCountry != tempCountryToAtt)
					{
						if (Attacker != Defender)
						{
							serialOfChosenCountry = tempCountryToAtt->getCountryNumber();
							validAttackCountry++;
						}
					}
					counter++;
				}
				if (validAttackCountry != 0)
				{
					tempCountryToAtt = a->getCountry(serialOfChosenCountry - 1); //Getting the country which will be attacked
					Defender = tempCountryToAtt->getOwner();					 //Getting the defender
					defenderDice = Defender->getDice();							 //Getting the dice for defender
					numArmDef = tempCountryToAtt->getNbOfArmies();				 //Getting number of armies on the country which will be attacked
					state2 = false;
				}
			}
			//Attack between two players
			//Attack phase ends when one of the countries has zero armies on it
			int numberOfDicesAtt = 0;
			//Choosing number of dices for attacker
			if (tempCountry->getNbOfArmies() == 2)
			{
				numberOfDicesAtt = 1;
			}
			else if (tempCountry->getNbOfArmies() == 3)
			{
				std::uniform_int_distribution<int> one_or_two_dice(1, 2);
				numberOfDicesAtt = one_or_two_dice(generator);
			}
			else
			{
				std::uniform_int_distribution<int> one_two_three_dice(1, 3);
				numberOfDicesAtt = one_two_three_dice(generator);
			}
			//Choosing number of dices for defender
			int numberOfDiceDef = 0;
			if (tempCountryToAtt->getNbOfArmies() == 1)
			{
				numberOfDiceDef = 1;
			}
			if (tempCountryToAtt->getNbOfArmies() >= 2)
			{
				std::uniform_int_distribution<int> one_two_dice_Def(1, 2);
				numberOfDiceDef = one_two_dice_Def(generator);
			}
			//Starting the actual attack
			while (tempCountry->getNbOfArmies() != 0 && tempCountryToAtt->getNbOfArmies() != 0)
			{
				Attacker->RollDice(numberOfDicesAtt);
				Defender->RollDice(numberOfDiceDef);
				int tempValForAtt[3];
				int tempValForDef[3];
				//getting all values rolled
				for (int i = 0; i < 3; ++i)
				{
					tempValForAtt[i] = attackerDice->get_value_at(i);
					tempValForDef[i] = defenderDice->get_value_at(i);
				}
				//Sorting values from highest to lowest for both array
				int tempForSorting = 0;
				for (int i = 0; i < 3; ++i)
				{
					for (int j = i + 1; j < 3; ++j)
					{
						if (tempValForAtt[i] < tempValForAtt[j])
						{
							tempForSorting = tempValForAtt[i];
							tempValForAtt[i] = tempValForAtt[j];
							tempValForAtt[j] = tempForSorting;
						}
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					for (int j = i + 1; j < 3; ++j)
					{
						if (tempValForDef[i] < tempValForDef[j])
						{
							tempForSorting = tempValForDef[i];
							tempValForDef[i] = tempValForDef[j];
							tempValForDef[j] = tempForSorting;
						}
					}
				}
				//Comparing and changing number of armies based on rolled values
				if (numberOfDicesAtt == numberOfDiceDef)
				{
					for (int i = 0; i < numberOfDicesAtt; ++i)
					{
						if (tempValForAtt[i] > tempValForDef[i])
						{
							--numArmDef;
							tempCountryToAtt->setArmyNumber(numArmDef);
						}
						if (tempValForAtt[i] <= tempValForDef[i])
						{
							--numArmAtt;
							tempCountry->setArmyNumber(numArmAtt);
						}
					}
				}
				if (numberOfDicesAtt < numberOfDiceDef)
				{
					if (tempValForAtt[0] > tempValForDef[0])
					{
						--numArmDef;
						tempCountryToAtt->setArmyNumber(numArmDef);
					}
					if (tempValForAtt[0] <= tempValForDef[0])
					{
						--numArmAtt;
						tempCountry->setArmyNumber(numArmAtt);
					}
				}
				if (numberOfDicesAtt > numberOfDiceDef)
				{
					for (int i = 0; i < numberOfDiceDef; ++i)
					{
						if (tempValForAtt[i] > tempValForDef[i])
						{
							--numArmDef;
							tempCountryToAtt->setArmyNumber(numArmDef);
						}
						if (tempValForAtt[i] <= tempValForDef[i])
						{
							--numArmAtt;
							tempCountry->setArmyNumber(numArmAtt);
						}
					}
				}
			}
			//After one of the country run out of armies, find out which play win tha round
			//modifying all corresponding attributes
			int indextoSet = 0;
			if (numArmAtt == 0)//unseccessful attack
			{
				cout << endl;
			}
			else if (numArmDef == 0)//successful attack
			{
				int moveArmies = 0;								//keep number of arm the player want to move
				int totalArmies = tempCountry->getNbOfArmies(); //Keep total number of arm in the attacking country
				(*actionsdonehere)++;
				//Changing owner of the attacked country, changing player's state
				//state change on defender
				Defender->decrementNumOfCountry();
				int tempSer = tempCountryToAtt->getCountryNumber();
				int indexSerial = Defender->findIndex(tempSer);
				Defender->removeIndex(indexSerial);
				//statechange on attacker
				tempCountryToAtt->setOwner(Attacker);
				Attacker->setIndexOfCountry(tempCountryToAtt->getCountryNumber());
				Attacker->incrementNumOfCountry();
				//Moving random number of armies to the new country
				while (true)
				{
					//If there is only one arm left on the attacking country, do nothing
					if (tempCountry->getNbOfArmies() == 1)
					{
						break;
					}
					//If there are more than one armies on the attacking country, move 1 to (army-1) number of armies to the newly owned country
					std::uniform_int_distribution<int> random_move_army(1, (tempCountry->getNbOfArmies() - 1));
					moveArmies = random_move_army(generator);
					tempCountryToAtt->setArmyNumber(moveArmies);
					tempCountry->setArmyNumber(totalArmies - moveArmies);
					break;
					
				}
			}
		}
		else if (state == 2)
		{ //return from method attack
			return;
		}
	}
}

void randomPlayer::Fortify(Player* p) {
	*actionsdonehere = 0;
	Map* a = GameEngine::getMap();
	//Map* a = gameMap;
	Country* sourceCountry;
	Country* targetCountry;
	Player* tempPlayer = p; //Get the player who calls this method
	int serialNumOfSourceCountry = -1;
	int originalArmOnSource = 0;
	int originArmOnTarget = 0;
	bool state1 = true;
	//Creating random number generator
	std::mt19937 generator;
	generator.seed(std::time(0));

	while (state1)
	{
		while (true)
		{
			//Generating a random country serial number
			std::uniform_int_distribution<int> random_index(0, (tempPlayer->getNumOwnedCountry() - 1));
			serialNumOfSourceCountry = tempPlayer->getSerialAt(random_index(generator));
			sourceCountry = a->getCountry(serialNumOfSourceCountry - 1); //Getting the source country
			originalArmOnSource = sourceCountry->getNbOfArmies();		 //Getting original armies on source country
			if (originalArmOnSource <= 1)//The source country has at least two armies on it
			{
				continue;
			}
			break;
		}
		//Getting the borders of the source country and find whether it is adjacent to source country
		int* tempBorders = sourceCountry->getBorders();
		//Checking which country can be reached from the source country(could be none)
		int counter = 0;
		while (tempBorders[counter] != -1)
		{ //Getting one of its borders
			for (int j = 0; j < tempPlayer->getNumOwnedCountry(); ++j)
			{ //loop through all countries that own by the player
				//if the players owns that country and the country is not itself
				if (tempBorders[counter] == (p->getSerialAt(j)))
				{
					if (tempBorders[counter] != sourceCountry->getCountryNumber())
					{
						targetCountry = a->getCountry(tempBorders[counter] - 1);
						originArmOnTarget = targetCountry->getNbOfArmies();
						std::uniform_int_distribution<int> moving_armies(1, (originalArmOnSource - 1));
						int armyMoved = moving_armies(generator);
						sourceCountry->setArmyNumber(originalArmOnSource - armyMoved);
						targetCountry->setArmyNumber(originArmOnTarget + armyMoved);
						return;
					}
				}
			}
			counter++;
		}
	}
}

