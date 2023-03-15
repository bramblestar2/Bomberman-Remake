#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

/* A animation class */
class RectAnimation
{
public:
	/* Stores the pointer to the texture for animations */
	RectAnimation(sf::Texture* texture_ptr = nullptr) : 
		m_texture_ptr(texture_ptr), m_current_frame(0)
	{ }
	~RectAnimation();

	/* Applies the current frame to the given sprite */
	void apply(sf::Sprite& sprite);
	/* Applies the current frame to the given shape */
	void apply(sf::Shape& shape);

	/* Adds a new frame into the animation(rect) list */
	void addFrame(sf::IntRect rect);
	/* Removes a frame from the animation(rect) list */
	bool removeFrame(int index);

	/* Sets the texture ptr */
	void setTexturePtr(sf::Texture* texture_ptr);
	/* Sets the current frame for the animation */
	bool setCurrentFrame(int frame);
	/* Goes to the next frame in the animation */
	/* If the next frame exceeds the max frames, it starts back at frame zero */
	int nextFrame();
	/* Goes to the previous frame in the animation */
	/* If the previous frame goes below 0, it starts at the max frames */
	int previousFrame();

	/* Returns the number of frames in the animation */
	int frames() const;
	/* Returns the current frame number of the animation */
	int currentFrame() const;

private:
	std::vector<sf::IntRect*> m_rects;
	sf::Texture* m_texture_ptr;

	int m_current_frame;
};