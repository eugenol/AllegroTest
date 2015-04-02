#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Update(const bool *key)
{
	GameObject::Update(key);
}

void Player::Draw()
{
	float image_width = 32;
	float image_height = 48;
	//Draw the image. Center it on the x and y coordinates.
	al_draw_bitmap_region(image, 0, 0, 32, 48, this->get_x() - image_width / 2, this->get_y() - image_height/2, 0);
}
