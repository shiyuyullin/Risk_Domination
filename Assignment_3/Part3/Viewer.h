#pragma once
#include "GameObservers.h"
#include "GameEngine.h"
/*
PhaseObserver, an observer of this program. They 
are simple classes that display relevant information
on what is going in game, mainly after the player has finished their
attack,fortify, or reinforcement.
Ian Lopez
*/
class PhaseObserver : public Observer {

private:
	GameEngine* engine;
public:
	PhaseObserver();
	~PhaseObserver();
	PhaseObserver(GameEngine* en);
	void Update(int player_num,int action,string msg);
	void display(int player_num, int action, string msg);
	void displayReinforceInfo(int a1,string msg);//1
	void displayAttackInfo(int a2,string msg);//2
	void displayFortifyInfo(int a3,string msg);//3
};
