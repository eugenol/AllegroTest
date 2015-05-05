#include "Bullet.h"


Bullet::Bullet(float x, float y, float velocity_x, float velocity_y, int direction_x, int direction_y)
	: GameObject(x, y, velocity_x, velocity_y, 3, 3, 0, BULLET, NULL)
{
	GameObject::direction_x = direction_x;
	GameObject::direction_y = direction_y;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (isAlive)
	{
		x += velocity_x*direction_x;
		y += velocity_y*direction_y;
	}

	if ((x <= 0+width/2) ||( x >= 800-width/2) || (y <= 0 +height/2) || (y >= 600 - height/2))
	{ 
		isAlive = false;
		x = 0;
		y = 0;
	}
		
}

void Bullet::Draw()
{
	al_draw_filled_circle(x, y, 3, al_map_rgb(255, 255, 255));
}

void Bullet::setImage(ALLEGRO_BITMAP *image)
{

}