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
	int scaleFactor;
	bool isIdle;
	
	GameObject *owner;
	ALLEGRO_BITMAP *image;
public:
	Sprite(int maxFrame, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int animationColumns,
		int animationRows, int curRow, int animationDirection, GameObject *owner, ALLEGRO_BITMAP *image, int scaleFactor = 1);
	~Sprite();

	void Update();
	void Draw();
};

