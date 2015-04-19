#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update(ALLEGRO_EVENT ev)
{
	//bounds checking
	if (y <= MIN_HEIGHT + height/2+bound)
		y = MIN_HEIGHT + height / 2 + bound;
	
	//Fixed so that their feet toughes the ground
	if (y >= MAX_HEIGHT - (height / 2 - 2))
		y = MAX_HEIGHT - (height / 2 - 2);

	if (x <= MIN_WIDTH + width / 2 + bound)
		x = MIN_WIDTH + width / 2 + bound;
	//Scrolling, so no need for this check

	if (x >= MAX_WIDTH - (0 + width / 2 + bound))
		x = MAX_WIDTH - (0 + width / 2 + bound);
}