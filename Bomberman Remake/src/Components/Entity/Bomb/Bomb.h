#pragma once
#include <vector>
#include "../Entity.h"

class Bomb : public Entity
{
public:
	Bomb(const int x, const int y, const int radius = 1, const bool has_timer = true);

	void explode();
	virtual void update(const double dt) override;
	virtual void updateEvents(sf::Event& event) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

	sf::Vector2f collision(Collidable& collider);
	const bool& hasExploded() const { return m_has_exploded; }
	const bool& hasExplosionFinished() const { return m_explosion_ended; }
	//Get tile positions that the explosion takes place on
	std::vector<sf::Vector2f> getEffectedTiles();

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