#include "Collidable.h"

bool Collidable::check(Collidable& other)
{
    return m_rect.intersects(other.m_rect);
}

bool Collidable::check(Collidable& other, sf::Vector2f& velocity)
{
    /* Horizontal Checks */

    //Check if left is less than left other.m_rect and if
    //right of m_rect is greater than left other.m_rect
    //If true, velocity.x should move to the left of m_rect

    //Check if left is less than right other.m_rect and if
    //right of m_rect is greater than right other.m_rect
    //If true, velocity.x should move to the left of m_rect

    /* Vertical Checks */


    return false;
}

const sf::FloatRect& Collidable::getBounds() const
{
    return m_rect;
}

sf::RectangleShape Collidable::getVisualBounds()
{
    sf::RectangleShape temp({ m_rect.width, m_rect.height });

    temp.setFillColor(sf::Color::Transparent);
    temp.setOutlineColor(sf::Color::Blue);
    temp.setOutlineThickness(1);

    return temp;
}

void Collidable::updateRect(sf::FloatRect rect)
{
    m_rect = rect;
}
