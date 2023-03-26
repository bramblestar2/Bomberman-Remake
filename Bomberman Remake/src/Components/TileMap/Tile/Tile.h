#pragma once
#include <SFML/Graphics.hpp>
#include "../../Collidable/Collidable.h"
#include "../../Animation/RectAnimation.h"
#include "../../Enums.h"
#include "../../Handlers/TextureHandler/TextureHandler.h"

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

/* A class for tiles that can have a variety of different uses */
class Tile : public Collidable
{
public:
	/* Sets the X and Y position of the tile as well as the Type of the tile */
	Tile(const int x, const int y, const TileTypes::ID type);

	/* Draws the tile to the screen */
	void draw(sf::RenderTarget& target, sf::RenderStates& states);
	
	/* Sets the type of a tile */
	virtual void setType(const TileTypes::ID type);
	/* Specifies if the tile has a powerup and what kind of powerup it is */
	virtual void setHasPowerup(const bool has_powerup, 
		const PowerupTypes::ID type);
	/* Adds the tile to the destroy queue in TileMap */
	void destroy();
	/* Virtual method in case update needs to be changed in the future */
	virtual void update();

	const sf::Vector2i& getTilePosition() const { return m_tile_position; }
	const TileTypes::ID& getType() const { return m_tile_type; }
	const bool& isDestroyed() const { return m_destroyed; }
	const bool& isDestructable() const { return m_destructable; }
	const bool& hasDestroyedAnimation() const { return m_has_destroyed_animation; }
	const bool& hasAnimationFinished() const { return (m_animation.currentFrame() == m_animation.frames() - 1); }
	const bool& isPowerup() const { return m_has_powerup; }
protected:
	virtual void updateAnimation();

	RectAnimation m_animation;

private:
	void getTextureByID();

	sf::Clock m_animation_clock;

	sf::RectangleShape m_sprite;
	sf::Vector2i m_tile_position;
	TileTypes::ID m_tile_type;

	bool m_has_destroyed_animation;
	bool m_destroyed;
	bool m_destructable;
	bool m_has_powerup;
};