#include <iostream>
#include "Player.h"
#include "D:\Visual Studio\WorkSpace\Map\Map.h"//Path on my computer change it if needed
#include "D:\Visual Studio\WorkSpace\GameEngine\GameEngine.h"//Path on my computer change it if needed
using namespace std;
Player::Player()
{
	dice = new Dice();
	hand = new Hand();
	numberOfCountryOwned = new int(0);
	playerId = new int(0);
}

Player::Player(int id, int armyCount)
{
	dice = new Dice();
	hand = new Hand();
	playerId = new int(id);
	armies = new int(armyCount);
	numberOfCountryOwned = new int(0);
}

Player::~Player()
{
	delete dice;
	delete hand;
	delete numberOfCountryOwned;
	int temp = indexOfCountryOwned.size();
}

void Player::reinforce()
{
	cout << "This method will reinforce"<<endl;
}
//**************************************************************************************************************************************
void Player::attack()
{
	Map* a = GameEngine::getMap();
	int state = 0;
	Country* tempCountry = new Country();//Country to attack from
	Country* tempCountryToAtt = new Country();//Country that will be attacked
	Player* Attacker = new Player();//The player who is attacking
	Player* Defender = new Player();//The player who is attacked
	while (state != 2) {
		cout << "Please choose the following options: 1. attack 2. not attack." << endl;
		cout << "if you want to attack, enter 1, if not enter 2: ";
		cin >> state;
		if (state == 1) {//enter the attack phase loop
			int tempValue = 0;
			int numArmAtt = 0;
			int numArmDef = 0;
			bool state1 = true;
			bool state2 = true;
			cout << "Welcome to the attack phase!" << endl;
			while (state2) {
				cout << "Please choose one of the following country to attack from(The integer value before the country name):" << endl;
				for (int i = 0; i < *numberOfCountryOwned; ++i) {
					tempCountry = a->getCountry(indexOfCountryOwned[i] - 1);
					cout << "You own: " << endl;
					cout << tempCountry->getCountryNumber() << ". " << tempCountry->getCountryName() << ", number of armies: " << tempCountry->getNbOfArmies() << endl;
				}
				//Validating the attacking country(it has at least 2 armies)
				while (state1) {
					cin >> tempValue;
					tempCountry = a->getCountry(tempValue - 1);//get the country to attack from
					int tempComparing = tempCountry->getNbOfArmies();
					if (tempComparing < 2) {
						cout << "The attacking country has less than 2 armies, it cannot be used for attacking, please select another country: " << endl;
					}
					else {
						state1 = false;
					}
				}
				Attacker = tempCountry->getOwner();//get the owner(player) of that country
				numArmAtt = tempCountry->getNbOfArmies();//Getting number of armies on attacking country
				//Validating the attacking path
				//first, get the borders of the selected country
				int* bordersTemp = tempCountry->getBorders();
				int counter = 0;
				int validAttackCountry = 0;
				int serialOfChosenCountry;
				cout << "You can attack:" << endl;
				while (bordersTemp[counter] != -1) {//Validating each border
					tempCountryToAtt = a->getCountry(bordersTemp[counter] - 1);
					Defender = tempCountryToAtt->getOwner();
					if (tempCountry != tempCountryToAtt) {
						if (Attacker != Defender) {
							cout << tempCountryToAtt->getCountryNumber() << ". " << tempCountryToAtt->getCountryName() << endl;
							validAttackCountry++;
						}
					}
					counter++;
				}
				if (validAttackCountry != 0) {
					cout << "Please select a country to attack to(enter the number before the country's name): ";
					cin >> serialOfChosenCountry;
					tempCountryToAtt = a->getCountry(serialOfChosenCountry - 1);//Getting the country which will be attacked
					Defender = tempCountryToAtt->getOwner();//Getting the defender
					numArmDef = tempCountryToAtt->getNbOfArmies();//Getting number of armies on the country which will be attacked
					cout << endl;
					state2 = false;
				}
				else {
					cout << "There is no valid country to attack from the selected country." << endl;
					cout << "Try another country" << endl;
				}
			}
			//Attack between two players
			//Attack phase ends when one of the countries has zero armies on it
			int numberOfDicesAtt = 0;
			//Choosing number of dices for attacker
			if (tempCountry->getNbOfArmies() == 2) {
				cout << "The Attacker can use only one dice, for attacking." << endl;
				numberOfDicesAtt = 1;
			}
			else if (tempCountry->getNbOfArmies() == 3) {
				while (true) {
					cout << "Attacker, Please choose how many dice you want to use(1 or 2):";
					cin >> numberOfDicesAtt;
					cout << endl;
					if (numberOfDicesAtt < 1 || numberOfDicesAtt > 2) {
						cout << "Invalid number of dices, please try again." << endl;
						continue;
					}
					break;
				}
			}
			else {
				while (true) {
					cout << "Atacker, Please choose number of dice you want to use(1,2,or3): ";
					cin >> numberOfDicesAtt;
					cout << endl;
					if (numberOfDicesAtt < 1 || numberOfDicesAtt > 3) {
						cout << "Invalid number of dices, please try again." << endl;
						continue;
					}
					break;
				}
			}
			//Choosing number of dices for defender
			int numberOfDiceDef = 0;
			if (tempCountryToAtt->getNbOfArmies() == 1) {
				cout << "The defender can only use 1 dice, for defending." << endl;
				numberOfDiceDef = 1;
			}
			if (tempCountryToAtt->getNbOfArmies() >= 2) {
				while (true) {
					cout << "Defender, please choose number of dice you want to use(1 or 2): ";
					cin >> numberOfDiceDef;
					cout << endl;
					if (numberOfDiceDef < 1 || numberOfDiceDef > 2) {
						cout << "Invalid number of dice, please try again." << endl;
						continue;
					}
					break;
				}
			}
			//Starting the actual attack 
			while (tempCountry->getNbOfArmies() != 0 && tempCountryToAtt->getNbOfArmies() != 0) {
				Attacker->RollDice(numberOfDicesAtt);
				Defender->RollDice(numberOfDiceDef);
				int tempValForAtt[3];
				int tempValForDef[3];
				//getting all values rolled
				for (int i = 0; i < 3; ++i) {
					tempValForAtt[i] = Attacker->dice->get_value_at(i);
					cout << "Dice " << i << " : " << tempValForAtt[i] << endl;
					tempValForDef[i] = Defender->dice->get_value_at(i);
					cout << "Dice " << i << " : " << tempValForDef[i] << endl;
				}
				//Sorting values from highest to lowest for both array
				int tempForSorting = 0;
				for (int i = 0; i < 3; ++i) {
					for (int j = i + 1; j < 3; ++j) {
						if (tempValForAtt[i] < tempValForAtt[j]) {
							tempForSorting = tempValForAtt[i];
							tempValForAtt[i] = tempValForAtt[j];
							tempValForAtt[j] = tempForSorting;
						}
					}
				}
				for (int i = 0; i < 3; ++i) {
					for (int j = i + 1; j < 3; ++j) {
						if (tempValForDef[i] < tempValForDef[j]) {
							tempForSorting = tempValForDef[i];
							tempValForDef[i] = tempValForDef[j];
							tempValForDef[j] = tempForSorting;
						}
					}
				}
				//Comparing and changing number of armies based on rolled values
				if (numberOfDicesAtt == numberOfDiceDef) {
					for (int i = 0; i < numberOfDicesAtt; ++i) {
						if (tempValForAtt[i] > tempValForDef[i]) {
							--numArmDef;
							tempCountryToAtt->setArmyNumber(numArmDef);
						}
						if (tempValForAtt[i] <= tempValForDef[i]) {
							--numArmAtt;
							tempCountry->setArmyNumber(numArmAtt);
						}
					}
				}
				if (numberOfDicesAtt < numberOfDiceDef) {
					if (tempValForAtt[0] > tempValForDef[0]) {
						--numArmDef;
						tempCountryToAtt->setArmyNumber(numArmDef);
					}
					if (tempValForAtt[0] <= tempValForDef[0]) {
						--numArmAtt;
						tempCountry->setArmyNumber(numArmAtt);
					}
				}
				if (numberOfDicesAtt > numberOfDiceDef) {
					for (int i = 0; i < numberOfDiceDef; ++i) {
						if (tempValForAtt[i] > tempValForDef[i]) {
							--numArmDef;
							tempCountryToAtt->setArmyNumber(numArmDef);
						}
						if (tempValForAtt[i] <= tempValForDef[i]) {
							--numArmAtt;
							tempCountry->setArmyNumber(numArmAtt);
						}
					}
				}
			}
			//After one of the country run out of armies, find out which play win tha round
			//modifying all corresponding attributes
			int indextoSet = 0;
			if (numArmAtt == 0) {
				cout << "Your attack is unsuccessful." << endl;
			}
			else if (numArmDef == 0) {
				int moveArmies = 0;//keep number of arm the player want to move
				int totalArmies = tempCountry->getNbOfArmies();//Keep total number of arm in the attacking country
				cout << "Congratulation! Your attack is successful, now you own the attacked country." << endl;
				//Changing owner of the attacked country, changing player's state
				//state change on defender
				Defender->decrementNumOfCountry();
				int tempSer = tempCountryToAtt->getCountryNumber();
				indexOfCountryOwned.erase(std::remove(indexOfCountryOwned.begin(), indexOfCountryOwned.end(), tempSer), indexOfCountryOwned.end());
				indexOfCountryOwned.shrink_to_fit();
				//statechange on attacker
				tempCountryToAtt->setOwner(Attacker);
				Attacker->setIndexOfCountry(tempCountryToAtt->getCountryNumber());

				while (true) {
					cout << "You can move armies from attacking country(from 1 to total armies - 1)" << endl;
					cout << "You now have: " << tempCountry->getNbOfArmies() << " armies in your attacking country" << endl;
					if (tempCountry->getNbOfArmies() == 1) {
						cout << "You cannot move any army to the attacked country." << endl;
						break;
					}
					cout << "Please enter number of armies you want to move to your new country: ";
					cin >> moveArmies;
					if (moveArmies < 1 || moveArmies > totalArmies - 1) {
						cout << "Invalid number of armies, please try again." << endl;
					}
					else {
						tempCountryToAtt->setArmyNumber(moveArmies);
						tempCountry->setArmyNumber(totalArmies - moveArmies);
						break;
					}
				}
			}
		}
		else if (state == 2) {//return from method attack
			return;
		}
		else {//Invalid input
			cout << "Invalid input, please try again." << endl;

		}
	}
}

 
void Player::foritfy()
{
	Map* a = GameEngine::getMap();//Fake map
	Country* sourceCountry = new Country();
	Country* targetCountry = new Country();
	Player* tempPlayer = this;//Get the player who calls this method
	int numOfArmiesMove = 0;
	int serialNumOfTargetCountry = -1;
	int serialNumOfSourceCountry = -1;
	int originalArmOnSource = 0;
	int originArmOnTarget = 0;
	bool state1 = true;
	bool state2 = true;
	cout << "Welcome to the Fortify phase" << endl;
	while (state1) {
		cout << "Please select one of your owned country as source country: " << endl;
		//Displaying all of the owned countries
		for (int i = 0; i < tempPlayer->getNumOwnedCountry(); ++i) {
			int serialNum = tempPlayer->indexOfCountryOwned[i];
			Country* disPlay = a->getCountry(serialNum - 1);
			cout << disPlay->getCountryNumber() << ". " << disPlay->getCountryName() <<" Armies: " << disPlay->getNbOfArmies() << endl;
		}
		while (true) {
			cout << "Enter the serial number(number before the country's name): ";
			cin >> serialNumOfSourceCountry;
			cout << endl;
			sourceCountry = a->getCountry(serialNumOfSourceCountry - 1);//Getting the source country
			originalArmOnSource = sourceCountry->getNbOfArmies();//Getting original armies on source country
			if (originalArmOnSource <= 1) {
				cout << "Sorry, you cannot select this country as source country because its armies are smaller that or equal to 1." << endl;
				cout << "Please try again" << endl;
				continue;
			}
			break;
			
		}
		//Getting the borders of the source country and find whether it is adjacent to source country
		int* tempBorders = sourceCountry->getBorders();
		//Checking which country can be reached from the source country(could be none)
		int counter = 0;
		int countValidCountry = 0;
		while (tempBorders[counter] != -1) {//Getting one of its borders
			for (int j = 0; j < tempPlayer->getNumOwnedCountry(); ++j) {//loop through all countries that own by the player
				//if the players owns that country and the country is not itself
				if (tempBorders[counter] == indexOfCountryOwned[j]) {
					if (tempBorders[counter] != sourceCountry->getCountryNumber()) {
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
		if (countValidCountry == 0) {
			cout << "Sorry, there is no valid target countries that can be reached from the source country." << endl;
			cout << "Please select another source country." << endl;
		}
		else {
			state1 = false;
			cout << "Please enter the serial number of the target country(the number before the country name): ";
			cin >> serialNumOfTargetCountry;
			cout << endl;
			targetCountry = a->getCountry(serialNumOfTargetCountry - 1);//Getting the target country
			originArmOnTarget = targetCountry->getNbOfArmies();//Getting original armies on target country
			while (state2) {
				cout << "Please enter number of armies you want to move from source country: " << endl;
				cout << "You have: " << sourceCountry->getNbOfArmies() << " in the source country" << endl;
				cin >> numOfArmiesMove;
				if (numOfArmiesMove < 1 || numOfArmiesMove >(sourceCountry->getNbOfArmies() - 1)) {
					cout << "Invalid number of armies, please try again";
				}
				else {
					state2 = false;
					sourceCountry->setArmyNumber(originalArmOnSource - numOfArmiesMove);
					targetCountry->setArmyNumber(originArmOnTarget + numOfArmiesMove);
				}
			}
		}

	}
}
//***********************************************************************************************************************************************************

void Player::RollDice(int n)
{
	dice->Roll(n);
}

void Player::DisplayRollInfo(int n) //Displays: Roll values stored in the array and
									//Percentages
{
	dice->Display(n);
	dice->percentages();
}
void Player::setPlayerID(int id) {
	*playerId = id;
}

void Player::incrementNumOfCountry() {
	*numberOfCountryOwned = *numberOfCountryOwned + 1;
}

void Player::decrementNumOfCountry() {
	*numberOfCountryOwned = *numberOfCountryOwned - 1;
}

void Player::setIndexOfCountry(int serialNum) {
	indexOfCountryOwned.push_back(serialNum);
	*numberOfCountryOwned = *numberOfCountryOwned + 1;
}
int Player::getPlayerID() {
	return *playerId;
}
int Player::getNumOwnedCountry() {
	return *numberOfCountryOwned;
}

int Player::findIndex(int serialNum) {
	int none = -1;
	int tempsize = indexOfCountryOwned.size();
	for (int i = 0; i < tempsize; i++) {
		if (indexOfCountryOwned[i] == serialNum) {
			return i;
		}
	}
	return(none);
}
