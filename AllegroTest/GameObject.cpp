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
	if (y <= 0 + height/2+bound)
		y = 0 + height / 2 + bound;

	if (y >= SCREEN_HEIGHT - (height / 2 + bound))
		y = SCREEN_HEIGHT - (height / 2 + bound);

	if (x <= 0 + width / 2 + bound)
		x = 0 + width / 2 + bound;

	if (x >= SCREEN_WIDTH - (0 + width / 2 + bound))
		x = SCREEN_WIDTH - (0 + width / 2 + bound);
}