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