#pragma once
#include <vector>
#include "../Entity.h"

/* Bomb inherits from Entity class */
class Bomb : public Entity
{
public:
	/* Specify the X and Y tile position of the bomb */
	/* Setting the explosion radius of the bomb is optional */
	/* Setting whether the bomb has a set timer before it explodes is optional */
	Bomb(const int x, const int y, const int radius = 1, const bool has_timer = true);

	/* Explodes the bomb, setting the playing animation of the explosion to start */
	/* Destroys the tiles that are in the affected range of the bomb */
	void explode();
	/* Updates the bombs animation */
	/* Explodes after a set of time if there is a timer */
	virtual void update(const double dt) override;
	/* No events */
	virtual void updateEvents(sf::Event& event) override;
	/* Overrides the draw method of entity due to the explosion animation */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

	/* Returns the offset of where the collider should move to */
	sf::Vector2f collision(Collidable& collider);
	/* Returns true if the bomb has exploded */
	const bool& hasExploded() const { return m_has_exploded; }
	/* Returns true if the animation for the explosion has ended */
	const bool& hasExplosionFinished() const { return m_explosion_ended; }
	/* Returns a list of what tile positions would be affected by the explosion */
	std::vector<sf::Vector2f> getEffectedTiles(const bool change_distances = true);
	/* Returns true if a tile position is in the range of the bomb */
	bool isTileAffected(sf::Vector2f tile_position);

private:
	void updateBombAnimation();
	void updateExplosionAnimation();

	/* Dont collide if player dropped bomb, 
	but start colliding when player leaves bomb */

	bool m_player_on_bomb;

	/* */

	bool m_has_exploded;
	bool m_explosion_ended;
	bool m_has_timer;
	//The radius the bomb will explode at
	int m_explosion_radius;
	//The radius the bomb can explode at for each direction
	// [0] N -> [1] E -> [2] S -> [3] W
	int m_exploded_radius[4]{0};

	sf::Clock m_bomb_clock, m_detonation_clock;

	Collidable m_horizontal_explosion_collider, m_vertical_explosion_collider;

	//Bomb sitting animation
	RectAnimation m_bomb_animation;
	//Explosion end parts
	RectAnimation m_up_explosion, m_right_explosion, m_down_explosion, m_left_explosion;
	//Continuous explosion parts
	RectAnimation m_center_explosion, m_horizontal_explosion, m_vertical_explosion;
};