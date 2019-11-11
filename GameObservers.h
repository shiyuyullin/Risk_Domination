#pragma once
#include <list>
using namespace std;

//Interfaces

//respond to Notify() with Update()
class Observer { //Abstract class that will need to be derived by the observer obj/class
public:
	~Observer();
	virtual void Update(int n) = 0;
protected:
	Observer();
};


class Subject {//The object of interest, the observable, the game engine
public:
	virtual void Attach(Observer* o);//Register obsever
	virtual void Detach(Observer* o);//REmove observer
	virtual void Notify(int n);//Boradcast that the object of interest has changed
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;//list of observers
};
