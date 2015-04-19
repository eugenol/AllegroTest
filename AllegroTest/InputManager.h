#pragma once

#include <allegro5/allegro.h>

class InputManager
{
private:
	ALLEGRO_KEYBOARD_STATE keyState;
public:
	InputManager();
	~InputManager();

	void Update();

	bool IsKeyPressed(ALLEGRO_EVENT ev, int key);
	bool IsKeyReleased(ALLEGRO_EVENT ev, int key);

	bool IsKeyDown(int key);
};

