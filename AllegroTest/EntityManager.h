/*
* This singleton class is used to manage all entities it should make it easier to handle the
* creation and destruction of bullets and enemies.
*
*/
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <list>
#include "GameObject.h"

class EntityManager
{
private:
	EntityManager(); //Make constructor Private, so that only one instance can be made
	std::list<GameObject*> *entityList;
public:
	static EntityManager & getInstance();
	~EntityManager();

	void getEntityList(std::list<GameObject*> *entityList);
	void UpdateList();
	void AddEntity(GameObject *entity);

	//Can't use these methods to accidentally copy the input manager.
	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;
};
#endif

