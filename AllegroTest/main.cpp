/*
//Moved to more global file
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
*/
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <list>
#include <fstream>
#include <string>
#include <sstream>

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "InitData.h"
#include "mappy_a5.h"

void cameraUpdate(float *cameraPosition, float x, float y, int width, int height);
static void*loading_thread(ALLEGRO_THREAD*load, void*data);

int main(int argc, char **argv)
{
	//Consts
	//const int SCREEN_WIDTH = 800;
	//const int SCREEN_HEIGHT = 600;
	//const float FPS = 60;

	InitData data;
	bool game_done = false;
	bool redraw = false;
	srand(time(NULL));

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	float cameraPosition[2] = { 0, 0 };

	std::list<GameObject*> objects;

	EntityManager::getInstance().getEntityList(&objects);

	//Intitializations
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	//Fonts
	ALLEGRO_FONT *font_pirulen_18 = NULL;
	ALLEGRO_FONT *font_pirulen_24 = NULL;
	ALLEGRO_FONT *font_pirulen_72 = NULL;
	//Images
	ALLEGRO_BITMAP *player_image = NULL;
	ALLEGRO_BITMAP *enemy_image = NULL;
	ALLEGRO_BITMAP *background = NULL; //Terribly slow when using a background image.
	//Background music
	ALLEGRO_SAMPLE *bg_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE *bgInstance = NULL;
	//Gun sound
	ALLEGRO_SAMPLE *laser_sound = NULL;
	ALLEGRO_SAMPLE_INSTANCE *laser_sound_instance = NULL;
	//Mouse cursor
	ALLEGRO_BITMAP *cursorImage = NULL;
	ALLEGRO_MOUSE_CURSOR *cursor = NULL;
	//Camera
	ALLEGRO_TRANSFORM camera;
	//Player
	Player *player = NULL;
	//Thread
	ALLEGRO_THREAD *loading = NULL;
	
	//Intitalize allegro
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to initialize",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Display
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//al_set_new_display_flags(ALLEGRO_NOFRAME);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_window_title(display, "IRON MAN vs. HULK");
	data.display = display;

	//Intitialize addons
	//Fonts
	al_init_font_addon();
	al_init_ttf_addon();
	
	if (MapLoad("testmap.FMP", 1))
		return -5;

	//Create Font
	font_pirulen_72 = al_load_ttf_font("pirulen.ttf", 72, 0);
	font_pirulen_24 = al_load_ttf_font("pirulen.ttf", 24, 0);
	font_pirulen_18 = al_load_ttf_font("pirulen.ttf", 18, 0);
	if (!font_pirulen_72 && !font_pirulen_18 && !font_pirulen_24)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the font",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	loading = al_create_thread(loading_thread, &data);
	al_start_thread(loading);
	while (!data.done_loading)
	{
		static int  a = 0;

		if (a >= 1200)
			a = 0;

		if (a < 300)
			al_draw_text(font_pirulen_72, al_map_rgb(255, 255, 255), 150, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading   ");
		else if (a < 600)
			al_draw_text(font_pirulen_72, al_map_rgb(255, 255, 255), 150, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading.  ");
		else if (a <900)
			al_draw_text(font_pirulen_72, al_map_rgb(255, 255, 255), 150, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading.. ");
		else if (a < 1200)
			al_draw_text(font_pirulen_72, al_map_rgb(255, 255, 255), 150, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_LEFT, "Loading...");
		a++; 
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_thread(loading);

	//Get loaded data
	//display = data.display;
	event_queue = data.event_queue;
	timer = data.timer;
	player_image = al_clone_bitmap(data.player_image); //NB have to do this
	enemy_image = al_clone_bitmap(data.enemy_image); //NB have to do this
	background = al_clone_bitmap(data.background); //NB have to do this
	bg_music = data.bg_music;
	bgInstance = data.bgInstance;
	laser_sound = data.laser_sound;
	laser_sound_instance = data.laser_sound_instance;
	cursorImage = al_clone_bitmap(data.cursorImage);
	cursor = data.cursor;
	player = data.player;
	

	//Checks
	if (!timer)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	if (!event_queue)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the event queue",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}


	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	//Start playing the music
	//al_play_sample_instance(bgInstance);//turned off for now.. it can get irritating!!

	//keep track of framerate
	gameTime = al_get_time();

	al_start_timer(timer); //Start the timer

	//Game Loop
	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//Capture key input
		InputManager::getInstance().getInput(ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			redraw = true;

			//Updating
			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->Update();

			////Colission Detection with Map elements
			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
			{
				//if ((*iter)->CheckCollision())
				//	(*iter)->Collided();

				//call colission routine
			}

			//Colission Detection with objects
			for (std::list<GameObject*>::iterator iter1 = objects.begin(); iter1 != objects.end(); iter1++)
			{
				for (std::list<GameObject*>::iterator iter2 = objects.begin(); iter2 != objects.end(); iter2++)
				{
					if (iter1 != iter2) //Cant collide with yourself!
					{
						if ((*iter1)->CheckCollision(*iter2)) //Did you collide?
							(*iter1)->Collided(*iter2); //Do something about it.
					}					
				}
			}

			EntityManager::getInstance().UpdateList();

			//cameraUpdate(cameraPosition, player->get_x(), player->get_y(), player->get_width(), player->get_height());
			//al_identity_transform(&camera);
			//al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
			//al_use_transform(&camera);
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		//Escape key pressed? exit game
		if (InputManager::getInstance().isKeyPressed(ESCAPE))
			game_done = true;

		// For testing, spawn random hulk
		if (InputManager::getInstance().isKeyPressed(SPACE))
		{
			if (rand() % 5 == 0) //Dont let too many spawn at a time;
			{
				Enemy *enemyPtr = new Enemy(rand() % 700 + 50, rand() % 500 +50, 3, 3, 56, 40, 1, enemy_image);
				EntityManager::getInstance().AddEntity(enemyPtr);
			}

		}


		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty befor redrawing.
		{
			redraw = false;

			//al_draw_bitmap(background, 0, 0, 0);
			MapDrawBG(20, 20, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->Draw();


			al_draw_text(font_pirulen_24, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTER, "IRON MAN vs. HULK");
			al_draw_textf(font_pirulen_18, al_map_rgb(255, 0, 0), SCREEN_WIDTH/2 + cameraPosition[0] ,30, ALLEGRO_ALIGN_CENTER, "%i fps", gameFPS);		
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	//Destroy
	//if (player)
	//	delete player;

	al_destroy_bitmap(background);
	al_destroy_sample_instance(bgInstance);
	al_destroy_sample(bg_music);
	al_destroy_bitmap(enemy_image);
	al_destroy_bitmap(player_image);
	al_destroy_font(font_pirulen_72);
	al_destroy_font(font_pirulen_24);
	al_destroy_font(font_pirulen_18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	al_destroy_bitmap(cursorImage);
	al_destroy_mouse_cursor(cursor);
	al_destroy_sample_instance(laser_sound_instance);
	al_destroy_sample(laser_sound);

	//Unload map
	MapFreeMem();

	return 0;
}

void cameraUpdate(float *cameraPosition, float x, float y, int width, int height)
{
	cameraPosition[0] = -(SCREEN_WIDTH / 2) + (x /*+ width/2*/);
	cameraPosition[1] = -(SCREEN_HEIGHT / 2) + (y /*+ height/2*/);

	//if (cameraPosition[0] < -800)
	//	cameraPosition[0] = -800;
	//if (cameraPosition[0] > 1600)
	//	cameraPosition[0] = 1600;
	//if (cameraPosition[1] < -600)
	//	cameraPosition[1] = 600;
	//if (cameraPosition[1] > 1200)
	//	cameraPosition[1] = 1200;
}

static void*loading_thread(ALLEGRO_THREAD*load, void*data)
{
	InitData *Data = (InitData*)data;
	
	//Intitialize addons
	al_install_keyboard();		//Keyboard
	al_install_mouse();			//Mouse
	al_init_primitives_addon(); //Primitives (shapes)
	al_init_image_addon();		//Images
	al_install_audio();			//Audio
	al_init_acodec_addon();		//Audio

	//Set up cursor Image
	Data->cursorImage = al_load_bitmap("target.png");
	al_convert_mask_to_alpha(Data->cursorImage, al_map_rgb(255, 255, 255));
	Data->cursor = al_create_mouse_cursor(Data->cursorImage, 16, 16);

	//Load images
	Data->player_image = al_load_bitmap("ironman.png");			//Player image
	Data->enemy_image = al_load_bitmap("hulk.png");				//Enemy Image
	Data->background = al_load_bitmap("city_background.png");	//Load Background

	//Sounds & Musics
	al_reserve_samples(2);
	Data->bg_music = al_load_sample("A Night of Dizzy Spells.ogg");
	Data->bgInstance = al_create_sample_instance(Data->bg_music);
	al_set_sample_instance_playmode(Data->bgInstance, ALLEGRO_PLAYMODE_LOOP);
	//can set other properties here such as speed, gain, etc..
	al_attach_sample_instance_to_mixer(Data->bgInstance, al_get_default_mixer());

	Data->laser_sound = al_load_sample("laser.wav");
	Data->laser_sound_instance = al_create_sample_instance(Data->laser_sound);
	al_set_sample_instance_playmode(Data->laser_sound_instance, ALLEGRO_PLAYMODE_ONCE);
	al_set_sample_instance_speed(Data->laser_sound_instance, 5.0);
	//can set other properties here such as speed, gain, etc..
	al_attach_sample_instance_to_mixer(Data->laser_sound_instance, al_get_default_mixer());

	Data->player = new Player(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 5, 5, 48, 32, 1, Data->player_image, Data->laser_sound_instance);
	EntityManager::getInstance().AddEntity(Data->player);
	Enemy::getPlayer(Data->player);

	//Create Timer
	Data->timer = al_create_timer(1.0 / FPS);
	//Create Event Queue
	Data->event_queue = al_create_event_queue();

	//Register Event Sources
	al_register_event_source(Data->event_queue, al_get_display_event_source(Data->display)); //display events
	al_register_event_source(Data->event_queue, al_get_timer_event_source(Data->timer)); // timer events
	al_register_event_source(Data->event_queue, al_get_keyboard_event_source()); // keyboard events
	al_register_event_source(Data->event_queue, al_get_mouse_event_source()); // mouse events
	
	//Create Enemies
	Enemy *enemy1 = new Enemy(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, 3, 56, 40, 1, Data->enemy_image);
	EntityManager::getInstance().AddEntity(enemy1);

	Enemy *enemy2 = new Enemy(3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 3, 3, 56, 40, 1, Data->enemy_image);
	EntityManager::getInstance().AddEntity(enemy2);

	al_rest(2.5);

	//Mouse cursor
	al_set_mouse_cursor(Data->display, Data->cursor);

	Data->done_loading = true;

	return NULL;
}