#include "Tile.h"

Tile::Tile(const int x, const int y, const TileTypes::ID type)
{
	m_tile_type = type;
	m_tile_position = sf::Vector2i(x, y);

	m_destroyed = false;
	
	if (type == TileTypes::ID::BRICK)
		m_destructable = false;
	else
		m_destructable = true;
}

void Tile::setHasPowerup(const bool has_powerup, const PowerupTypes::ID type)
{
	m_has_powerup = has_powerup;
}

void Tile::destroy()
{
	if (!m_destructable)
		m_destroyed = false;
}
