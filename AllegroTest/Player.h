#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	ALLEGRO_BITMAP *image;
	bool left;
public:
	Player();
	~Player();

	void setImage(ALLEGRO_BITMAP *image) { Player::image = image; }
	void Update(const bool *key);
	void Draw();
	void setLeft(bool left) { Player::left = left; }
};

