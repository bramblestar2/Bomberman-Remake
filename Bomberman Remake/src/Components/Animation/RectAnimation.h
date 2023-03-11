#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class RectAnimation
{
public:
	RectAnimation(sf::Texture* texture_ptr) : 
		m_texture_ptr(texture_ptr), m_current_frame(0)
	{ }
	~RectAnimation();

	void apply(sf::Sprite& sprite);
	void apply(sf::Shape& shape);

	void addFrame(sf::IntRect rect);
	bool removeFrame(int index);

	bool setCurrentFrame(int frame);
	int nextFrame();
	int previousFrame();

	int frames() const;
	int currentFrame() const;

private:
	std::vector<sf::IntRect*> m_rects;
	sf::Texture* m_texture_ptr;

	int m_current_frame;
};