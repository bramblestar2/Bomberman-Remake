#pragma once
#include <SFML/Graphics.hpp>
#include <map>

/* A Handler class for SFML Textures with all static methods */
/* Can be called anywhere by using TextureHandler::(METHOD_NAME) */
class TextureHandler
{
public:
	/* Returns a pointer to a texture using a string id */
	static sf::Texture* get(const std::string string_id);
	/* Loads a texture into the texture list */
	/* Requires a string_id to associate the texture with, */
	/* and the file path for the texture */
	static bool load(const std::string string_id, const std::string texture_path);
	/* Removes and deallocates a texture from the texture list using the string id */
	static bool remove(const std::string string_id);
	/* Clears the entire list of textures and deallocates memory */
	static void clear();
private:
	static std::map<std::string, sf::Texture*> m_textures;
};