#pragma once
#include <SFML/Graphics.hpp>
#include "../Collidable/Collidable.h"
#include "../Animation/RectAnimation.h"
#include "../TileMap/Tile/Tile.h"

#define ENTITY_SIZE_X 64
#define ENTITY_SIZE_Y 64

/* A abstract class that can be used to set up a Entity */
class Entity : public Collidable
{
public:
	Entity(int x, int y);

	/* Pure virtual method for updating Entity */
	virtual void update(const double dt) = 0;
	/* Pure virtual method for updating the events of Entity */
	virtual void updateEvents(sf::Event& event) = 0;
	/* virtual method that can be redefined to be drawn in a different way */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states);

	/* Move the entity at an offset */
	void move(const sf::Vector2f& velocity);

	/* Returns the velocity of the Entity */
	const sf::Vector2f& getVelocity() const;
	/* Returns the speed of the Entity */
	const float& getSpeed() const { return m_speed; }
	/* Returns the tile position of the Entity */
	sf::Vector2f getTilePosition();
	/* Returns the position of the Entity sprite */
	const sf::Vector2f& getPosition() const;

protected:
	sf::RectangleShape m_sprite;

	/* Sets the velocity of the Entity */
	void setVelocity(const sf::Vector2f& velocity);
	/* Sets the speed of the entity */
	void setSpeed(const float speed);

private:
	float m_speed;
	sf::Vector2f m_velocity;
};