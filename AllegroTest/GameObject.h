#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//Consts
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float FPS = 60;
enum KEYS{ KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D };

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
	int get_y_direction() { return direction_y; }

	virtual void Update(const bool *key);

	virtual void Draw() = 0;

};

