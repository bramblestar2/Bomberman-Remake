#pragma once
#include "Tile/Tile.h"

class TileMap
{
public:
	TileMap(const int width, const int height);
	~TileMap();

	sf::Vector2f collision(Collidable& collidable);

	void draw(sf::RenderTarget& target, sf::RenderStates& states);

	static void setTile(const int x, const int y, TileTypes::ID type);

	static Tile* getTile(const int x, const int y);
	static Tile*** getMap();
	static const sf::Vector2i& getSize();
private:
	static sf::Vector2i m_map_size;
	static Tile*** m_tile_map;
};