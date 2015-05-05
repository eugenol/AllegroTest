#pragma once
#include "GameObject.h"
class HUD
{
private:
	GameObject *owner;
public:
	HUD(GameObject *owner);
	~HUD();
	void Update();
	void Draw();
};

