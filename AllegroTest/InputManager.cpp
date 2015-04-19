#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	al_get_keyboard_state(&keyState);
}

bool InputManager::IsKeyPressed(ALLEGRO_EVENT ev, int key)
{
	if (ev.type = ALLEGRO_EVENT_KEY_DOWN)
	{
		if (ev.keyboard.keycode == key)
			return true;
	}
	return false;
}

bool InputManager::IsKeyReleased(ALLEGRO_EVENT ev, int key)
{
	if (ev.type = ALLEGRO_EVENT_KEY_UP)
	{
		if (ev.keyboard.keycode == key)
			return true;
	}
	return false;
}

bool InputManager::IsKeyDown(int key)
{
	if (al_key_down(&keyState, key))
		return true;
	return false;
}