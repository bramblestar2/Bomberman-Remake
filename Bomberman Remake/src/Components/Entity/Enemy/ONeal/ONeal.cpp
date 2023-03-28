#include "ONeal.h"
#include <iostream>

ONeal::ONeal(int x, int y) : Enemy(x, y)
{
	m_left_animation.setTexturePtr(TextureHandler::get("enemies"));
	m_right_animation.setTexturePtr(TextureHandler::get("enemies"));
	m_death_animation.setTexturePtr(TextureHandler::get("enemies"));

	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
		{
			m_right_animation.addFrame(sf::IntRect(16 * i, 16 * 0, 16, 16));
			m_left_animation.addFrame(sf::IntRect(16 * i, 16 * 1, 16, 16));
		}

		m_death_animation.addFrame(sf::IntRect(16 * i, 16 * 2, 16, 16));
	}

	m_right_animation.addFrame(sf::IntRect(16 * 1, 16 * 0, 16, 16));
	m_left_animation.addFrame(sf::IntRect(16 * 1, 16 * 1, 16, 16));

	m_looking_direction = Directions::EAST;
}

void ONeal::updateAnimation()
{
	if (Enemy::getHeading() == Directions::Heading::EAST || 
		Enemy::getHeading() == Directions::Heading::WEST)
		m_looking_direction = Enemy::getHeading();

	if (m_animation_clock.getElapsedTime().asSeconds() > 0.2)
	{
		if (!Enemy::isDead())
		{
			m_right_animation.nextFrame();
			m_left_animation.nextFrame();
		}
		else
		{
			if (m_death_animation.currentFrame() < m_death_animation.frames()-1)
				m_death_animation.nextFrame();
		}

		//Looking right
		if (m_looking_direction == Directions::EAST)
			m_right_animation.apply(Entity::m_sprite);
		//Looking left
		else if (m_looking_direction == Directions::WEST)
			m_left_animation.apply(Entity::m_sprite);

		m_animation_clock.restart();
	}
}
