#pragma once
#include <vector>
#include "../Entity.h"
#include "../../Handlers/TextureHandler.h"
#include "../Bomb/Bomb.h"

/* The class for a User to control the player character in the game */
class Player : public Entity
{
public:
	/* Specify the X and Y tile position of the Player */
	Player(int x, int y);
	~Player();

	/* Moves the player according to what key the user presses */
	virtual void update(const double dt) override;
	/* Updates the events of player */
	/* Mainly for whether a bomb should be placed and */
	/* if the player detonates the bomb if the player has a detonator */
	virtual void updateEvents(sf::Event& event) override;
	/* The draw method has been overriden due to the bombs needing to be drawn */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) override;

private:
	void updateAnimation();
	sf::Clock m_animation_clock;

	RectAnimation m_up_walk, m_right_walk, m_down_walk, m_left_walk;
	sf::Keyboard::Key m_up_key, m_right_key, m_down_key, m_left_key;

	int m_max_bombs;
	int m_bomb_range;
	bool m_has_detonator;
	bool m_pass_through;

	std::vector<Bomb*> m_bomb_list;
};