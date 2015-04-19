#pragma once

#include <allegro5/allegro.h>

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool isKeyPressed();
};

