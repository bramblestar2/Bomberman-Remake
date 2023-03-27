#include "Enemy.h"
#include "../../TileMap/TileMap.h"

Enemy::Enemy(int x, int y) : Entity(x, y)
{
	m_heading_direction = Directions::EAST;

	m_entered_tile = true;

	m_previous_tile = { x, y };
}

void Enemy::update(const double dt)
{
	//If enemy has entered new tile, set to true
	if (!m_entered_tile && m_previous_tile != (sf::Vector2i)getTilePosition())
	{
		m_previous_tile = (sf::Vector2i)getTilePosition();
		m_entered_tile = true;
	}
	else
		m_entered_tile = false;

	movementLogic();
}

void Enemy::updateEvents(sf::Event& event)
{
}

void Enemy::movementLogic()
{
	if (m_entered_tile)
	{
		int random = rand() % 10;

		if (!canMoveForward())
		{
			turnRight();
			turnRight();
		}

		/* 10% chance to turn */
		if (random == 0)
		{
			bool turned = false;

			if (canMoveRight())
			{
				turnRight();
				turned = true;
			}

			if (canMoveLeft() && !turned)
			{
				turnLeft();
				turned = true;
			}
		}
	}
}

bool Enemy::canMoveForward()
{
	sf::Vector2i enemy_position = (sf::Vector2i)Entity::getTilePosition();

	int direction = m_heading_direction;

	sf::Vector2i to_check = getCheckPos((Directions::Heading)direction, enemy_position);

	if (TileMap::getTile(to_check.x, to_check.y)->getType() == TileTypes::AIR)
	{
		return true;
	}

	return false;
}


bool Enemy::canMoveLeft()
{
	sf::Vector2i enemy_position = (sf::Vector2i)Entity::getTilePosition();

	int direction = m_heading_direction;

	if (direction - 1 < 0)
		direction = Directions::WEST;
	else
		direction = (Directions::Heading)(direction - 1);

	sf::Vector2i to_check = getCheckPos((Directions::Heading)direction, enemy_position);

	if (TileMap::getTile(to_check.x, to_check.y)->getType() == TileTypes::AIR)
	{
		return true;
	}

	return false;
}

bool Enemy::canMoveRight()
{
	sf::Vector2i enemy_position = (sf::Vector2i)Entity::getTilePosition();

	int direction = m_heading_direction;

	if (direction + 1 > 3)
		direction = Directions::NORTH;
	else
		direction = (Directions::Heading)(direction + 1);

	sf::Vector2i to_check = getCheckPos((Directions::Heading)direction, enemy_position);

	if (TileMap::getTile(to_check.x, to_check.y)->getType() == TileTypes::AIR)
	{
		return true;
	}

	return false;
}

void Enemy::turnLeft()
{
	if (m_heading_direction - 1 < 0)
		m_heading_direction = Directions::WEST;
	else
		m_heading_direction = (Directions::Heading)(m_heading_direction - 1);
}

void Enemy::turnRight()
{
	if (m_heading_direction + 1 > 3)
		m_heading_direction = Directions::NORTH;
	else
		m_heading_direction = (Directions::Heading)(m_heading_direction + 1);
}

void Enemy::setHeading(const Directions::Heading heading)
{
	m_heading_direction = heading;
}

sf::Vector2i Enemy::getCheckPos(Directions::Heading direction, sf::Vector2i position)
{
	sf::Vector2i to_check = position;

	switch (direction)
	{
	case Directions::NORTH:
		to_check.y = position.y - 1;
		break;
	case Directions::EAST:
		to_check.x = position.x + 1;
		break;
	case Directions::SOUTH:
		to_check.y = position.y + 1;
		break;
	case Directions::WEST:
		to_check.x = position.x - 1;
		break;
	}

	return to_check;
}
