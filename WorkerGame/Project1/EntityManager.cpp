#include "EntityManager.h"



EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(BaseGameEntity* entity) {
	//const int id = 
	emap[entity->ID()] = entity;
}

BaseGameEntity* EntityManager::getEntityById(int id) const{
	EntityMap::const_iterator it = emap.find(id);
	if (it == emap.end()) return nullptr;
	return it->second;
}

void EntityManager::removeEntity(BaseGameEntity* pEntity) {
	emap.erase(emap.find(pEntity->ID()));
}
