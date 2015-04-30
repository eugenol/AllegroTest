#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Sprite.h"

class Enemy : public GameObject
{
protected:
	ALLEGRO_BITMAP *image;
	Sprite *sprite;

	//For finite state ai
	const float visible_distance = 200;
	enum STATE{ IDLING, CHASING, SEARCHING, RETREATING, HUNTING};
	int currState = IDLING;
	void changeState(int newState);
	float distanceToPlayer(Player * player);
	float angleToPlayer(Player * player);
	float last_player_x;
	float last_player_y;
	void Loiter();
	static Player *m_player;
public:
	Enemy();
	~Enemy();
	
	void setImage(ALLEGRO_BITMAP *image);
	void Update();
	void Draw();
	static void getPlayer(Player *player);
};