#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy : public GameObject
{
	ALLEGRO_BITMAP *image;

	//For finite state ai
	const float visible_distance = 200;
	enum STATE{ IDLING, CHASING, RETREATING };
	int state=IDLING;
	void changeState(int newState) { state = newState; }
	float distanceToPlayer(Player * player);
	float angleToPlayer(Player * player);
	void Loiter();
public:
	Enemy();
	~Enemy();
	
	void setImage(ALLEGRO_BITMAP *image) { Enemy::image = image; }
	void Update(Player * player);
	void Draw();


};

