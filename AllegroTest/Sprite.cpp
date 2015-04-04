#include "Sprite.h"


Sprite::Sprite(int maxFrame, int curFrame, int frameCount, int frameDelay, int frameWidth, int frameHeight, int animationColumns,
	int animationRows, int curRow, int animationDirection, GameObject *owner, ALLEGRO_BITMAP *image, int scaleFactor)
{
	Sprite::maxFrame = maxFrame;
	Sprite::curFrame = curFrame;
	Sprite::frameCount = frameCount;
	Sprite::frameDelay = frameDelay;
	Sprite::frameWidth = frameWidth;
	Sprite::frameHeight = frameHeight;
	Sprite::animationColumns = animationColumns;
	Sprite::animationRows = animationRows;
	Sprite::curRow = curRow;
	Sprite::animationDirection = animationDirection;

	Sprite::owner = owner;
	Sprite::image = image;
	Sprite::scaleFactor = scaleFactor;
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
			curFrame = 0;
		else if (curFrame <= 0)
			curFrame = maxFrame - 1;

		frameCount = 0;
	}

	if (owner->get_x_direction() == 0)
	{
		curRow = 0;
	}
	else if (owner->get_x_direction() == -1)
	{
		curRow = 1;
	}
	else if (owner->get_x_direction() == 1)
	{
		curRow = 2;
	}
}

void Sprite::Draw()
{
	//al_draw_bitmap_region(image, curFrame*frameWidth, curRow*frameHeight, frameWidth, frameHeight, owner->get_x(), owner->get_x(), 0);

	al_draw_scaled_bitmap(image, curFrame*frameWidth, curRow*frameHeight, frameWidth, frameHeight,
		owner->get_x() - frameWidth / 2 * scaleFactor, owner->get_y() - frameHeight / 2 * scaleFactor,
		frameWidth*scaleFactor, frameHeight*scaleFactor, 0);
}