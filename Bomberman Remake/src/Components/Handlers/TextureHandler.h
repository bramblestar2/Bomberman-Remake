#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureHandler
{
public:
	static sf::Texture* get(const std::string string_id);
	static bool load(const std::string string_id, const std::string texture_path);
	static bool remove(const std::string string_id);
private:
	static std::map<std::string, sf::Texture*> m_textures;
};