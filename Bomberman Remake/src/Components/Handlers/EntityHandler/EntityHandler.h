#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "../../Entity/Entity.h"

class EntityHandler
{
public:
	static std::vector<Entity*>* getList(const std::string id);
	static Entity* get(const std::string id, const int it);
	static void add(const std::string id, Entity* entity);

	static void remove(const std::string id);
	static void clear();

private:
	static std::unordered_map<std::string, std::vector<Entity*>> m_entities;
};