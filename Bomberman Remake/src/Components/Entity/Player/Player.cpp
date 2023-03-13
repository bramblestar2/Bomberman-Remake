#include "Player.h"
#include <iostream>

Player::Player(int x, int y) : Entity(x, y)
{
	Entity::m_sprite.setSize({ ENTITY_SIZE_X, ENTITY_SIZE_Y });

	m_up_walk.setTexturePtr(TextureHandler::get("player"));
	m_right_walk.setTexturePtr(TextureHandler::get("player"));
	m_down_walk.setTexturePtr(TextureHandler::get("player"));
	m_left_walk.setTexturePtr(TextureHandler::get("player"));

	for (int i = 0; i < 3; i++)
	{
		m_left_walk.addFrame(sf::IntRect(12 * i, 16 * 0, 12, 16));
		m_right_walk.addFrame(sf::IntRect(12 * i, 16 * 1, 12, 16));
		m_down_walk.addFrame(sf::IntRect(12 * i, 16 * 2, 12, 16));
		m_up_walk.addFrame(sf::IntRect(12 * i, 16 * 3, 12, 16));
	}

	m_down_walk.apply(Entity::m_sprite);

	Entity::setSpeed(200);

	m_left_key = sf::Keyboard::Left;
	m_right_key = sf::Keyboard::Right;
	m_up_key = sf::Keyboard::Up;
	m_down_key = sf::Keyboard::Down;
}

void Player::move(const sf::Vector2f& velocity)
{
	Entity::m_sprite.move(velocity);
	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());
}

void Player::update(const double dt)
{
	if (sf::Keyboard::isKeyPressed(m_left_key))
		Entity::setVelocity(sf::Vector2f(-Entity::getSpeed() * dt, 0));
	else if (sf::Keyboard::isKeyPressed(m_right_key))
		Entity::setVelocity(sf::Vector2f(Entity::getSpeed() * dt, 0));
	else if (sf::Keyboard::isKeyPressed(m_up_key))
		Entity::setVelocity(sf::Vector2f(0, -Entity::getSpeed() * dt));
	else if (sf::Keyboard::isKeyPressed(m_down_key))
		Entity::setVelocity(sf::Vector2f(0, Entity::getSpeed() * dt));
	else
		Entity::setVelocity(sf::Vector2f(0, 0));

	Entity::m_sprite.move(Entity::getVelocity());

	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());

	updateAnimation();
}

void Player::updateEvents(sf::Event& event)
{
}

void Player::updateAnimation()
{
	if (Entity::getVelocity().x != 0 || Entity::getVelocity().y != 0)
	{
		if (m_animation_clock.getElapsedTime().asSeconds() > 0.2)
		{
			m_left_walk.nextFrame();
			m_right_walk.nextFrame();
			m_up_walk.nextFrame();
			m_down_walk.nextFrame();

			m_animation_clock.restart();
		}

		if (Entity::getVelocity().x < 0)
			m_left_walk.apply(Entity::m_sprite);
		else if (Entity::getVelocity().x > 0)
			m_right_walk.apply(Entity::m_sprite);
		else if (Entity::getVelocity().y < 0)
			m_up_walk.apply(Entity::m_sprite);
		else
			m_down_walk.apply(Entity::m_sprite);
	}
}
