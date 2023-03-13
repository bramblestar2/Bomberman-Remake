#include "RectAnimation.h"

RectAnimation::~RectAnimation()
{
	while (m_rects.size() > 0)
	{
		delete m_rects.at(0);
		m_rects.erase(m_rects.begin());
	}
}

void RectAnimation::apply(sf::Sprite& sprite)
{
	if (m_texture_ptr != nullptr && m_rects.size() != 0)
	{
		sprite.setTexture(*m_texture_ptr);
		sprite.setTextureRect(*m_rects.at(m_current_frame));
	}
}

void RectAnimation::apply(sf::Shape& shape)
{
	if (m_texture_ptr != nullptr && m_rects.size() != 0)
	{
		shape.setTexture(m_texture_ptr, true);
		shape.setTextureRect(*m_rects.at(m_current_frame));
	}
}

void RectAnimation::addFrame(sf::IntRect rect)
{
	m_rects.push_back(new sf::IntRect(rect));
}

bool RectAnimation::removeFrame(int index)
{
	if (index >= 0 && index < m_rects.size())
	{
		delete m_rects.at(index);
		m_rects.erase(m_rects.begin() + index);

		return true;
	}

	return false;
}

void RectAnimation::setTexturePtr(sf::Texture* texture_ptr)
{
	m_texture_ptr = texture_ptr;
}

bool RectAnimation::setCurrentFrame(int frame)
{
	if (frame >= 0 && frame < m_rects.size())
	{
		m_current_frame = frame;
		return true;
	}

	return false;
}

int RectAnimation::nextFrame()
{
	if (m_current_frame + 1 >= m_rects.size())
		m_current_frame = 0;
	else
		m_current_frame++;

	return m_current_frame;
}

int RectAnimation::previousFrame()
{
	if (m_current_frame - 1 < 0)
		m_current_frame = m_rects.size() - 1;
	else
		m_current_frame--;

	return m_current_frame;
}

int RectAnimation::frames() const
{
	return m_rects.size();
}

int RectAnimation::currentFrame() const
{
	return m_current_frame;
}
