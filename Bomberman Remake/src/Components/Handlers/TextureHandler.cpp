#include "TextureHandler.h"

std::map<std::string, sf::Texture*> TextureHandler::m_textures;

sf::Texture* TextureHandler::get(const std::string string_id)
{
    auto find_texture = m_textures.find(string_id);

    if (find_texture != m_textures.end())
        return m_textures[string_id];
    
    return nullptr;
}

bool TextureHandler::load(const std::string string_id, const std::string texture_path)
{
    auto id_exists = m_textures.find(string_id);
    if (id_exists == m_textures.end())
    {
        sf::Texture* tex = new sf::Texture();

        if (!tex->loadFromFile(texture_path))
            delete tex;
        else
        {
            m_textures[string_id] = tex;
            return true;
        }
    }
    return false;
}

bool TextureHandler::remove(const std::string string_id)
{
    auto find_texture = m_textures.find(string_id);

    if (find_texture != m_textures.end())
    {
        delete m_textures[string_id];
        m_textures.erase(string_id);

        return true;
    }

    return false;
}
