#pragma once
#include "../Enemy.h"

class ONeal : public Enemy
{
public:
	ONeal(int x, int y);

private:
	void updateAnimation() override;

	RectAnimation m_left_animation, m_right_animation, m_death_animation;
	sf::Clock m_animation_clock;

	//For determining whether to use left animation or right animation
	Directions::Heading m_looking_direction;
};