#include "GameEngine.h"
#include "D:\Visual Studio\WorkSpace\ObserverForGame\Viewer.h"
int main() {

	GameEngine* eng = new GameEngine();
	PhaseObserver* PO = new PhaseObserver(eng);
	eng->startGame();

	// Part 3 & 4 Test
	//eng->startGame();
	//eng->testPart3AND4();


	delete eng;
}
