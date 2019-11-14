#include "Viewer.h"

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
