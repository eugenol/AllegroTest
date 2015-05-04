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

void cameraUpdate(float *cameraPosition, float x, float y, int width, int height);
static void*loading_thread(ALLEGRO_THREAD*load, void*data);
ALLEGRO_BITMAP * loadMap();

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

	//Intitialize addons
	//Fonts
	al_init_font_addon();
	al_init_ttf_addon();

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
			al_draw_text(font_pirulen_18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Loading   ");
		else if (a < 600)
			al_draw_text(font_pirulen_18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Loading.  ");
		else if (a <900)
			al_draw_text(font_pirulen_18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Loading.. ");
		else if (a < 1200)
			al_draw_text(font_pirulen_18, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTER, "Loading...");
		a++; 
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	al_destroy_thread(loading);

	//Get loaded data
	//display = data.display;
	event_queue = data.event_queue;
	timer = data.timer;
	player_image = data.player_image;
	enemy_image = data.enemy_image;
	//background = data.background;
	background = data.map;
	bg_music = data.bg_music;
	bgInstance = data.bgInstance;
	laser_sound = data.laser_sound;
	laser_sound_instance = data.laser_sound_instance;
	cursorImage = data.cursorImage;
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

			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->Update();

			for (std::list<GameObject*>::iterator iter1 = objects.begin(); iter1 != objects.end(); iter1++)
			{
				for (std::list<GameObject*>::iterator iter2 = objects.begin(); iter2 != objects.end(); iter2++)
				{
					bool collision = false;
					if (iter1 != iter2)
						collision = (*iter1)->CheckCollision(*iter2);
					if (collision)
						(*iter1)->Collided(*iter2);
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
				Enemy *enemyPtr = new Enemy(rand() % 801, rand() % 601, 3, 3, 40, 56, 1, enemy_image);
				EntityManager::getInstance().AddEntity(enemyPtr);
			}

		}


		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty befor redrawing.
		{
			redraw = false;

			//al_clear_to_color(al_map_rgb(0, 0, 0));
			///using a bitmap as a background kills the framerate. Draw lines to see motion effect.
			//for (int i = -100; i < 100; i++)
			//	al_draw_line(i*75, -600, i*75, 1200, al_map_rgb(255, 0, 255), 2);
			//al_draw_filled_rectangle(0, 0, 1200, 600, al_map_rgb(255, 0, 255));
			//al_draw_bitmap(background, 0, 0, NULL);
			//al_draw_bitmap(background, 1067, 0, NULL);

			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->Draw();


			al_draw_text(font_pirulen_24, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTER, "IRON MAN vs. HULK");
			al_draw_textf(font_pirulen_18, al_map_rgb(255, 0, 0), SCREEN_WIDTH/2 + cameraPosition[0] ,30, ALLEGRO_ALIGN_CENTER, "%i fps", gameFPS);
			
			if (player->getHealth() >= 0 && player->getHealth() <= 100)
			{
				//al_draw_textf(font_pirulen_18, al_map_rgb(255, 0, 0), SCREEN_WIDTH - 100, SCREEN_HEIGHT - 20, ALLEGRO_ALIGN_CENTER, "Health: %i", player->getHealth());
				al_draw_rectangle(SCREEN_WIDTH - 116, SCREEN_HEIGHT - 20, SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10, al_map_rgba(255, 0, 0, 100), 2);
				al_draw_filled_rectangle(SCREEN_WIDTH - 113, SCREEN_HEIGHT - 17, SCREEN_WIDTH - 113 + player->getHealth(), SCREEN_HEIGHT - 13, al_map_rgba(255, 0, 0,50));
			}
			
			
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

	Data->player = new Player(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 5, 5, 32, 48, 1, Data->player_image, Data->laser_sound_instance);
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
	Enemy *enemy1 = new Enemy(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, 3, 40, 56, 1, Data->enemy_image);
	EntityManager::getInstance().AddEntity(enemy1);

	Enemy *enemy2 = new Enemy(3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 3, 3, 40, 56, 1, Data->enemy_image);
	EntityManager::getInstance().AddEntity(enemy2);

	al_rest(2.5);

	//Load Map
	Data->map = loadMap();
	al_set_target_bitmap(al_get_backbuffer(Data->display));
	//Mouse cursor
	al_set_mouse_cursor(Data->display, Data->cursor);

	Data->done_loading = true;

	return NULL;
}

ALLEGRO_BITMAP * loadMap()
{
	int mapfile[40][30] = { { 0 } };
	std::string temp;
	std::stringstream tempRow;
	std::ifstream inFile("map/map.dat");
	ALLEGRO_BITMAP *tempBitmap;
	ALLEGRO_BITMAP *map;

	//Read mapfile into array
	for (int i = 0; i < 30; i++)
	{
		std::getline(inFile, temp);
		std::stringstream tempRow(temp);
		for (int j = 0; j < 40; j++)
		{
			tempRow >> mapfile[j][i];
		}
	}

	//Draw map
	map = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	al_set_target_bitmap(map);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			tempRow.str("");
			tempRow << "map/0" << mapfile[i][j] << ".png";
			temp = tempRow.str();
			tempBitmap = al_load_bitmap(temp.c_str());
			al_draw_bitmap(tempBitmap, i * 20, j * 20, 0);
			al_destroy_bitmap(tempBitmap);
		}
	}
	return map;
}