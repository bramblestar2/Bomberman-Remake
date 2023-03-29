#pragma once
#include <iostream>
#include "Game.h"

Game* Game::m_instance;

Game::Game() : m_map(31, 13), m_player(1, 1), m_enemy(1, 1)
{
	m_window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman NES", sf::Style::Close | sf::Style::Titlebar);
	//m_window->setMouseCursorVisible(false);
	
	m_player_follower.follow(&m_player.getPosition());
	m_player_follower.setSize((sf::Vector2f)m_window->getSize());
	m_player_follower.setLimits(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(TileMap::getSize().x * TILE_SIZE_X, TileMap::getSize().y * TILE_SIZE_Y - 4)));

	m_event = sf::Event();
	m_dt = 0;

	//MapGenerator::noBrickGeneration();
	MapGenerator::randomBrickGeneration(3);
}

Game::~Game()
{
	delete m_window;
}

void Game::run()
{
	while (m_window->isOpen())
	{
		updateDT();
		update();
		updateEvents();
		render();
	}
}

void Game::update()
{
	if (m_window->hasFocus())
	{
		if (m_dt > 5)
			m_dt = 0.01;

		m_player_follower.update();

		m_player.update(m_dt);

		sf::Vector2f offset = m_map.collision(m_player);
		m_player.move(offset);

		m_enemy.update(m_dt);

		for (const auto bomb : m_player.getBombs())
		{
			m_enemy.bombCollision(bomb);
		}

		TileMap::updateDestroyQueue();
	}
}

void Game::updateEvents()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::Space)
			{
				MapGenerator::randomBrickGeneration(3);
			}
		}

		m_player.updateEvents(m_event);
		m_enemy.updateEvents(m_event);
	}
}

void Game::updateDT()
{
	m_dt = m_dt_clock.restart().asSeconds();
}

void Game::render()
{
	m_window->clear();
	m_window->setView(m_player_follower);
	sf::RenderStates states;

	m_map.draw(*m_window, states);

	m_player.draw(*m_window, states);
	m_enemy.draw(*m_window, states);

	m_window->display();
}
