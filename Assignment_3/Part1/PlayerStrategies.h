#pragma once
#include <ostream>
#include <vector>
#include <algorithm>
class Player;
class Map;
class GameEngine;
class Dice;
class Hand;

class Strategy {
protected:
	int* actionsdonehere = new int(0);
public:
	virtual void Reinforce(Player* p) = 0;
	virtual void Attack(Player* p) = 0;
	virtual void Fortify(Player* p) = 0;
	const inline int getAction() { return *actionsdonehere; };
};

class humanPlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};

class aggressivePlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};

class beneloventPlayer : public Strategy {
	void Reinforce(Player* p);
	void Attack(Player* p);
	void Fortify(Player* p);
};


