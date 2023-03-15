#pragma once
#include <SFML/Graphics.hpp>

/* Inherets from SFML's view */
class ViewFollower : public sf::View
{
public:
	/* Normal Constructor, initializes variables */
	ViewFollower();

	/* Sets the current position ptr to follow */
	void follow(const sf::Vector2f* position_ptr);
	/* Updates the center position of the view to the vector2f ptr */
	void update();
	/* Sets the limits of the view, the view wont leave the limit area */
	void setLimits(sf::FloatRect limit_area);
	/* Returns the limits of the view */
	const sf::FloatRect& getLimits() const;

private:
	const sf::Vector2f* m_position_ptr;
	sf::FloatRect m_limit_area;
};

