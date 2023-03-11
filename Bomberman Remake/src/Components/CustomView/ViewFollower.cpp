#include "ViewFollower.h"
#include <iostream>

ViewFollower::ViewFollower()
{
	m_position_ptr = nullptr;
}

void ViewFollower::follow(const sf::Vector2f* position_ptr)
{
	m_position_ptr = position_ptr;
}

void ViewFollower::update()
{
	if (m_position_ptr != nullptr)
	{
		if (m_limit_area.width != 0 && m_limit_area.height != 0 || m_limit_area.left != 0 && m_limit_area.top != 0)
		{
			sf::Vector2f new_position = *m_position_ptr;

			//View rect
			float top = new_position.y - (this->getSize().y/2);
			float bottom = top + this->getSize().y;
			float left = new_position.x - (this->getSize().x/2);
			float right = left + this->getSize().x;

			if (left < m_limit_area.left)
				new_position.x = m_limit_area.left + (this->getSize().x / 2);
			else if (right > m_limit_area.left + m_limit_area.width)
				new_position.x = (m_limit_area.left + m_limit_area.width) - (this->getSize().x / 2);

			if (top < m_limit_area.top)
				new_position.y = m_limit_area.top + (this->getSize().y / 2);
			else if (bottom > m_limit_area.top + m_limit_area.height)
				new_position.y = (m_limit_area.top + m_limit_area.height) - (this->getSize().y / 2);

			this->setCenter(new_position);
		}
		else
			this->setCenter(*m_position_ptr);
	}
}

void ViewFollower::setLimits(sf::FloatRect limit_area)
{
	m_limit_area = limit_area;
}

const sf::FloatRect& ViewFollower::getLimits() const
{
	return m_limit_area;
}
