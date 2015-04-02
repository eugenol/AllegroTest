#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

//Consts
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float FPS = 60;
enum KEYS{ KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

class GameObject
{
	float x;
	float y;
	float size;
	float velocity_x;
	float velocity_y;
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

	float get_size() { return size; }
	void set_size(float size) { GameObject::size = size; }

	virtual void Update(const bool *key);

	virtual void Draw() = 0;

};

