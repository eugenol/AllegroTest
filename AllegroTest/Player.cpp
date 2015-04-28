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
	
	direction_y = 0;
	direction_x = 0;
	//update position
	if (key[KEY_UP])
	{
		y -= velocity_y;
		direction_y = 1;
	}
	if (key[KEY_DOWN])
	{
		y += velocity_y;
		direction_y = -1;
	}

	if (key[KEY_LEFT])
	{
		x -= velocity_x;
		direction_x = -1;
	}

	if (key[KEY_RIGHT])
	{
		x += velocity_x;
		direction_x = +1;
	}
	GameObject::Update(key);
	sprite->Update();
}

void Player::Draw()
{
	sprite->Draw();
}
