#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	ALLEGRO_BITMAP *image;
public:
	Player();
	~Player();

	void setImage(ALLEGRO_BITMAP *image) { Player::image = image; }
	void Update(const bool *key);
	void Draw();
};

