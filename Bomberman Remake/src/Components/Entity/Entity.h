#pragma once
#include <SFML/Graphics.hpp>
#include "../Collidable/Collidable.h"
#include "../Animation/RectAnimation.h"

class Entity : public Collidable
{
public:

	virtual void update() = 0;
	virtual void updateEvents() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states);

	const sf::Vector2f& getVelocity() const;

protected:
	RectAnimation m_animation;

	void setVelocity(const sf::Vector2f& velocity);

private:

	sf::RectangleShape m_sprite;
	sf::Vector2f m_velocity;
};