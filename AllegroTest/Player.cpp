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
	const float image_width = al_get_bitmap_width(image) / 4;
	const float image_height = al_get_bitmap_height(image) / 4;;
	float start_image_x = 0;
	float start_image_y = 0;

	//Draw the image. Center it on the x and y coordinates.
	if (this->get_x_direction() == 0)
	{
		currframeRow = 0;
	}
	else if (this->get_x_direction() == -1)
	{
		currframeRow = 1;
	}
	else if (this->get_x_direction() == 1)
	{
		currframeRow = 2;
	}
	//Causes tooo much flickering
	/*
	if (currframeCol < 4)
		currframeCol++;
	else
		currframeCol = 0;
	*/

	//al_draw_bitmap_region(image,currframeCol*image_width , currframeRow*image_height, image_width, image_height,
	//	this->get_x() - image_width / 2, this->get_y() - image_height / 2, 0);

	al_draw_scaled_bitmap(image, currframeCol*image_width, currframeRow*image_height, image_width, image_height,
		this->get_x() - image_width, this->get_y() - image_height, image_width * 2, image_height*2, 0);
}
