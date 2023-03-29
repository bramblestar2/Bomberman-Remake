#pragma once
#include "../Entity.h"
#include "../Bomb/Bomb.h"
#include "../../Enums.h"

class Enemy : public Entity
{
public:
	Enemy(int x, int y);

	virtual void update(const double dt) override;

	virtual void updateEvents(sf::Event& event) override;

	const bool& isDead() const { return m_dead; }

	void kill() { m_dead = true; }

	void bombCollision(Bomb* bomb);

protected:
	virtual void movementLogic();
	bool canMoveForward();
	bool canMoveLeft();
	bool canMoveRight();
	bool canMoveBackward();
	bool randomTurn();
	void turnLeft();
	void turnRight();
	void setHeading(const Directions::Heading heading);
	Directions::Heading getHeading() const { return m_heading_direction; }

private:
	virtual void updateAnimation() = 0;

	sf::Vector2i getCheckPos(Directions::Heading direction, sf::Vector2i position);

	Directions::Heading m_heading_direction;


	//Should be true when the enemy has entered a new tile
	//and should be false when it hasnt entered a new tile
	bool m_entered_tile;
	//Previous tile position
	sf::Vector2i m_previous_tile;

	//If the enemy is dead or not
	bool m_dead;
};