#include "Game.h"


#include <ctime>
#include <cstdlib>


int main(int argc, char* argv[])
{
	srand(time(NULL));

	Game game;
	game.Init();
	while (game.running)
	{
		game.HandleEvents();
		game.Update();
		game.Render();
	}
	game.Quit();

	return 0;
}