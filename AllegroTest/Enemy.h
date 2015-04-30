#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Sprite.h"

class Enemy : public GameObject
{
private:
	Sprite *sprite;
protected:
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
	Enemy(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, ALLEGRO_BITMAP *image);
	~Enemy();
	
	virtual void setImage(ALLEGRO_BITMAP *image);
	virtual void Update();
	virtual void Draw();
	static void getPlayer(Player *player);
};