#include "Entity.h"

void Entity::draw(sf::RenderTarget& target, sf::RenderStates& states)
{
	target.draw(m_sprite, states);
}

const sf::Vector2f& Entity::getVelocity() const
{
	return m_velocity;
}

void Entity::setVelocity(const sf::Vector2f& velocity)
{
	m_velocity = velocity;
}
