#include "GameObservers.h"
/*
The classes down here will be of no use for this assignment
Ian Lopez
*/
Observer::~Observer()
{
}

Observer::Observer()
{
}


/*
The subject defintions however are of high importance
as these methods instantiate the list of observers
adds and removes observers
And finally, notifies the observers what happened in
the current pahse
Ian Lopez
*/
Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};
void Subject::Notify(int player_num,int action,string msg) {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(player_num,action,msg);
};
