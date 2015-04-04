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
	GameObject::Update(key);
	sprite->Update();
}

void Player::Draw()
{
	sprite->Draw();
}
