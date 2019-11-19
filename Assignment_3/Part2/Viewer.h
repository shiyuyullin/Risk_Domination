#pragma once
#include "GameObservers.h"
#include "GameEngine.h"
/*

PhaseObserver, an observer of this program.  This class displays relevant information
on what is going in game, mainly after the player has finished their
attack,fortify, or reinforcement and imolements a view of the game statistics (player world domination)

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
	
	void gameStatsDisplay();  //Displays Game Stats
	void displayDomination(); //Displays World Domination
	void displayCelebratoryMessage(int iD); //Displays Winner Celebratory Message
};
