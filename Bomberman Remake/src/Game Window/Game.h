#pragma once
#include <SFML/Graphics.hpp>
#include "../Components/CustomView/ViewFollower.h"
#include "../Components/Collidable/Collidable.h"

class TestTile : public Collidable, public sf::RectangleShape
{
public:
	void update()
	{
		updateRect(this->getGlobalBounds());
	}
};


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
	sf::RenderWindow* m_window;
	sf::Event m_event;

	sf::Clock m_dt_clock;
	float m_dt;

	ViewFollower m_player_follower;

	TestTile test1, test2, test3, test4;
	sf::Vector2f test_velocity;

	sf::RectangleShape temp;

	void update();
	void updateEvents();
	void updateDT();
	void render();
};