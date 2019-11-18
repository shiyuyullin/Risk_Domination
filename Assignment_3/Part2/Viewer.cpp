#include "Viewer.h"
#include "iomanip>

PhaseObserver::PhaseObserver()
{

}

PhaseObserver::~PhaseObserver()
{

}

/*
For the observer pattern to work, we must pass the subject (observable)
as argument to an observer. This is why must pass the Engine itself
as argument and then add the PhaseObserver as an observer
to the list of observers to the engine "engine->Attach(this);"
*/

PhaseObserver::PhaseObserver(GameEngine* en)
{
	engine = en;
	engine->Attach(this);
}

void PhaseObserver::Update(int player_num, int action, string msg)
{
/*
As mentioned before, this code is the implementation of the update
inheritance from Observer class. Where the player_num is to know which
player is currently affecting the game and action is to point the
update function to another function (the functions below display)
to display their appropriate action along with a string, msg,
to make more sense on what is it that just happened in the respective 
phase
*/
display(player_num,action, msg);
}

void PhaseObserver::display(int player_num, int action, string msg)
{
	//0 will display a default message to in this method
	//1 Reinforcement
	//2 Attack
	//3 Fortify
	//else will display a banner that cannot be catogrized from 0-3
	if (action == 0) {
		cout << "==========================\n\tPHASE OBSERVER\n==========================\n";
	}
	else if (action == 1) {
		cout << "Player " << player_num << "'s turn: \n";
		displayReinforceInfo(action, msg);
	}
	else if (action == 2) {
		cout << "Player " << player_num << "'s turn: \n";
		displayAttackInfo(action, msg);
	}
	else if (action == 3) {
		cout << "Player " << player_num << "'s turn: \n";
		displayFortifyInfo(action, msg);
	}
	else {
		cout << "==========================\n\tPHASE OBSERVER\n==========================\n";
		cout << msg << "\n";
	}
}
	

void PhaseObserver::displayReinforceInfo(int a1, string msg)
{
	cout << "==========================\n\tPHASE OBSERVER\n==========================\n";
	cout << "Reinforcement phase:\n" << msg << endl;
}

void PhaseObserver::displayAttackInfo(int a2, string msg)
{
	cout << "==========================\n\tPHASE OBSERVER\n==========================\n";
	cout << "Attacking phase:\n" << msg << endl;
}

void PhaseObserver::displayFortifyInfo(int a3,string msg)
{
	cout << "==========================\n\tPHASE OBSERVER\n==========================\n";
	cout << "Fortifying phase:\n" << msg << endl;
}




GameStatisticsObserver::GameStatisticsObserver(){}  //Default Constructor

GameStatisticsObserver::~GameStatisticsObserver(){}  //Destructor

//Parameterzed Constructor - Game engine pointer as parameter
GameStatisticsObserver::GameStatisticsObserver(GameEngine *en) {

	engine = en;
	engine->Attach(this);
}

//Inherited from Observer class. Calls display method as defined in GameStatisticsObserver class
void GameStatisticsObserver::Update() {
	
	display();
	
}

/*Implements the view of the GamesStatisticsObserver class. Displays congratulatory message if winner is found. Displays world domina
if all countries haven't been dominated by one player yet.
*/
void GameStatisticsObserver::display() {
	std::cout << "\n \n \n";
	
	double playerNumOfCountries; // number of countries dominated by one player
	bool winner = false;	 //boolean check for winner
	int players = engine->getNumOfPlayers(); // number of players in game
	double gameNumOfCountries = engine->getMap()->getNumOfCountries(); //number of countries on map in play

	/*Traversing players vector - checking for winner. If winner is found then winner is set to TRUE and congratulatory message is 
	displayed else player domination stats is displayed */
	for (int i = 0; i < players; i++) {
		playerNumOfCountries = engine->getPlayers().at(i)->getNumOwnedCountry();
		if (playerNumOfCountries == gameNumOfCountries) {
			displayCelebratoryMessage(engine->getPlayers().at(i)->getPlayerId());
			winner = true;
			break;
		}
	}

	if (!winner) 
		displayDomination();
	
	
}

/*Celebratory message if a player wins game */
void GameStatisticsObserver::displayCelebratoryMessage(int iD) {
	cout << "==================================================" << endl;
	cout << "		     WINNER!!!" << endl;
	cout << "==================================================" << endl<<endl;
	cout << "		    *PLAYER "<<iD<<"*" << endl;
	cout << "	 ~				~" << endl << endl;
	cout << " You are a CHAMPION! You are awesome at your game!" << endl;
	cout << "  You have conquered all nations in this world..." << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "--------------------------------------------------" << endl<<endl;

}

/*Game Stats Display View */
void GameStatisticsObserver::displayDomination() {
	int num = engine->getNumOfPlayers();
	double gameNumOfCountries = engine->getMap()->getNumOfCountries();
	std::cout << "===========================" << endl;
	std::cout << " PLAYER | WORLD DOMINATION" << endl;
	std::cout << "===========================" << endl;
	for (int i = 0; i < num; i++) {

		double playerNumOfCountries = engine->getPlayers().at(i)->getNumOwnedCountry();

		if (playerNumOfCountries > 0) {

			double percent = (playerNumOfCountries / gameNumOfCountries) * 100;
			std::cout << "  P" << engine->getPlayers().at(i)->getPlayerId() << "      ";
			std::cout << fixed;
			std::cout << setprecision(2);
			std::cout << percent
				<< "%" << endl;
		}
	}
	std::cout << "===========================" << endl << endl;
}
