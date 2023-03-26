#include "EntityHandler.h"

std::unordered_map<std::string, std::vector<Entity*>> EntityHandler::m_entities;

std::vector<Entity*>* EntityHandler::getList(const std::string id)
{
    auto find_id = m_entities.find(id);

    if (find_id != m_entities.end())
    {
        return &m_entities[id];
    }

    return nullptr;
}

Entity* EntityHandler::get(const std::string id, const int it)
{
    auto find_id = m_entities.find(id);

    if (find_id != m_entities.end())
    {
        if (it < m_entities[id].size() && it >= 0)
        {
            return m_entities[id].at(it);
        }
    }

    return nullptr;
}

void EntityHandler::add(const std::string id, Entity* entity)
{
    m_entities[id].push_back(entity);
}

void EntityHandler::remove(const std::string id)
{
    auto find_id = m_entities.find(id);

    if (find_id != m_entities.end())
    {
        while (m_entities[id].size() > 0)
        {
            delete m_entities[id].at(0);
            m_entities.erase(id);
        }
    }
}

void EntityHandler::clear()
{
    for (auto lists : m_entities)
    {
        remove(lists.first);
    }
}
