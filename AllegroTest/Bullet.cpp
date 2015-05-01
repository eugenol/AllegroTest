#include "Bullet.h"


Bullet::Bullet(float x, float y, float velocity_x, float velocity_y, int direction_x, int direction_y)
	: GameObject(x, y, velocity_x, velocity_y, height, width, bound, PLAYER, NULL)
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
}

void Bullet::Draw()
{
	al_draw_filled_circle(x, y, 3, al_map_rgb(255, 255, 255));
}