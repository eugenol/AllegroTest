#pragma once
#include "GameObject.h"
#include "Player.h"
class Enemy : public GameObject
{
	ALLEGRO_BITMAP *image;

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
	
	void setImage(ALLEGRO_BITMAP *image) { Enemy::image = image; }
	void Update(Player * player);
	void Draw();


};

