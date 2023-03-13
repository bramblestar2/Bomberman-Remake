#include "Player.h"

Player::Player(int x, int y) : Entity(x, y)
{
	Entity::m_sprite.setSize({ ENTITY_SIZE_X, ENTITY_SIZE_Y });

	Entity::m_animation.setTexturePtr(TextureHandler::get("player"));
	Entity::m_animation.addFrame(sf::IntRect(16 * 0, 16 * 0, 12, 16));
	
	//Entity::m_animation.apply(Entity::m_sprite);

	Entity::setSpeed(200);
}

void Player::move(const sf::Vector2f& velocity)
{
	Entity::m_sprite.move(velocity);
	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());
}

void Player::update(const double dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		Entity::setVelocity(sf::Vector2f(Entity::getVelocity().x, -Entity::getSpeed() * dt));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		Entity::setVelocity(sf::Vector2f(Entity::getVelocity().x, Entity::getSpeed() * dt));
	else
	{
		Entity::setVelocity(sf::Vector2f(Entity::getVelocity().x, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		Entity::setVelocity(sf::Vector2f(-Entity::getSpeed() * dt, Entity::getVelocity().y));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		Entity::setVelocity(sf::Vector2f(Entity::getSpeed() * dt, Entity::getVelocity().y));
	else
	{
		Entity::setVelocity(sf::Vector2f(0, Entity::getVelocity().y));
	}

	Entity::m_sprite.move(Entity::getVelocity());

	Collidable::updateRect(Entity::m_sprite.getGlobalBounds());
}

void Player::updateEvents(sf::Event& event)
{
}
