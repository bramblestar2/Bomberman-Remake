#pragma once
#include <SFML/Graphics.hpp>
#include "../Components/CustomView/ViewFollower.h"
#include "../Components/TileMap/MapGenerator/MapGenerator.h"
#include "../Components/Entity/Player/Player.h"
#include "../Components/Entity/Bomb/Bomb.h"

#include "../Components/Entity/Enemy/ONeal/ONeal.h"

/* This class is a Singleton class so there is only one instance of it */
/* Handles all of the elements for the game, such as the level, tiles, entities, etc */
class Game
{
private:
	Game();
	~Game();

	static Game* m_instance;

public:
	static Game* get()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Game();
			return m_instance;
		}
		else
			return m_instance;
	}

	static void freeResources()
	{
		delete m_instance;
	};

	void run();

	Game(const Game& obj) = delete;
private:
	Player* m_player;
	ONeal m_enemy;

	TileMap m_map;

	sf::RenderWindow* m_window;
	sf::Event m_event;

	sf::Clock m_dt_clock;
	float m_dt;

	ViewFollower m_player_follower;

	sf::RectangleShape temp;

	void update();
	void updateEvents();
	void updateDT();
	void render();
};