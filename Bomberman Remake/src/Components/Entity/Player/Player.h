#pragma once
#include <vector>
#include "../Entity.h"
#include "../../Handlers/TextureHandler.h"
#include "../Bomb/Bomb.h"

class Player : public Entity
{
public:
	Player(int x, int y);
	~Player();

	void move(const sf::Vector2f& velocity);
	virtual void update(const double dt) override;
	virtual void updateEvents(sf::Event& event) override;
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