#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	ALLEGRO_BITMAP *image;
public:
	Enemy();
	~Enemy();

	void setImage(ALLEGRO_BITMAP *image) { Enemy::image = image; }
	void Update(const bool *key);
	void Draw();
};

