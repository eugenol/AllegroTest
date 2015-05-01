/*
* This singleton class is used to manage all entities it should make it easier to handle the
* creation and destruction of bullets and enemies.
*
*/
#pragma once
class EntityManager
{
private:
	EntityManager(); //Make constructor Private, so that only one instance can be made
public:
	static EntityManager & getInstance();
	~EntityManager();

	//Can't use these methods to accidentally copy the input manager.
	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;
};

