#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collidable/Collidable.h"
#include "../../Animation/RectAnimation.h"
#include "../../Enums.h"
#include "../../Handlers/TextureHandler.h"

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

class Tile : public Collidable
{
public:
	Tile(const int x, const int y, const TileTypes::ID type);

	void draw(sf::RenderTarget& target, sf::RenderStates& states);
	
	void setType(const TileTypes::ID type);
	virtual void setHasPowerup(const bool has_powerup, 
		const PowerupTypes::ID type);
	void destroy();
	void update();

	const sf::Vector2i& getTilePosition() const { return m_tile_position; }
	const TileTypes::ID& getType() const { return m_tile_type; }
	bool isDestroyed() const { return m_destroyed; }
	bool isDestructable() const { return m_destructable; }
protected:
	RectAnimation m_animation;

private:
	void getTextureByID();

	sf::RectangleShape m_sprite;
	sf::Vector2i m_tile_position;
	TileTypes::ID m_tile_type;

	bool m_destroyed;
	bool m_destructable;
	bool m_has_powerup;
};