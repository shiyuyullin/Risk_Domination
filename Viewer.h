#pragma once
#include "GameObservers.h"
#include "GameEngine.h"

class PhaseObserver : public Observer {
	/**
	 * Concrete observer that views what is going on with the player's actions on 
	 the game
	 */

private:
	GameEngine* engine;
public:
	PhaseObserver();
	~PhaseObserver();
	PhaseObserver(GameEngine* en);
	void Update(int n);
	void display(int n);
	void displayReinforceInfo();
	void displayAttackInfo();
	void displayFortifyInfo();
};
