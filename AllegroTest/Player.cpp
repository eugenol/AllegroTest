#include "Player.h"


Player::Player(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, ALLEGRO_BITMAP *image)
	: GameObject(x, y, velocity_x, velocity_y, height, width, bound, PLAYER, image)
{
	setImage(image);
	ID = PLAYER;
}


Player::~Player()
{
	delete sprite;
}

void Player::setImage(ALLEGRO_BITMAP *image)
{
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
	
	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{

		if (shootDelay == 0||shootDelay > 6)
		{
			shootDelay = 0;
			Shoot();
		}
		shootDelay++;
		
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

void Player::Shoot()
{
	float target_x = InputManager::getInstance().getMouseX();
	float target_y = InputManager::getInstance().getMouseY();

	//find angle to target
	float deltax = target_x - x;
	float deltay = target_y - y;
	float angleToTarget = atan2(deltay, deltax);

	float velocity_x = abs(cos(angleToTarget) * 10);
	float velocity_y = abs(sin(angleToTarget) * 10);

	int y_direction = sin(angleToTarget) < 0 ? -1 : 1;
	int x_direction = cos(angleToTarget) < 0 ? -1 : 1;

	Bullet *bulletPtr = new Bullet(x, y, velocity_x, velocity_y, x_direction, y_direction);

	EntityManager::getInstance().AddEntity(bulletPtr);
}