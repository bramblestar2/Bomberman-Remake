#include "Collidable.h"
#include <iostream>

bool Collidable::check(Collidable& other)
{
    return m_rect.intersects(other.m_rect);
}

bool Collidable::check(Collidable& other, sf::Vector2f& v_correction, const sf::Vector2f& velocity)
{
    sf::FloatRect inter;
    if (m_rect.intersects(other.m_rect, inter))
    {
        float this_left = m_rect.left;
        float this_right = m_rect.left + m_rect.width;
        float this_top = m_rect.top;
        float this_bottom = m_rect.top + m_rect.height;

        float other_left = other.m_rect.left;
        float other_right = other.m_rect.left + other.m_rect.width;
        float other_top = other.m_rect.top;
        float other_bottom = other.m_rect.top + other.m_rect.height;

        auto lerp = [](float a, float b, float t) -> float
        {
            return a + t * (b - a);
        };

        float time = 2.f;

        float left_intersect = -(this_right - other_left) - 0.1;
        float right_intersect = -(this_left - other_right) + 0.1;
        float top_intersect = -(this_bottom - other_top) - 0.1;
        float bottom_intersect = -(this_top - other_bottom) + 0.1;

        //std::cout << left_intersect << " - " << right_intersect << " - " << top_intersect << " - " << bottom_intersect << "\n";
        std::cout << inter.left << " - " << inter.top << " - " << inter.width << " - " << inter.height << "\n";

        if (inter.width < 5 && inter.height > 5)
        {
            if (inter.left == other_left)
                v_correction.x = left_intersect;
            else
                v_correction.x = right_intersect;
        }
        else if (inter.height < 5)
        {
            if (inter.top == other_top)
                v_correction.y = top_intersect;
            else
                v_correction.y = bottom_intersect;
        }

        //if (velocity.x != 0)
        //{
        //    /* Horizontal Checks */
        //
        //    //If should be left
        //    //Check if left is less than left other.m_rect and if
        //    //right of m_rect is greater than left other.m_rect
        //    //If true, velocity.x should move to the left of m_rect
        //    if (this_left < other_left && this_right > other_left)
        //    {
        //        //v_correction.x = lerp(v_correction.x, -(this_right - other_left) - 0.1, time);
        //        v_correction.x = -(this_right - other_left) - 0.1;
        //    }
        //
        //    //If should be right
        //    //Check if left is less than right other.m_rect and if
        //    //right of m_rect is greater than right other.m_rect
        //    //If true, velocity.x should move to the left of m_rect
        //    else if (this_left < other_right && this_right > other_right)
        //    {
        //        //v_correction.x = lerp(v_correction.x, -(this_left - other_right) + 0.1, time);
        //        v_correction.x = -(this_left - other_right) + 0.1;
        //    }
        //}
        //else if (velocity.y != 0)
        //{
        //    /* Vertical Checks */
        //
        //    //If should be up
        //    //Check if top is less than top other.m_rect and if
        //    //bottom of m_rect is greater than top other.m_rect
        //    //If true, velocity should move to the top of m_rect
        //    if (this_top < other_top && this_bottom > other_top)
        //    {
        //        //v_correction.y = lerp(v_correction.y, -(this_bottom - other_top) - 0.1, time);
        //        v_correction.y = -(this_bottom - other_top) - 0.1;
        //    }
        //
        //    //If should be down
        //    //Check if top is less than bottom other.m_rect and if
        //    //bottom of m_rect is greater than bottom other.m_rect
        //    //If true, velocity should move to the bottom of m_rect
        //    else if (this_top < other_bottom && this_bottom > other_bottom)
        //    {
        //        //v_correction.y = lerp(v_correction.y, -(this_top - other_bottom) + 0.1, time);
        //        v_correction.y = -(this_top - other_bottom) + 0.1;
        //    }
        //
        //
        //}

        return true;
    }

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