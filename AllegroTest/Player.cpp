#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
	delete sprite;
}

void Player::setImage(ALLEGRO_BITMAP *image)
{
	//Move this to the constructor
	Player::image = image; 
	sprite = new Sprite(4, 0, 0, 5, 32, 48, 4, 4, 0, 1, this, image, 2);
}

void Player::Update(const bool *key)
{
	this->set_y_direction(0);
	this->set_x_direction(0);
	float x, y, velx, vely;
	int dirx, diry;

	x = this->get_x();
	y = this->get_y();
	velx = this->get_x_velocity();
	vely = this->get_y_velocity();
	dirx = this->get_x_direction();
	diry = this->get_y_direction();

	//update position
	if (key[KEY_UP])
	{
		y -= vely;
		diry = 1;
	}
	if (key[KEY_DOWN])
	{
		y += vely;
		diry = -1;
	}

	if (key[KEY_LEFT])
	{
		x -= velx;
		dirx = -1;
	}

	if (key[KEY_RIGHT])
	{
		x += velx;
		dirx = +1;
	}

	this->set_x(x);
	this->set_y(y);
	this->set_x_direction(dirx);
	this->set_y_direction(diry);

	GameObject::Update(key);
	sprite->Update();
}

void Player::Draw()
{
	sprite->Draw();
}
