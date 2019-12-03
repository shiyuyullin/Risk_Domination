#include "GameEngine.h"
#include "D:\Visual Studio\WorkSpace\ObserverForGame\Viewer.h"



int main() {
	int choice = 0;
	cout << "Select a single player [1] or tournament mode [2]" << endl;
	cin >> choice;
	if (choice == 1) {
		GameEngine* eng = new GameEngine();
		PhaseObserver* PO = new PhaseObserver(eng);
		eng->startGame();
		delete eng;
	}
	else if (choice == 2) {
		int maps_to_be_played = 0;
		do {
			cout << "Please select how many maps you'd like to have in rotation [1-5]: \n";
			cin >> maps_to_be_played;
		} while (maps_to_be_played < 1 or maps_to_be_played > 6);
		int computers = 0;
		do {
			cout << "Please select how many computers will play [2-4]: \n";
			cin >> computers;
		} while (computers < 2 or computers > 4);
		int rounds_per_game = 0;
		do {
			cout << "Please select how many rounds per map you will simulate [1-5]: \n";
			cin >> rounds_per_game;
		} while (rounds_per_game < 1 or rounds_per_game > 5);
		//TURNS TO CONSIDER A VICTORY
		int draw = 10;
		GameEngine* eng = new GameEngine(maps_to_be_played, computers, rounds_per_game, draw);
		eng->startTournament();
		//display winners

		for (int i = 0; i < eng->getWinnerCount(); i++) {
			cout << "Displaying the winners: \nGame" + to_string(i) + ": ";
			cout << eng->getWinners()[i] << endl;
			cout << "\n";
		}
	}
	else {
		cout << "Goodbye\n";
	}
}