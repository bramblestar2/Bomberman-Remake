#include "Bomb.h"
#include "../../TileMap/TileMap.h"
#include <iostream>

Bomb::Bomb(const int x, const int y, const int radius, 
			const bool has_timer) : Entity(x, y)
{
	Entity::m_sprite.setSize({ ENTITY_SIZE_X, ENTITY_SIZE_Y });

	m_player_on_bomb = true;

	m_has_exploded = false;
	m_explosion_ended = false;
	m_has_timer = has_timer;
	m_explosion_radius = radius;

	/* Setup Animation */
	m_bomb_animation.setTexturePtr(TextureHandler::get("items"));
	for (int i = 0; i < 3; i++)
		m_bomb_animation.addFrame(sf::IntRect(16 * i, 16 * 0, 16, 16));

	m_center_explosion.setTexturePtr(TextureHandler::get("explosion"));
	m_up_explosion.setTexturePtr(TextureHandler::get("explosion"));
	m_right_explosion.setTexturePtr(TextureHandler::get("explosion"));
	m_down_explosion.setTexturePtr(TextureHandler::get("explosion"));
	m_left_explosion.setTexturePtr(TextureHandler::get("explosion"));
	m_vertical_explosion.setTexturePtr(TextureHandler::get("explosion"));
	m_horizontal_explosion.setTexturePtr(TextureHandler::get("explosion"));

	for (int i = 0; i < 4; i++)
	{
		m_center_explosion.addFrame(sf::IntRect(16 * i, 16 * 0, 16, 16));
		m_up_explosion.addFrame(sf::IntRect(16 * i, 16 * 1, 16, 16));
		m_right_explosion.addFrame(sf::IntRect(16 * i, 16 * 2, 16, 16));
		m_down_explosion.addFrame(sf::IntRect(16 * i, 16 * 3, 16, 16));
		m_left_explosion.addFrame(sf::IntRect(16 * i, 16 * 4, 16, 16));
		m_vertical_explosion.addFrame(sf::IntRect(16 * i, 16 * 5, 16, 16));
		m_horizontal_explosion.addFrame(sf::IntRect(16 * i, 16 * 6, 16, 16));
	}

	m_bomb_animation.apply(Entity::m_sprite);
}

void Bomb::explode()
{
	m_has_exploded = true;

	std::vector<sf::Vector2f> explos_pos = getEffectedTiles();

	for (int i = 0; i < explos_pos.size(); i++)
	{
		TileTypes::ID type = TileMap::getTile(explos_pos.at(i).x, explos_pos.at(i).y)->getType();
		if (type != TileTypes::ID::TILE && type != TileTypes::ID::AIR)
		{
			TileMap::setTile(explos_pos.at(i).x, explos_pos.at(i).y, TileTypes::ID::AIR);
		}
	}
}

void Bomb::update(const double dt)
{
	if (!m_has_exploded)
	{
		updateBombAnimation();

		if (m_detonation_clock.getElapsedTime().asSeconds() > 3 && m_has_timer)
		{
			explode();
		}
	}
	else
	{
		updateExplosionAnimation();
	}

	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());
}

void Bomb::updateEvents(sf::Event& event)
{
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	if (!m_explosion_ended)
	{
		target.draw(Entity::m_sprite);

		if (m_has_exploded)
		{

		}
	}
}

sf::Vector2f Bomb::collision(Collidable& collider)
{
	if (m_player_on_bomb)
	{
		if (!Collidable::check(collider))
		{
			m_player_on_bomb = false;
		}
		
		return sf::Vector2f();
	}
	else
	{
		sf::Vector2f offset;
		collider.check(*this, offset, sf::Vector2f());
		return offset;
	}
}

std::vector<sf::Vector2f> Bomb::getEffectedTiles()
{
	std::vector<sf::Vector2f> explosion_positions;
	sf::Vector2f bomb_pos = Entity::getTilePosition();
	explosion_positions.push_back(bomb_pos);

	bool stop_up = false, stop_right = false, stop_down = false, stop_left = false;

	for (int i = 0; i < m_explosion_radius; i++)
	{
		if (bomb_pos.x + (i + 1) < TileMap::getSize().x && !stop_right)
		{
			if (TileMap::getTile(bomb_pos.x + (i + 1), bomb_pos.y)->getType() == TileTypes::ID::AIR)
			{
				explosion_positions.push_back(sf::Vector2f(bomb_pos.x + (i + 1), bomb_pos.y));
				m_exploded_radius[1]++;
			}
			else
			{
				stop_right = true;

				if (TileMap::getTile(bomb_pos.x + (i + 1), bomb_pos.y)->isDestructable())
				{
					explosion_positions.push_back(sf::Vector2f(bomb_pos.x + (i + 1), bomb_pos.y));
					m_exploded_radius[1]++;
				}
			}
		}
		if (bomb_pos.x - (i + 1) >= 0 && !stop_left)
		{
			if (TileMap::getTile(bomb_pos.x - (i + 1), bomb_pos.y)->getType() == TileTypes::ID::AIR)
			{
				explosion_positions.push_back(sf::Vector2f(bomb_pos.x - (i + 1), bomb_pos.y));
				m_exploded_radius[3]++;
			}
			else
			{
				stop_left = true;

				if (TileMap::getTile(bomb_pos.x - (i + 1), bomb_pos.y)->isDestructable())
				{
					explosion_positions.push_back(sf::Vector2f(bomb_pos.x - (i + 1), bomb_pos.y));
					m_exploded_radius[3]++;
				}
			}
		}
		if (bomb_pos.y + (i + 1) < TileMap::getSize().y && !stop_down)
		{
			if (TileMap::getTile(bomb_pos.x, bomb_pos.y + (i + 1))->getType() == TileTypes::ID::AIR)
			{
				explosion_positions.push_back(sf::Vector2f(bomb_pos.x, bomb_pos.y + (i + 1)));
				m_exploded_radius[2]++;
			}
			else
			{
				stop_down = true;

				if (TileMap::getTile(bomb_pos.x, bomb_pos.y + (i + 1))->isDestructable())
				{
					explosion_positions.push_back(sf::Vector2f(bomb_pos.x, bomb_pos.y + (i + 1)));
					m_exploded_radius[2]++;
				}
			}
		}
		if (bomb_pos.y - (i + 1) >= 0 && !stop_up)
		{
			if (TileMap::getTile(bomb_pos.x, bomb_pos.y - (i + 1))->getType() == TileTypes::ID::AIR)
			{
				explosion_positions.push_back(sf::Vector2f(bomb_pos.x, bomb_pos.y - (i + 1)));
				m_exploded_radius[0]++;
			}
			else
			{
				stop_up = true;

				if (TileMap::getTile(bomb_pos.x, bomb_pos.y - (i + 1))->isDestructable())
				{
					explosion_positions.push_back(sf::Vector2f(bomb_pos.x, bomb_pos.y - (i + 1)));
					m_exploded_radius[0]++;
				}
			}
		}
	}

	system("cls");
	for (int i = 0; i < 4; i++)
	{
		std::cout << m_exploded_radius[i] << ", ";
	}
	std::cout << "\n";

	for (int i = 0; i < explosion_positions.size(); i++)
	{
		std::cout << explosion_positions.at(i).x << " - " << explosion_positions.at(i).y << "\n";
	}

	return explosion_positions;
}

void Bomb::updateBombAnimation()
{
	if (m_bomb_clock.getElapsedTime().asSeconds() > 0.1)
	{
		m_bomb_animation.nextFrame();

		m_bomb_animation.apply(Entity::m_sprite);

		m_bomb_clock.restart();
	}
}

void Bomb::updateExplosionAnimation()
{
	if (m_bomb_clock.getElapsedTime().asSeconds() > 0.1 && 
		m_center_explosion.currentFrame() != m_center_explosion.frames()-1)
	{
		m_center_explosion.nextFrame();
		m_up_explosion.nextFrame();
		m_right_explosion.nextFrame();
		m_down_explosion.nextFrame();
		m_left_explosion.nextFrame();
		m_vertical_explosion.nextFrame();
		m_horizontal_explosion.nextFrame();

		m_center_explosion.apply(Entity::m_sprite);

		m_bomb_clock.restart();
	}
	else
	{
		if (m_bomb_clock.getElapsedTime().asSeconds() > 0.1)
			m_explosion_ended = true;
	}
}
