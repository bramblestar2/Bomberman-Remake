#include "ONeal.h"

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
}

void ONeal::updateAnimation()
{
	if (m_animation_clock.getElapsedTime().asSeconds() > 0.2)
	{

	}
}
