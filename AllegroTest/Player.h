#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"

class Player : public GameObject
{
private:
	Sprite *sprite;
public:
	Player(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, ALLEGRO_BITMAP *image);
	~Player();

	virtual void setImage(ALLEGRO_BITMAP *image);
	virtual void Update();
	virtual void Draw();

};

