#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update()
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

bool GameObject::CheckCollision(GameObject *otherObject)
{
	//if (this->x + this->width / 2 > otherObject->x - otherObject->width/2 &&
	//	this->x - this->width / 2 < otherObject->x + otherObject->width/2 &&
	//	this->y + this->height / 2 > otherObject->y - otherObject->height/2 &&
	//	this->y - this->height / 2 < otherObject->y + otherObject->height/2)
	//	return true;
	//else
	//	return false;

	if ((x - width / 2 > otherObject->x + otherObject->width / 2) ||
		(y - height / 2 > otherObject->y + otherObject->height / 2) ||
		(otherObject->x - otherObject->width / 2 > x - width / 2) ||
		(otherObject->y - otherObject->height > y + height / 2))
	{
		return false;
	}
	return true;

}

void GameObject::Collided(GameObject *otherObject)
{
	//if (direction_x == 1)
	//	x = otherObject->x - (otherObject->width / 2 + width / 2);
	//else if (direction_x == -1)
	//	x = otherObject->x + (otherObject->width / 2 + width / 2);
	//else if (direction_y == 1)
	//	y = otherObject->y - (otherObject->height / 2 + height / 2);
	//else if (direction_y == -1)
	//	y = otherObject->y + (otherObject->height / 2 + height / 2);
	float diffx = x - otherObject->x;
	float diffy = y - otherObject->y;
	float vertdist = otherObject->width / 2 + width / 2;
	float hordist = otherObject->height / 2 + height / 2;

	if (x < otherObject->x)
	{
		x -= vertdist / 2;
		otherObject->x = otherObject->x + vertdist / 2;
	}
	if (x > otherObject->x)
	{
		x += vertdist / 2;
		otherObject->x = otherObject->x - vertdist / 2;
	}
	else if (y < otherObject->y)
	{
		y -= hordist / 2;
		otherObject->y = otherObject->y + hordist / 2;
	}
	else if (y > otherObject->y)
	{
		y += hordist / 2;
		otherObject->y = otherObject->y - hordist / 2;
	}

}