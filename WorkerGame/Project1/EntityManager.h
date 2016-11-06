#pragma once
#pragma warning (disable:4786)
#include <map>
#include <cassert>
#include <string>
#include "main.h"
typedef map<int, BaseGameEntity*> EntityMap;
#define EntityMgr EntityManager::Instance()
class EntityManager
{
	EntityManager();
	EntityManager(const EntityManager& e);
	EntityManager& operator=(const EntityManager&);	
	EntityMap emap;
public:
	~EntityManager();
	void addEntity(BaseGameEntity* entity); 
	BaseGameEntity* getEntityById(int id) const;
	void removeEntity(BaseGameEntity* pEntity);
	static EntityManager* Instance() {
		static EntityManager ent;
		return &ent;
	}
};


