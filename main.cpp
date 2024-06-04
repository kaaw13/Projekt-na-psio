#include "Game.h"
#include <time.h>
#include <cstdlib> 

int main()
{
	// INITIALIZATION
	srand(time(NULL));

	Game game;
	/////////////////////////////////
	game.run();

	// End of application
	return 0;
}