#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update(const bool *key)
{
	//update position
	if (key[KEY_UP])
		y -= velocity_y;
	if (key[KEY_DOWN])
		y += velocity_y;
	if (key[KEY_LEFT])
		x -= velocity_x;
	if (key[KEY_RIGHT])
		x += velocity_x;

	//bounds checking
	if (y <= size)
		y = size;

	if (y >= SCREEN_HEIGHT - size)
		y = SCREEN_HEIGHT - size;

	if (x <= size)
		x=size;

	if (x >= SCREEN_WIDTH - size)
		x = SCREEN_WIDTH -size;
}