#pragma once
#include "Game.h"

Game* Game::m_instance;

Game::Game()
{
	m_window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman NES", sf::Style::Close | sf::Style::Titlebar);

	temp.setSize({ 100,100 });

	m_player_follower.follow(&temp.getPosition());
	m_player_follower.setLimits(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(1000,1500)));

	m_event = sf::Event();
	m_dt = 0;
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

	temp.move({ 0, 200*m_dt});
}

void Game::updateEvents()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
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

	m_window->display();
}
