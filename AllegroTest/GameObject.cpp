#include "GameObject.h"


GameObject::GameObject(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, int ID, ALLEGRO_BITMAP *image)
{
	
	GameObject::x = x;
	GameObject::y = y;
	GameObject::height = height;
	GameObject::width = width;
	GameObject::velocity_x = velocity_x;
	GameObject::velocity_y = velocity_y;
	GameObject::bound = bound;
	GameObject::ID = ID;
	GameObject::image = image;
	health = 100;
	isAlive = true;
}


GameObject::~GameObject()
{
}

void GameObject::Update()
{
	////bounds checking
	//if (y <= MIN_HEIGHT + height/2+bound)
	//	y = MIN_HEIGHT + height / 2 + bound;
	//
	////Fixed so that their feet toughes the ground
	//if (y >= MAX_HEIGHT - (height / 2 - 2))
	//	y = MAX_HEIGHT - (height / 2 - 2);

	//if (x <= MIN_WIDTH + width / 2 + bound)
	//	x = MIN_WIDTH + width / 2 + bound;
	////Scrolling, so no need for this check

	//if (x >= MAX_WIDTH - (0 + width / 2 + bound))
	//	x = MAX_WIDTH - (0 + width / 2 + bound);

	if (x > SCREEN_WIDTH - width / 2)
		x = SCREEN_WIDTH - width / 2;

	if (x < width / 2)
		x = width / 2;

	if (y > SCREEN_HEIGHT - height / 2)
		y = SCREEN_HEIGHT - height / 2;

	if (y < height / 2)
		y = height / 2;

	// If dead, dead.
	if (health <= 0)
		isAlive = false;

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
	if ((this->ID == PLAYER || this->ID == ENEMY) && (otherObject->ID == PLAYER || otherObject->ID == ENEMY))
	{
		float diffx = x - otherObject->x;
		float diffy = y - otherObject->y;
		float vertdist = otherObject->width / 2 + width / 2;
		float hordist = otherObject->height / 2 + height / 2;
		vertdist /= 2;
		hordist /= 2;

		if (x < otherObject->x)
		{
			x -= (vertdist / 2 - fabsf(diffx) / 2);
			otherObject->x = otherObject->x + (vertdist / 2 - fabsf(diffx) / 2);
		}
		if (x > otherObject->x)
		{
			x += (vertdist / 2 - fabsf(diffx) / 2);
			otherObject->x = otherObject->x - (vertdist / 2 - fabsf(diffx) / 2);
		}
		else if (y < otherObject->y)
		{
			y -= (hordist / 2 - fabsf(diffy) / 2);
			otherObject->y = otherObject->y + (hordist / 2 - fabsf(diffy) / 2);
		}
		else if (y > otherObject->y)
		{
			y += (hordist / 2 - fabsf(diffy) / 2);
			otherObject->y = otherObject->y - (hordist / 2 - fabsf(diffy) / 2);
		}

		if (this->ID == PLAYER)
		{
			if (rand()%20 == 0)
				this->health -= 1;
		}
		if (otherObject->ID == PLAYER)
		{
			if (rand()%20 == 0)
				otherObject->health -= 1;
		}

	}
	else if ((this->ID == BULLET && otherObject->ID == ENEMY)&& this->getAlive())
	{
		this->isAlive = false;
		otherObject->health -= 20;
	}
	else if ((this->ID == ENEMY && otherObject->ID == BULLET) && otherObject->getAlive())
	{
		otherObject->isAlive = false;
		this->health -= 20;
	}



}