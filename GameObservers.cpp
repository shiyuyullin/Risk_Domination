#include "GameObservers.h"

Observer::~Observer()
{
}

Observer::Observer()
{
}



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
void Subject::Notify(int n) {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(n);
};
