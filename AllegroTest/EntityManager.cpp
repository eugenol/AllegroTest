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
	for (std::list<GameObject*>::iterator iter = entityList->begin(); iter != entityList->end(); iter++)
	{
		if (!(*iter)->getAlive())
		{
			GameObject *tempPtr;
			tempPtr = *iter;
			//entityList->erase(iter);
			//delete tempPtr;
		}
	}
}

void EntityManager::AddEntity(GameObject *entity)
{
	// add entity to the list
	entityList->push_back(entity);
}