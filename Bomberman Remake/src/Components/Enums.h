#pragma once

namespace TileTypes
{
	enum ID
	{
		AIR = 0,
		BRICK,
		TILE,
		DOOR,
		POWERUP,
	};
}

namespace PowerupTypes
{
	enum ID
	{
		BOMB_UP = 0,
		FLAME_UP,
		SPEED_UP,
		WALL_PASS,
		DETONATOR,
		BOMB_PASS, 
		FLAME_PASS, 
		INVINCIBILITY
	};
}

namespace Directions
{
	enum Heading
	{
		NORTH = 0,
		EAST,
		SOUTH,
		WEST,
	};
}