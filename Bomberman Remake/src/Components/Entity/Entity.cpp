#include "Entity.h"

Entity::Entity(int x, int y)
{
	m_sprite.setPosition(x * ENTITY_SIZE_X, y * ENTITY_SIZE_Y);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_sprite, states);
}

const sf::Vector2f& Entity::getVelocity() const
{
	return m_velocity;
}

sf::Vector2f Entity::getTilePosition()
{
	sf::Vector2f pos = m_sprite.getPosition();
	pos.x /= TILE_SIZE_X;
	pos.y /= TILE_SIZE_Y;
	pos.x = (int)pos.x;
	pos.y = (int)pos.y;

	return pos;
}

const sf::Vector2f& Entity::getPosition() const
{
	return m_sprite.getPosition();
}

void Entity::setVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}

void Entity::setSpeed(const float speed)
{
	m_speed = speed;
}
