#include "EntityManager.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}


EntityManager & EntityManager::getInstance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::getEntityList(std::list<GameObject*> *entityList)
{
	EntityManager::entityList = entityList;
}

void EntityManager::UpdateList()
{
	// Call this each update loop, if the object is dead, delete it

	std::list<GameObject*>::iterator iter = entityList->begin();
	while (iter != entityList->end())
	{
		if (!(*iter)->getAlive())
		{
			std::list<GameObject*>::iterator prev = iter++;
			GameObject *tempPtr;
			tempPtr = *prev;
			entityList->erase(prev);
			delete tempPtr;
		}
		else
			iter++;
	}
}

void EntityManager::AddEntity(GameObject *entity)
{
	// add entity to the list
	entityList->push_back(entity);
}