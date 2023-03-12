#pragma once
#include <iostream>
#include "Game.h"

Game* Game::m_instance;

Game::Game()
{
	m_window = new sf::RenderWindow(sf::VideoMode(750, 750), "Bomberman NES", sf::Style::Close | sf::Style::Titlebar);

	m_player_follower.setLimits(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(1000,1500)));

	m_event = sf::Event();
	m_dt = 0;

	test1.setSize({ 100,100 });
	test1.setFillColor(sf::Color::Red);
	test1.setPosition(200, 300);
	test2.setSize({ 100,100 });
	test2.setPosition(400, 400);
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

	auto lerp = [](float a, float b, float t) -> float
	{
		return a + t * (b - a);
	};

	float speed = 100;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && test_velocity.x > -speed)
		test_velocity += {-speed * m_dt, 0};
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && test_velocity.x < speed)
		test_velocity += {speed * m_dt, 0};
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//test_velocity.x = lerp(test_velocity.x, 0, 0.5f);
		test_velocity.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && test_velocity.y > -speed)
		test_velocity += {0, -speed * m_dt};
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && test_velocity.y < speed)
		test_velocity += {0, speed* m_dt};
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//test_velocity.y = lerp(test_velocity.y, 0, 0.5f);
		test_velocity.y = 0;
	}

	test1.update();
	test2.update();

	//std::cout <<  << std::endl;
	sf::Vector2f correction;
	test1.check(test2, correction, test_velocity);
	//std::cout << test_velocity.x << " - " << test_velocity.y << "\n";

	test1.move(test_velocity.x * m_dt, test_velocity.y * m_dt);
	test1.move(correction.x, correction.y);
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

	m_window->draw(test2);
	m_window->draw(test1);

	m_window->display();
}
