#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"

class Player : public GameObject
{
	ALLEGRO_BITMAP *image;
	Sprite *sprite;
	InputManager input;

public:
	Player();
	~Player();

	void setImage(ALLEGRO_BITMAP *image);
	void Update(ALLEGRO_EVENT ev);
	void Draw();

};

