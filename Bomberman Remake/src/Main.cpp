#include <iostream>
#include "Game Window/Game.h"

int main()
{
	TextureHandler::load("enemies", "src/Textures/bomberman_enemies.png");
	TextureHandler::load("explosion", "src/Textures/bomberman_explosion.png");
	TextureHandler::load("items", "src/Textures/bomberman_items.png");
	TextureHandler::load("player", "src/Textures/bomberman_player.png");

	Game::get()->run();

	Game::get()->freeResources();

	TextureHandler::clear();

	return 0;
}