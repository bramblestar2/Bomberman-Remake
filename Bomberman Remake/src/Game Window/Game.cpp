#pragma once
#include <iostream>
#include "Game.h"

Game* Game::m_instance;

Game::Game() : m_map(31, 13), m_player(1, 1)
{
	m_window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman NES", sf::Style::Close | sf::Style::Titlebar);
	
	m_player_follower.follow(&m_player.getPosition());
	m_player_follower.setSize((sf::Vector2f)m_window->getSize());
	m_player_follower.setLimits(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(TileMap::getSize().x * TILE_SIZE_X, TileMap::getSize().y * TILE_SIZE_Y)));

	m_event = sf::Event();
	m_dt = 0;

	//MapGenerator::noBrickGeneration();
	MapGenerator::randomBrickGeneration(5);
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
	m_player_follower.update();

	if (m_bomb != nullptr)
	{
		m_bomb->update(m_dt);
	}
	m_player.update(m_dt);
	
	sf::Vector2f offset = m_map.collision(m_player);
	m_player.move(offset);

	if (m_bomb != nullptr)
	{
		offset = m_bomb->collision(m_player);
		m_player.move(offset);
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
				MapGenerator::randomBrickGeneration(5);
			}
			else if (m_event.key.code == sf::Keyboard::A)
			{
				if (m_bomb != nullptr)
					delete m_bomb;
				m_bomb = new Bomb(m_player.getTilePosition().x, m_player.getTilePosition().y, 4);
			}
			else if (m_event.key.code == sf::Keyboard::B)
			{
				std::vector<sf::Vector2f> explos_pos = m_bomb->getEffectedTiles();

				for (int i = 0; i < explos_pos.size(); i++)
				{
					TileTypes::ID type = TileMap::getTile(explos_pos.at(i).x, explos_pos.at(i).y)->getType();
					if (type != TileTypes::ID::TILE && type != TileTypes::ID::AIR)
					{
						TileMap::setTile(explos_pos.at(i).x, explos_pos.at(i).y, TileTypes::ID::AIR);
					}
				}
			}
		}
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

	if (m_bomb != nullptr)
		m_bomb->draw(*m_window, states);

	m_window->display();
}
