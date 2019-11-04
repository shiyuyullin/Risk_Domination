#include "GameEngine.h"

int main() {
  //The creation of the game engine obj
	GameEngine* eng = new GameEngine();
  //1.) Johanson's part here:
  
  
  //2.) Ian's part here:
	eng->map_assign_startUp();// call this first
	eng->placeArmies_startUpPhase();//then this one
  
  
  //etc modify as you please
  // Part 3 & 4 Test
  eng->testPart3AND4();

	delete eng;
}
