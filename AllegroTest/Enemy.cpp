#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Update(const bool *key)
{
	const bool fake_key[4] = { false, false, false, false };
	this->set_x_direction(0);
	if (rand() % 10 == 0)
	{
		switch (rand() % 4)
		{
			case 0:
				this->set_y(this->get_y() + this->get_y_velocity());
				this->set_y_direction(-1);
				break;
			case 1:
				this->set_y(this->get_y() - this->get_y_velocity());
				this->set_y_direction(+1);
				break;
			case 2:
				this->set_x(this->get_x() - this->get_x_velocity());
				this->set_x_direction(-1);
				break;
			case 3:
				this->set_x(this->get_x() + this->get_x_velocity());
				this->set_x_direction(1);
				break;
		}
	}
	GameObject::Update(fake_key);
}

void Enemy::Draw()
{
	const float image_width = 40;
	const float image_height = 56;
	float start_image_x = 0;
	float start_image_y = 0;

	//Draw the image. Center it on the x and y coordinates.
	if (this->get_x_direction() == 0)
	{
		start_image_x = 0;
		start_image_y = 0;
	}
	else if (this->get_x_direction() == -1)
	{
		start_image_x = 0;
		start_image_y = 1 * image_height;
	}
	else if (this->get_x_direction() == 1)
	{
		start_image_x = 0;
		start_image_y = 2 * image_height;
	}

	al_draw_bitmap_region(image, start_image_x, start_image_y, image_width, image_height,
		this->get_x() - image_width / 2, this->get_y() - image_height / 2, 0);
}