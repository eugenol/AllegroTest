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
	{
		isAlive = false;
	}
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
		(otherObject->x - otherObject->width / 2 > x + width / 2) ||
		(otherObject->y - otherObject->height > y + height / 2))
	{
		return false;
	}
	return true;

}

bool GameObject::CheckCollision()
{
	int left = (int)(x - width / 2)+20;
	int top = (int)(y - height / 2)+20;
	int right = (int)(x + width / 2)+20;
	int bottom = (int)(y + height / 2)+20;

	BLKSTR *blockTL, *blockBL, *blockTR, *blockBR;

	blockTL = MapGetBlockInPixels(left, top);
	blockTR = MapGetBlockInPixels(right, top);
	blockBL = MapGetBlockInPixels(left, bottom);
	blockBR = MapGetBlockInPixels(right, bottom);

	if (!blockTL || !blockTR || !blockBL || !blockBR)
		return false;

	if (blockTL->user1 == 1 || blockTR->user1 == 1 || blockBL->user1 == 1 || blockBR->user1 == 1)
		return true;

	return false;
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
			while (abs(diffx) < vertdist)
			{
				x--;
				otherObject->x++;
				diffx = x - otherObject->x;
			}
		}
		if (x > otherObject->x)
		{
			while (abs(diffx) < vertdist)
			{
				x++;
				otherObject->x--;
				diffx = x - otherObject->x;
			}
		}
		if (y < otherObject->y)
		{
			while (abs(diffy) < hordist)
			{
				y--;
				otherObject->y++;
				diffy = y - otherObject->y;
			}
		}
		if (y > otherObject->y)
		{
			while (abs(diffy) < hordist)
			{
				y++;
				otherObject->y--;
				diffy = y - otherObject->y;
			}
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
	else if ((this->ID == BULLET && otherObject->ID == ENEMY) && this->getAlive())
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

void GameObject::Collided()
{
	int left = (int)(x - width / 2)+20;
	int top = (int)(y - height / 2)+20;
	int right = (int)(x + width / 2)+20;
	int bottom = (int)(y + height / 2)+20;

	BLKSTR *blockTL, *blockBL, *blockTR, *blockBR;

	blockTL = MapGetBlockInPixels(left, top);
	blockTR = MapGetBlockInPixels(right, top);
	blockBL = MapGetBlockInPixels(left, bottom);
	blockBR = MapGetBlockInPixels(right, bottom);

	if (direction_y == 1)
	{
		while (blockTR->user1 == 1 || blockTL->user1 == 1)
		{
			y++;
			int top = (int)(y - height / 2) + 20;
			blockTR = MapGetBlockInPixels(right, top);
			blockTL = MapGetBlockInPixels(left, top);
		}
	}

	if (direction_y == -1)
	{
		while (blockBR->user1 == 1 || blockBL->user1 == 1)
		{
			y--;
			bottom = (int)(y + height / 2) + 20;
			blockBR = MapGetBlockInPixels(right, bottom);
			blockBL = MapGetBlockInPixels(left, bottom);
		}
	}

	if (direction_x == 1)
	{
		while (blockTR->user1 == 1 || blockBR->user1 == 1)
		{
			x--;
			right = (int)(x + width / 2) + 20;
			blockTR = MapGetBlockInPixels(right, top);
			blockBR = MapGetBlockInPixels(right, bottom);
		}
	}
	
	if (direction_x == -1)
	{
		while (blockTL->user1 == 1 || blockBL->user1 == 1)
		{
			x++;
			left = (int)(x - width / 2) + 20;
			blockTL = MapGetBlockInPixels(left, top);
			blockBL = MapGetBlockInPixels(left, bottom);
		}
	}
	


	if (ID == BULLET)
	{
		isAlive = false;
	}
}