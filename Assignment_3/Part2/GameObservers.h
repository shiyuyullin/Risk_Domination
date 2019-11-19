#pragma once
#include <list>
using namespace std;
#include <string>
/*
Observer design pattern simply used to keep track of all
actions completed after a player phase is complete.
It will display relevant information of what actions the player has 
just taken in their turn.
*/

//respond to Notify() with Update()
class Observer { //Abstract class that will need to be derived by the observer obj/class
public:
	~Observer();
	/*
	Update here accepts the player number (to determine what player
	is the current object affecting the game engine) and the action
	argument is later explained in the implementation of it, but
	to be short this number will go through a series
	of if statements to display the appropriate message to the
	observers, and msg is a flexible string that displays relevant
	information regarding the player's actions.
	Ian Lopez
	*/
	virtual void Update(int player_num, int action, string msg) = 0;
	
	
protected:
	Observer();
};


class Subject {//The object of interest, the observable: the game engine
public:
	virtual void Attach(Observer* o);//Register obsever
	virtual void Detach(Observer* o);//Remove observer
	virtual void Notify(int player_num,int action, string msg);//Boradcast that the object of interest has changed
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;//list of observers
};
