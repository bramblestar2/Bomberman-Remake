#include "TileMap.h"
#include <math.h>
#include <iostream>

Tile*** TileMap::m_tile_map;
sf::Vector2i TileMap::m_map_size;

TileMap::TileMap(const int width, const int height)
{
	m_map_size.x = width;
	m_map_size.y = height;

	m_tile_map = new Tile * *[width];
	for (int x = 0; x < width; x++)
	{
		m_tile_map[x] = new Tile * [height];
		for (int y = 0; y < height; y++)
		{
			m_tile_map[x][y] = new Tile(x, y, TileTypes::ID::AIR);
		}
	}
}

TileMap::~TileMap()
{
	if (m_tile_map != nullptr)
	{
		for (int x = 0; x < m_map_size.x; x++)
		{
			if (m_tile_map[x] != nullptr)
			{
				for (int y = 0; y < m_map_size.y; y++)
				{
					if (m_tile_map[x][y] != nullptr)
					{
						delete m_tile_map[x][y];
					}
				}

				delete[] m_tile_map[x];
			}
		}
		delete[] m_tile_map;
	}
}

sf::Vector2f TileMap::collision(Collidable& collidable)
{
	sf::Vector2f correction;
	bool stop_checking = false;

	if (m_tile_map != nullptr)
	{
		for (int x = 0; x < m_map_size.x && !stop_checking; x++)
		{
			if (m_tile_map[x] != nullptr)
			{
				for (int y = 0; y < m_map_size.y && !stop_checking; y++)
				{
					if (m_tile_map[x][y] != nullptr)
					{
						if (m_tile_map[x][y]->getType() != TileTypes::ID::AIR)
						{
							m_tile_map[x][y]->update();

							sf::Vector2f center_tile = { 
								m_tile_map[x][y]->getBounds().left + (m_tile_map[x][y]->getBounds().width / 2),
								m_tile_map[x][y]->getBounds().top + (m_tile_map[x][y]->getBounds().height / 2)
							};
							sf::Vector2f center_other = 
							{
								collidable.getBounds().left + (collidable.getBounds().width / 2),
								collidable.getBounds().top + (collidable.getBounds().height / 2)
							};

							float distance = sqrt(pow(center_other.x - center_tile.x, 2) + 
												  pow(center_other.y - center_tile.y, 2));

							if (distance < TILE_SIZE_X * 2)
							{

								if (collidable.check(*m_tile_map[x][y], correction, sf::Vector2f()))
								{
									//std::cout << correction.x << " - " << correction.y << std::endl;

									//if (correction.x != 0 || correction.y != 0)
									//	return correction;
								}
							}
						}
					}
				}
			}
		}
	}

	return correction;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	if (m_tile_map != nullptr)
	{
		for (int x = 0; x < m_map_size.x; x++)
		{
			if (m_tile_map[x] != nullptr)
			{
				for (int y = 0; y < m_map_size.y; y++)
				{
					if (m_tile_map[x][y] != nullptr)
					{
						m_tile_map[x][y]->draw(target, states);
					}
				}
			}
		}
	}
}

void TileMap::setTile(const int x, const int y, TileTypes::ID type)
{
	if (x >= 0 && x < m_map_size.x && y >= 0 && y < m_map_size.y)
	{
		if (m_tile_map[x][y] != nullptr)
		{
			*m_tile_map[x][y] = Tile(x, y, type);
		}
	}
}

Tile* TileMap::getTile(const int x, const int y)
{
	if (x >= 0 && x < m_map_size.x && y >= 0 && y < m_map_size.y)
	{
		if (m_tile_map[x][y] != nullptr)
			return m_tile_map[x][y];
	}

	return nullptr;
}

Tile*** TileMap::getMap()
{
	return m_tile_map;
}

const sf::Vector2i& TileMap::getSize()
{
	return m_map_size;
}
