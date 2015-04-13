#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdlib.h>
#include <time.h>

//Consts
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MIN_HEIGHT = -600;
const int MAX_HEIGHT = 1200;
const int MIN_WIDTH = -800;
const int MAX_WIDTH =1600;

const float FPS = 60;
enum KEYS{ KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE };

class GameObject
{
	float x;
	float y;
	float height;
	float width;
	float velocity_x;
	float velocity_y;
	float bound;
	int direction_x;
	int direction_y;
public:
	GameObject();
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

	virtual void Update(const bool *key);

	virtual void Draw() = 0;

};

