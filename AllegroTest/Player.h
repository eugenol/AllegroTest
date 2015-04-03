#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	ALLEGRO_BITMAP *image;
	int currframeRow;
	int currframeCol;
public:
	Player();
	~Player();

	void setImage(ALLEGRO_BITMAP *image) { Player::image = image; }
	void setFrameRow(int row) {currframeRow = row;}
	void setFrameColumn(int column) { currframeCol = column;}
	void Update(const bool *key);
	void Draw();

};

