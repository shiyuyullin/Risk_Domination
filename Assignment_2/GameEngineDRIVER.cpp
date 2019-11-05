#include "GameEngine.h"

int main()
{
	//The creation of the game engine obj
	GameEngine *eng = new GameEngine();
	eng->startGame(); //Start up phase is all here, in the contructor of game engin "eng"

	// Part 3 & 4 Test
	//eng->startGame();
	//eng->testPart3AND4();


	delete eng;
}
