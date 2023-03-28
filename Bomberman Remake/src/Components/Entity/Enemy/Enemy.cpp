#include "Enemy.h"
#include "../../TileMap/TileMap.h"
#include <iostream>
#include <time.h>

Enemy::Enemy(int x, int y) : Entity(x, y)
{
	srand(time(NULL));

	m_heading_direction = Directions::EAST;

	m_entered_tile = true;
	m_dead = false;

	m_previous_tile = { x, y };

	Entity::setSpeed(100);

	Entity::m_sprite.setSize({ ENTITY_SIZE_X, ENTITY_SIZE_Y });
}

void Enemy::update(const double dt)
{
	//If enemy has entered new tile, set to true
	sf::Vector2f pos = Entity::m_sprite.getPosition();

	pos.x /= TILE_SIZE_X;
	pos.y /= TILE_SIZE_Y;
	pos.x = (int)pos.x;
	pos.y = (int)pos.y;

	if (!m_entered_tile && m_previous_tile != (sf::Vector2i)pos)
	{
		m_previous_tile = (sf::Vector2i)pos;
		m_entered_tile = true;
	}
	else
		m_entered_tile = false;

	movementLogic();

	sf::Vector2i velocity = getCheckPos(m_heading_direction, sf::Vector2i());
	Entity::setVelocity(sf::Vector2f(velocity.x * Entity::getSpeed(), 
									 velocity.y * Entity::getSpeed()));
	Entity::m_sprite.move(Entity::getVelocity().x * dt, Entity::getVelocity().y * dt);

	updateAnimation();

	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());
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

		/* 30% chance to turn */
		if (random < 3)
		{
			bool canTurnLeft = false; 
			bool canTurnRight = false; 

			if (canMoveRight())
				canTurnRight = true;
			if (canMoveLeft())
				canTurnLeft = true;

			if (canTurnLeft && canTurnRight)
			{
				switch (rand() % 2)
				{
				case 0: //Left turn
					turnLeft();
					break;
				case 1: //Right turn
					turnRight();
					break;
				}
			}
			else if (canTurnLeft)
				turnLeft();
			else if (canTurnRight)
				turnRight();
		}
	}
}

bool Enemy::canMoveForward()
{
	sf::Vector2i enemy_position = (sf::Vector2i)Entity::getTilePosition();

	sf::Vector2i to_check = getCheckPos(m_heading_direction, enemy_position);

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
