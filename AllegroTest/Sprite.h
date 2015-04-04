#pragma once
#include "GameObject.h"

class Sprite //: public GameObject
{
private:
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int curRow;
	int animationDirection;
	int scale;
	
	GameObject *owner;
	ALLEGRO_BITMAP *image;
public:
	Sprite(int maxFrame, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int animationColumns,
		int animationRows, int curRow, int animationDirection, GameObject *owner, ALLEGRO_BITMAP *image);
	~Sprite();

	void Update();
	void Draw();
};

