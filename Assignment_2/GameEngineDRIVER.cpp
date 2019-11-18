#include "GameEngine.h"
#include "Viewer.h"
int main() {

	GameEngine* eng = new GameEngine();
	PhaseObserver* PO = new PhaseObserver(eng);
	GameStatisticsObserver* GSO = new GameStatisticsObserver(eng);
	eng->startGame();

	// Part 3 & 4 Test
	//eng->startGame();
	//eng->testPart3AND4();


	delete eng;
}
