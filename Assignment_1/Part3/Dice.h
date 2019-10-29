#pragma once
class Dice {
private:
	int *valueptr, *TotalRollsptr;
	int DiceValues[3];
	double percentage[6];


public:
	Dice();
	~Dice();
	void Roll(int n);
	void Display(int rolls);
	void Reset();
	void percentages();
	const int get_value_at(int n);
};
