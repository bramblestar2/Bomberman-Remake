#pragma once
#include "../TileMap.h"

class MapGenerator
{
public:
	static void noBrickGeneration();
	static void randomBrickGeneration(int probability);

	static void loadFromFile(const std::string file_path);
};