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
	al_draw_filled_circle(this->get_x(), this->get_y(), this->get_size(), al_map_rgb(255, 255, 255));
}
