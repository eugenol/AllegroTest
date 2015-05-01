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
	x += velocity_x*direction_x;
	y += velocity_y*direction_y;

	if (x <= 0 || x >= 800 || y <= 0 || y >= 600)
		isAlive = false;
}

void Bullet::Draw()
{
	al_draw_filled_circle(x, y, 3, al_map_rgb(255, 255, 255));
}

void Bullet::setImage(ALLEGRO_BITMAP *image)
{

}