#include "Tile.h"
#include "../TileMap.h"
#include <iostream>

Tile::Tile(const int x, const int y, const TileTypes::ID type)
{
	m_tile_type = type;
	m_tile_position = sf::Vector2i(x, y);
	m_has_destroyed_animation = false;

	m_destroyed = false;
	m_has_powerup = false;
	
	if (type == TileTypes::ID::BRICK)
		m_destructable = false;
	else
		m_destructable = true;

	m_sprite.setSize({ TILE_SIZE_X, TILE_SIZE_Y });
	m_sprite.setPosition(x * TILE_SIZE_X, y * TILE_SIZE_Y);

	getTextureByID();
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	if (m_destroyed)
	{
		Tile tile(getTilePosition().x, getTilePosition().y, TileTypes::ID::AIR);
		tile.draw(target, states);
	}

	target.draw(m_sprite, states);
}

void Tile::setType(const TileTypes::ID type)
{
	m_tile_type = type;
}

void Tile::setHasPowerup(const bool has_powerup, const PowerupTypes::ID type)
{
	m_has_powerup = has_powerup;
}

void Tile::destroy()
{
	if (m_destructable)
	{
		if (m_has_destroyed_animation && !m_destroyed)
		{
			TileMap::pushDestroyQueue((sf::Vector2f)getTilePosition());
		}

		m_destroyed = true;
	}
}

void Tile::update()
{
	Collidable::updateRect(m_sprite.getGlobalBounds());

	updateAnimation();
}

void Tile::updateAnimation()
{
	if (m_destroyed)
	{
		if (m_tile_type == TileTypes::ID::BRICK)
		{
			if (m_animation_clock.getElapsedTime().asSeconds() > 0.05 && 
				m_animation.currentFrame() != m_animation.frames() - 1)
			{
				m_animation.nextFrame();
				
				m_animation.apply(m_sprite);

				m_animation_clock.restart();
			}
		}
	}
}

void Tile::getTextureByID()
{
	m_animation.setTexturePtr(TextureHandler::get("items"));

	switch (m_tile_type)
	{
	case TileTypes::ID::AIR:
		m_animation.addFrame(sf::IntRect(16 * 6, 16 * 2, 16, 16));
		m_destructable = false;
		break;
	case TileTypes::ID::BRICK:
		m_animation.addFrame(sf::IntRect(16 * 1, 16 * 1, 16, 16));

		for (int i = 0; i < 6; i++)
		{
			m_animation.addFrame(sf::IntRect(16 * i, 16 * 2, 16, 16));
		}

		m_has_destroyed_animation = true;

		m_destructable = true;
		break;
	case TileTypes::ID::DOOR:
		m_animation.addFrame(sf::IntRect(16 * 2, 16 * 1, 16, 16));
		m_destructable = false;
		break;
	case TileTypes::ID::POWERUP:
		m_animation.addFrame(sf::IntRect(16 * 1, 16 * 1, 16, 16));
		m_destructable = true;
		m_has_powerup = true;
		break;
	case TileTypes::ID::TILE:
		m_animation.addFrame(sf::IntRect(16 * 0, 16 * 1, 16, 16));
		m_destructable = false;
		break;
	}

	m_animation.apply(m_sprite);
}
