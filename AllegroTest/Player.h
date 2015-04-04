#pragma once
#include "GameObject.h"
#include "Sprite.h"

class Player : public GameObject
{
	ALLEGRO_BITMAP *image;
	Sprite *sprite;

public:
	Player();
	~Player();

	void setImage(ALLEGRO_BITMAP *image);
	void Update(const bool *key);
	void Draw();

};

