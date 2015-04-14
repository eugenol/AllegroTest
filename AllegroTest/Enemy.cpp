#include "Enemy.h"
#include <math.h>



Enemy::Enemy()
{
	srand(time(NULL));
	changeState(IDLING);
}


Enemy::~Enemy()
{
	delete sprite;
}

void Enemy::setImage(ALLEGRO_BITMAP *image)
{
	//Move this to the constructor
	Enemy::image = image;
	sprite = new Sprite(4, 0, 0, 5, 40, 56, 4, 4, 0, 1, this, image,2);
}

void Enemy::changeState(int newState)
{
	currState = newState;

	if (currState == IDLING)
	{ 
		this->set_x_velocity(1);
		this->set_y_velocity(1);
	}
	else if (currState == CHASING)
	{
		this->set_x_velocity(4);
		this->set_y_velocity(4);
	}
	else if (currState == SEARCHING)
	{
		this->set_x_velocity(2);
		this->set_y_velocity(2);
	}
	else if (currState == RETREATING)
	{}

}

void Enemy::Update(Player* player)
{
	if (currState == IDLING)
	{
		if (visible_distance > distanceToPlayer(player))
		{
			changeState(CHASING);

			int y_direction = sin(angleToPlayer(player)) < 0 ? -1 : 1;
			int x_direction = cos(angleToPlayer(player)) < 0 ? -1 : 1;
			this->set_y_direction(y_direction);
			this->set_x_direction(x_direction);
			this->set_x(this->get_x() + this->get_x_velocity()*this->get_x_direction());
			this->set_y(this->get_y() + this->get_y_velocity()*this->get_y_direction());

			last_player_x = player->get_x();
			last_player_y = player->get_y();
		}
		else
		{
			Loiter();
		}
	}
	else if (currState == CHASING)
	{
		if (visible_distance < distanceToPlayer(player))
		{
			//if enemy just lost sight of the player, move in last known direction
			changeState(SEARCHING);
			
			float deltax = last_player_x - this->get_x();
			float deltay = last_player_y - this->get_y();
			float angle = atan2(deltay, deltax);

			int y_direction = sin(angle) < 0 ? -1 : 1;
			int x_direction = cos(angle) < 0 ? -1 : 1;
			this->set_y_direction(y_direction);
			this->set_x_direction(x_direction);
			this->set_x(this->get_x() + this->get_x_velocity()*this->get_x_direction());
			this->set_y(this->get_y() + this->get_y_velocity()*this->get_y_direction());

			//if the player is in sight again, start chasing him
			if (visible_distance > distanceToPlayer(player))
				changeState(CHASING);
		}
		else
		{
			//Move in direction of player
			int y_direction = sin(angleToPlayer(player)) < 0 ? -1 : 1;
			int x_direction = cos(angleToPlayer(player)) < 0 ? -1 : 1;
			this->set_y_direction(y_direction);
			this->set_x_direction(x_direction);
			this->set_x(this->get_x() + this->get_x_velocity()*this->get_x_direction());
			this->set_y(this->get_y() + this->get_y_velocity()*this->get_y_direction());

			last_player_x = player->get_x();
			last_player_y = player->get_y();
		}
	}
	else if (currState == SEARCHING)
	{
		// Check if close to the last known position, if then start idling, otherwise, move to last known position
		float deltax = last_player_x - this->get_x();
		float deltay = last_player_y - this->get_y();

		if (visible_distance > distanceToPlayer(player))
		{
			changeState(CHASING);

			int y_direction = sin(angleToPlayer(player)) < 0 ? -1 : 1;
			int x_direction = cos(angleToPlayer(player)) < 0 ? -1 : 1;
			this->set_y_direction(y_direction);
			this->set_x_direction(x_direction);
			this->set_x(this->get_x() + this->get_x_velocity()*this->get_x_direction());
			this->set_y(this->get_y() + this->get_y_velocity()*this->get_y_direction());

			last_player_x = player->get_x();
			last_player_y = player->get_y();
		}
		else if (sqrt(pow(deltax, 2) + pow(deltay, 2)) > 50)
		{
			//if enemy just lost sight of the player, move in last known direction
			float angle = atan2(deltay, deltax);

			int y_direction = sin(angle) < 0 ? -1 : 1;
			int x_direction = cos(angle) < 0 ? -1 : 1;
			this->set_y_direction(y_direction);
			this->set_x_direction(x_direction);
			this->set_x(this->get_x() + this->get_x_velocity()*this->get_x_direction());
			this->set_y(this->get_y() + this->get_y_velocity()*this->get_y_direction());

			if (visible_distance > distanceToPlayer(player))
				changeState(CHASING);
		}
		else
		{
			changeState(IDLING);
			Loiter();
		}
	}
	else if (currState == RETREATING)
	{
		//Not used yet.
	}

	//Can add for enemy to head in last known direction of player.

	//bounds checking
	if (this->get_y() <= MIN_HEIGHT + this->get_height() / 2 + this->get_bound())
	{
		this->set_y(MIN_HEIGHT + this->get_height() / 2 + this->get_bound());
		this->set_y_direction(1);
	}

	//Fixed so that their feet toughes the ground
	if (this->get_y() >= MAX_HEIGHT - (this->get_height() / 2 - 2))
	{
		this->set_y(MAX_HEIGHT - (this->get_height() / 2 - 2));
		this->set_y_direction(-1);
	}

	if (this->get_x() <= MIN_WIDTH + this->get_width() / 2 + this->get_bound())
	{
		this->set_x(MIN_WIDTH + this->get_width() / 2 + this->get_bound());
		this->set_x_direction(1);
	}

	//No bound on leaving the screen
	if (this->get_x() >= MAX_WIDTH - (0 + this->get_width() / 2 + this->get_bound()))
	{
		this->set_x(MAX_WIDTH - (0 + this->get_width() / 2 + this->get_bound()));
		this->set_x_direction(-1);
	}
	//GameObject::Update(fake_key);

	sprite->Update();
}

float Enemy::distanceToPlayer(Player* player)
{
	return sqrt(pow(player->get_x() - this->get_x(), 2) + pow(player->get_y() - this->get_y(), 2));
}

float Enemy::angleToPlayer(Player* player)
{
	float deltax = player->get_x() - this->get_x();
	float deltay = player->get_y() - this->get_y();

	return atan2(deltay, deltax);
}

void Enemy::Draw()
{

	// field of view circle
	al_draw_circle(this->get_x(), this->get_y(), visible_distance, al_map_rgb(255, 0, 255),2);

	//Player Last seen position
	al_draw_circle(last_player_x, last_player_y, 50, al_map_rgb(255, 0, 0),2);
	al_draw_filled_circle(last_player_x, last_player_y, 2, al_map_rgb(255, 0, 0));

	//Draw sprite
	sprite->Draw();
}

void Enemy::Loiter()
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
}