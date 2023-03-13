#pragma once
#include "../Entity.h"
#include "../../Handlers/TextureHandler.h"

class Player : public Entity
{
public:
	Player(int x, int y);

	void move(const sf::Vector2f& velocity);
	virtual void update(const double dt) override;
	virtual void updateEvents(sf::Event& event) override;

private:
	void updateAnimation();
	sf::Clock m_animation_clock;

	RectAnimation m_up_walk, m_right_walk, m_down_walk, m_left_walk;
	sf::Keyboard::Key m_up_key, m_right_key, m_down_key, m_left_key;
};