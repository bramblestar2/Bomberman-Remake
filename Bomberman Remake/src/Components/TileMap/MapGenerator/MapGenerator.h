#pragma once
#include "../TileMap.h"

class MapGenerator
{
public:
	static void noBrickGeneration();
	static void randomBrickGeneration(int probability);
};