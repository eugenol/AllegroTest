#pragma once
#include "GameObject.h"

class Sprite
{
private:
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationDirection;
	
	ALLEGRO_BITMAP *image;
public:
	Sprite();
	~Sprite();

	void Update();
	void Draw();
};

