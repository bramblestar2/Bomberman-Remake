#pragma once
#include <SFML/Graphics.hpp>
#include "../Collidable/Collidable.h"
#include "../Animation/RectAnimation.h"
#include "../TileMap/Tile/Tile.h"

#define ENTITY_SIZE_X 64
#define ENTITY_SIZE_Y 64

class Entity : public Collidable
{
public:
	Entity(int x, int y);

	virtual void update(const double dt) = 0;
	virtual void updateEvents(sf::Event& event) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states);

	const sf::Vector2f& getVelocity() const;
	const float& getSpeed() const { return m_speed; }
	sf::Vector2f getTilePosition();
	const sf::Vector2f& getPosition() const;

protected:
	RectAnimation m_animation;
	sf::RectangleShape m_sprite;

	void setVelocity(const sf::Vector2f& velocity);
	void setSpeed(const float speed);

private:
	float m_speed;
	sf::Vector2f m_velocity;
};