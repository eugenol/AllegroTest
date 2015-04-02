#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	~Player();

	void Update(const bool *key);
	void Draw();
};

