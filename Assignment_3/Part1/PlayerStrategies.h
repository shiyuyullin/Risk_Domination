#pragma once
#include <ostream>
#include <vector>
#include <algorithm>
class Player;
class Map;
class GameEngine;
class Dice;
class Hand;

//The strategy design pattern gives the ability to change player behaviors
//for the same functions in the run time. 

//The super class for all different player stratefies
class Strategy {
protected:
	int* actionsdonehere = new int(0);
public:
	virtual void Reinforce(Player* p) = 0;
	virtual void Attack(Player* p) = 0;
	virtual void Fortify(Player* p) = 0;
	const inline int getAction() { return *actionsdonehere; };
	virtual ~Strategy();
};

//The functions for human players require user interaction to make decisions
class humanPlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};

//The aggressive player(computer player) who focus on attack.
// 1.It always reinforce its strongest country
// 2.It always use that country to attack, until it cannot attack with that country anymore
// 3.Fortifies in order to aggregate its armies into one country
class aggressivePlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};

//The benevolent player(computer player) who focus on protecting its weak countries
// 1.reinforce to its weakest country(reinforce to country with smallest number of armies)
// 2.never attack
// 3.fortify in order to move armies to weaker countries(balance armies among countries)
class beneloventPlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};

class cheaterPlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};

class randomPlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};


