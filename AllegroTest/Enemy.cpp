#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Update(const bool *key)
{
	// Move
	this->set_y(this->get_y() + this->get_y_velocity()*this->get_y_direction());
	this->set_x(this->get_x() + this->get_x_velocity()*this->get_x_direction());

	//Choose new direction

	if (rand() % 80 == 0)
	{
		switch (rand() % 2)
		{
		case 0:
			{
				switch (rand() % 3)
				{
				case 0:
					this->set_y_direction(-1);
					break;
				case 1:
					this->set_y_direction(+1);
					break;
				case 2:
					this->set_x_direction(0);
					break;
				}
			}
			break;
		case 1:
			{
				switch (rand() % 3)
				{
				case 0:
					this->set_x_direction(-1);
					break;
				case 1:
					this->set_x_direction(+1);
					break;
				case 2:
					this->set_x_direction(0);
					break;
				}
			}
			break;
		}
	}
	//bounds checking
	if (this->get_y() <= 0 + this->get_height()/ 2 + this->get_bound())
	{
		this->set_y(0 + this->get_height() / 2 + this->get_bound());
		this->set_y_direction(1);
	}

	//Fixed so that their feet toughes the ground
	if (this->get_y() >= SCREEN_HEIGHT - (this->get_height() / 2 - 2))
	{
		this->set_y(SCREEN_HEIGHT - (this->get_height() / 2 - 2));
		this->set_y_direction(-1);
	}

	if (this->get_x() <= 0 + this->get_width() / 2 + this->get_bound())
	{
		this->set_x(0 + this->get_width() / 2 + this->get_bound());
		this->set_x_direction(1);
	}

	if (this->get_x() >= SCREEN_WIDTH - (0 + this->get_width() / 2 + this->get_bound()))
	{
		this->set_x(SCREEN_WIDTH - (0 + this->get_width() / 2 + this->get_bound()));
		this->set_x_direction(-1);
	}
	//GameObject::Update(fake_key);
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

	//al_draw_bitmap_region(image, start_image_x, start_image_y, image_width, image_height,
	//	this->get_x() - image_width / 2, this->get_y() - image_height / 2, 0);
	
	al_draw_scaled_bitmap(image, start_image_x, start_image_y, image_width, image_height,
		this->get_x() - image_width, this->get_y() - image_height, image_width*2, image_height*2, 0);
}