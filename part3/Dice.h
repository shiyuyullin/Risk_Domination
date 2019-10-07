#pragma once
class Dice {
private:
	int value, TotalRolls;
	int *valueptr, *TotalRollsptr;
	int DiceValues[3];
	double percentage[6];
	int* DVptr=DiceValues;
	double* Pptr = percentage;

public:
	Dice();

	void Roll(int n);
	void Display(int rolls);
	void Reset(); //private fields set back to 0
	//private memeber fields
	void percentages();
};
