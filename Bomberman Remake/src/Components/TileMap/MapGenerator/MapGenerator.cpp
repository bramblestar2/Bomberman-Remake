#include "MapGenerator.h"
#include <iostream>
#include <time.h>

void MapGenerator::noBrickGeneration()
{
	Tile*** tilemap = TileMap::getMap();

	if (tilemap != nullptr)
		for (int x = 0; x < TileMap::getSize().x; x++)
			if (tilemap[x] != nullptr)
				for (int y = 0; y < TileMap::getSize().y; y++)
					if (tilemap[x][y] != nullptr)
					{
						if (x == 0 || y == 0 || 
							x == TileMap::getSize().x - 1 ||
							y == TileMap::getSize().y - 1)
						{
							delete tilemap[x][y];
							tilemap[x][y] = new Tile(x, y, TileTypes::ID::TILE);
						}
						else if (x > 1 && y > 1 && 
							x < TileMap::getSize().x-1 && 
							y < TileMap::getSize().y-1)
						{
							if (x % 2 == 0 && y % 2 == 0)
							{
								delete tilemap[x][y];
								tilemap[x][y] = new Tile(x, y, TileTypes::ID::TILE);
							}
							else
							{
								delete tilemap[x][y];
								tilemap[x][y] = new Tile(x, y, TileTypes::ID::AIR);
							}
						}
					}
}

void MapGenerator::randomBrickGeneration(int probability)
{
	Tile*** tilemap = TileMap::getMap();
	srand(time(NULL));

	if (tilemap != nullptr)
		for (int x = 0; x < TileMap::getSize().x; x++)
			if (tilemap[x] != nullptr)
				for (int y = 0; y < TileMap::getSize().y; y++)
					if (tilemap[x][y] != nullptr)
					{
						if (x == 0 || y == 0 ||
							x == TileMap::getSize().x - 1 ||
							y == TileMap::getSize().y - 1)
						{
							delete tilemap[x][y];
							tilemap[x][y] = new Tile(x, y, TileTypes::ID::TILE);
						}
						else if (x > 0 && y > 0 &&
							x < TileMap::getSize().x - 1 &&
							y < TileMap::getSize().y - 1)
						{
							if (rand() % probability == 0)
							{
								if (x % 2 == 0 || y % 2 == 0)
								{
									delete tilemap[x][y];
									tilemap[x][y] = new Tile(x, y, TileTypes::ID::BRICK);
								}
							}
							else
							{
								delete tilemap[x][y];
								tilemap[x][y] = new Tile(x, y, TileTypes::ID::AIR);
							}

							if (x % 2 == 0 && y % 2 == 0)
							{
								delete tilemap[x][y];
								tilemap[x][y] = new Tile(x, y, TileTypes::ID::TILE);
							}
						}
					}
}

void MapGenerator::loadFromFile(const std::string file_path)
{
}
