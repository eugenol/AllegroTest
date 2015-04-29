#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"

class Player : public GameObject
{
	ALLEGRO_BITMAP *image;
	Sprite *sprite;

public:
	Player();
	~Player();

	void setImage(ALLEGRO_BITMAP *image);
	void Update();
	void Draw();

};

