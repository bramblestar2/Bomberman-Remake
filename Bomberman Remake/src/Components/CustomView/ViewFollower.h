#pragma once
#include <SFML/Graphics.hpp>

class ViewFollower : public sf::View
{
public:
	ViewFollower();

	void follow(const sf::Vector2f* position_ptr);
	void update();
	void setLimits(sf::FloatRect limit_area);
	const sf::FloatRect& getLimits() const;

private:
	const sf::Vector2f* m_position_ptr;
	sf::FloatRect m_limit_area;
};

