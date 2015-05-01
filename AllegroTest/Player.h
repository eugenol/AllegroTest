#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include <cmath>
#include "EntityManager.h"

class Player : public GameObject
{
private:
	Sprite *sprite;
	void Shoot();
public:
	Player(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, ALLEGRO_BITMAP *image);
	~Player();

	virtual void setImage(ALLEGRO_BITMAP *image);
	virtual void Update();
	virtual void Draw();

};

