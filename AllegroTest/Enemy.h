#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Sprite.h"

class Enemy : public GameObject
{
	ALLEGRO_BITMAP *image;
	Sprite *sprite;

	//For finite state ai
	const float visible_distance = 200;
	enum STATE{ IDLING, CHASING, SEARCHING, RETREATING };
	int currState = IDLING;
	void changeState(int newState);
	float distanceToPlayer(Player * player);
	float angleToPlayer(Player * player);
	float last_player_x;
	float last_player_y;
	void Loiter();
public:
	Enemy();
	~Enemy();
	
	void setImage(ALLEGRO_BITMAP *image);
	void Update(Player * player);
	void Draw();


};

