#include "Player.h"


Player::Player()
{
	ID = PLAYER;
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

void Player::Update()
{	
	
	direction_y = 0;
	direction_x = 0;
	//update position
	if (InputManager::getInstance().isKeyPressed(UP))
	{
		y -= velocity_y;
		direction_y = 1;
	}
	if (InputManager::getInstance().isKeyPressed(DOWN))
	{
		y += velocity_y;
		direction_y = -1;
	}

	if (InputManager::getInstance().isKeyPressed(LEFT))
	{
		x -= velocity_x;
		direction_x = -1;
	}

	if (InputManager::getInstance().isKeyPressed(RIGHT))
	{
		x += velocity_x;
		direction_x = +1;
	}


	GameObject::Update();
	sprite->Update();
}

void Player::Draw()
{
	float mousex, mousey;
	mousex = InputManager::getInstance().getMouseX();
	mousey = InputManager::getInstance().getMouseY();
	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{
		al_draw_circle(mousex, mousey, 10, al_map_rgb(255, 0, 0), 2);
	}

	sprite->Draw();
}
