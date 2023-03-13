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

};