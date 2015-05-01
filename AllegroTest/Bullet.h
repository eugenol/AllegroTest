#pragma once
#include "GameObject.h"
class Bullet :
	public GameObject
{
public:
	Bullet(float x, float y, float velocity_x, float velocity_y, int direction_x, int direction_y);
	~Bullet();

	virtual void Update();
	virtual void Draw();
};

