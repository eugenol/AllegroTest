#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "mappy_A5.h"
//#include "Sprite.h"

//Consts
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MIN_HEIGHT = -600;
const int MAX_HEIGHT = 1200;
const int MIN_WIDTH = -800;
const int MAX_WIDTH =1600;

const float FPS = 60;

class GameObject
{
protected:
	float x;
	float y;
	float height;
	float width;
	float velocity_x;
	float velocity_y;
	float bound;
	int direction_x;
	int direction_y;	
	int ID;
	int health;
	bool isAlive;
	ALLEGRO_BITMAP *image;
	//Sprite *sprite;
	enum OBJECT_ID{PLAYER,ENEMY, BULLET};
public:
	GameObject(float x, float y, float velocity_x, float velocity_y, float height, float width, float bound, int ID, ALLEGRO_BITMAP *image);
	~GameObject();

	//Accessors and Mutators
	float get_x() { return x; }
	void set_x(float x) { GameObject::x = x; }

	float get_y() { return y; }
	void set_y(float y) { GameObject::y = y; }

	float get_x_velocity() { return velocity_x; }
	void set_x_velocity(float velocity_x) { GameObject::velocity_x = velocity_x; }

	float get_y_velocity() { return velocity_y; }
	void set_y_velocity(float velocity_y) { GameObject::velocity_y = velocity_y; }

	float get_width() { return width; }
	void set_width(float width) { GameObject::width = width; }

	float get_height() { return height; }
	void set_height(float height) { GameObject::height = height; }

	float get_bound() { return bound; }
	void set_bound(float bound) { GameObject::bound = bound; }

	int get_x_direction() { return direction_x; }
	void set_x_direction(int direction_x) { GameObject::direction_x = direction_x; }
	int get_y_direction() { return direction_y; }
	void set_y_direction(int direction_y) { GameObject::direction_y = direction_y; }

	bool getAlive() { return isAlive; }
	int getHealth() { return health; }

	virtual void Update() = 0;
	virtual void setImage(ALLEGRO_BITMAP *image) = 0;
	virtual void Draw() = 0;

	bool CheckCollision(GameObject *otherObject);
	bool CheckCollision();
	//void virtual Collided(int objectID);
	void virtual Collided(GameObject *otherObject);
	void virtual Collided();
	//bool Collidable();

};

