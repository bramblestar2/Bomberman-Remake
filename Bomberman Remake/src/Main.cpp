#include <iostream>
#include "Game Window/Game.h"

int main()
{
	Game::get()->run();
	Game::get()->freeResources();

	return 0;
}