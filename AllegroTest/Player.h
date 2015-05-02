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
	int shootDelay=0;
	ALLEGRO_SAMPLE_INSTANCE *bullet_sound;
public:
	Player(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE_INSTANCE *bullet_sound);
	~Player();

	virtual void setImage(ALLEGRO_BITMAP *image);
	virtual void Update();
	virtual void Draw();

};

