#include "Player.h"
#include <iostream>

Player::Player(int x, int y) : Entity(x, y)
{
	m_bomb_range = 2;
	m_max_bombs = 5;
	m_has_detonator = true;
	m_dead = false;

	m_pass_through = false;

	Entity::m_sprite.setSize({ ENTITY_SIZE_X, ENTITY_SIZE_Y });

	m_death_animation.setTexturePtr(TextureHandler::get("player"));
	m_up_walk.setTexturePtr(TextureHandler::get("player"));
	m_right_walk.setTexturePtr(TextureHandler::get("player"));
	m_down_walk.setTexturePtr(TextureHandler::get("player"));
	m_left_walk.setTexturePtr(TextureHandler::get("player"));

	for (int i = 0; i < 3; i++)
	{
		m_left_walk.addFrame(sf::IntRect(16 * i, 16 * 0, 16, 16));
		m_right_walk.addFrame(sf::IntRect(16 * i, 16 * 1, 16, 16));
		m_down_walk.addFrame(sf::IntRect(16 * i, 16 * 2, 16, 16));
		m_up_walk.addFrame(sf::IntRect(16 * i, 16 * 3, 16, 16));
	}

	for (int i = 0; i < 8; i++)
		m_death_animation.addFrame(sf::IntRect(16 * i, 16 * 4, 16, 16));

	m_down_walk.apply(Entity::m_sprite);

	Entity::setSpeed(200);

	m_left_key = sf::Keyboard::Left;
	m_right_key = sf::Keyboard::Right;
	m_up_key = sf::Keyboard::Up;
	m_down_key = sf::Keyboard::Down;
}

Player::~Player()
{
	for (auto bomb : m_bomb_list)
	{
		delete bomb;
	}
}

void Player::update(const double dt)
{
	if (!m_dead)
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
	}

	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());

	updateAnimation();

	for (int i = 0; i < m_bomb_list.size(); i++)
	{
		m_bomb_list.at(i)->update(dt);

		sf::Vector2f offset;
		offset = m_bomb_list.at(i)->collision(*this);
		this->move(offset);

		if (m_bomb_list.at(i)->hasExplosionFinished())
		{
			delete m_bomb_list.at(i);
			m_bomb_list.erase(m_bomb_list.begin() + i);
		}
		else if (m_bomb_list.at(i)->hasExploded())
		{
			std::vector<sf::Vector2f> exploded_tiles = m_bomb_list.at(i)->getEffectedTiles(false);
			for (int i = 0; i < exploded_tiles.size(); i++)
			{
				if (Entity::getTilePosition() == exploded_tiles.at(i))
				{
					setDeathState(true);
				}
			}
		}
	}
}

void Player::updateEvents(sf::Event& event)
{
	if (!m_dead)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				if (m_bomb_list.size() < m_max_bombs)
				{
					bool bomb_already_exists = false;

					for (int i = 0; i < m_bomb_list.size() && !bomb_already_exists; i++)
					{
						if (m_bomb_list.at(i)->getTilePosition() == Entity::getTilePosition())
						{
							bomb_already_exists = true;
						}
					}

					if (!bomb_already_exists)
						m_bomb_list.push_back(new Bomb(Entity::getTilePosition().x, Entity::getTilePosition().y, m_bomb_range, !m_has_detonator));
				}
				break;
			case sf::Keyboard::B:
				if (m_has_detonator)
				{
					if (m_bomb_list.size() > 0)
					{
						int explode_iterator = 0;

						do
						{
							if (m_bomb_list.at(explode_iterator)->hasExploded() && explode_iterator < m_bomb_list.size() - 1)
								explode_iterator++;
							else if (!m_bomb_list.at(explode_iterator)->hasExploded())
								m_bomb_list.at(explode_iterator)->explode();
						} while (!m_bomb_list.at(explode_iterator)->hasExploded());

					}
				}
				break;
			}
		}
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	for (int i = m_bomb_list.size()-1; i >= 0; i--)
	{
		m_bomb_list.at(i)->draw(target, states);
	}

	target.draw(Entity::m_sprite, states);
}

void Player::updateAnimation()
{
	if (!m_dead)
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
	else
	{
		if (m_animation_clock.getElapsedTime().asSeconds() > 0.15 && 
			m_death_animation.currentFrame() != m_death_animation.frames()-1)
		{
			m_death_animation.nextFrame();

			m_animation_clock.restart();
		}

		m_death_animation.apply(Entity::m_sprite);
	}
}
