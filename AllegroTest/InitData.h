#ifndef INITDATA_H
#define INITDATA_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Player.h"

class InitData
{
public:
	InitData();
	~InitData();

	//Intitializations
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	//Images
	ALLEGRO_BITMAP *player_image = NULL;
	ALLEGRO_BITMAP *enemy_image = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *map = NULL;
	//Background music
	ALLEGRO_SAMPLE *bg_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE *bgInstance = NULL;
	//Gun sound
	ALLEGRO_SAMPLE *laser_sound = NULL;
	ALLEGRO_SAMPLE_INSTANCE *laser_sound_instance = NULL;
	//Mouse cursor
	ALLEGRO_BITMAP *cursorImage = NULL;
	ALLEGRO_MOUSE_CURSOR *cursor = NULL;
	Player *player = NULL;

	bool done_loading;
};
#endif
