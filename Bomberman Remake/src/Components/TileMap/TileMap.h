#pragma once
#include "Tile/Tile.h"

/* Manages all of the tiles */
/* The static methods can be called with TileMap::(METHOD_NAME) */
class TileMap
{
public:
	/* Provide the width and height of the map */
	TileMap(const int width, const int height);
	/* Free up and allocated resources */
	~TileMap();

	/* Checks collision between a collidable and all of the tilemaps */
	/* in m_tile_map */
	sf::Vector2f collision(Collidable& collidable);

	/* Draws the entire tilemap to a */
	/* specified target (Such as a RenderWindow or RenderTexture */
	void draw(sf::RenderTarget& target, sf::RenderStates& states);
	/* Goes through the destroy queue and checks if a tile */
	/* Needs to be deleted */
	static void updateDestroyQueue();
	/* Adds a queue for a tile to be destroyed */
	/* Was made in case a tile has a animation that needs to be played */
	static void pushDestroyQueue(const sf::Vector2f& destroyed);

	/* Sets a tile to a specified ID */
	static void setTile(const int x, const int y, TileTypes::ID type);

	static Tile* getTile(const int x, const int y);
	/* Returns the multidimensional array pointer of tiles */
	static Tile*** getMap();
	/* Gets the size of the tilemap */
	static const sf::Vector2i& getSize();
private:
	/* Deallocates m_tile_map */
	void freeResources();

	//To be destroyed
	static std::vector<sf::Vector2f> m_destroy_queue;
	/* The size of the map */
	static sf::Vector2i m_map_size;
	/* A multidimensional array pointer of tiles*/
	static Tile*** m_tile_map;
};