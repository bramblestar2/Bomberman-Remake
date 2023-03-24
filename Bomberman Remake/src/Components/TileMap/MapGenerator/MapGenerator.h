#pragma once
#include "../TileMap.h"

/* Generates a map for the TileMap */
class MapGenerator
{
public:
	/* Generates a plain map */
	static void noBrickGeneration();
	/* Randomizes the bricks placed within the map */
	static void randomBrickGeneration(int probability);

	/* Not worked on yet */
	/* Will include powerups and doors and bricks */
	static void randomGenerator(int probability);

	/* Not worked on yet */
	/* Loads the tiles from a file into the tilemap */
	static void loadFromFile(const std::string file_path);
};