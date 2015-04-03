/*#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
*/
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <list>


#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"


int main(int argc, char **argv)
{
	//Consts
	//const int SCREEN_WIDTH = 800;
	//const int SCREEN_HEIGHT = 600;
	//const float FPS = 60;
	//enum KEYS{KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT};

	bool game_done = false;
	bool redraw = false;
	int framecount =0;
	bool key[5] = { false, false, false, false, false};
	srand(time(NULL));

	std::list<GameObject*> objects;

	//Intitializations
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font_pirulen_18 = NULL;
	ALLEGRO_FONT *font_pirulen_24 = NULL;
	ALLEGRO_FONT *font_pirulen_72 = NULL;
	ALLEGRO_BITMAP *player_image = NULL;
	ALLEGRO_BITMAP *enemy_image = NULL;
	//Background music
	ALLEGRO_SAMPLE *bg_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE *bgInstance = NULL;

	//ALLEGRO_BITMAP *background = NULL;

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
	//Keyboard
	al_install_keyboard();
	//Images & Primatives(shapes)
	al_init_primitives_addon();
	al_init_image_addon();
	//Audio
	al_install_audio();
	al_init_acodec_addon();

	//New Player Object
	player_image = al_load_bitmap("ironman.png");
	enemy_image = al_load_bitmap("hulk.png");

	Player *player;
	Enemy *enemy;

	player = new Player;
	player->set_x(SCREEN_WIDTH /2);
	player->set_y(3*SCREEN_HEIGHT / 4);
	player->set_x_velocity(5);
	player->set_y_velocity(5);
	player->set_width(32*2);
	player->set_height(48*2);
	player->set_bound(1);
	player->setImage(player_image);
	player->setFrameColumn(0);
	player->setFrameRow(0);
	objects.push_back(player);

	enemy = new Enemy;
	enemy->set_x(SCREEN_WIDTH / 2);
	enemy->set_y(SCREEN_HEIGHT-28);
	enemy->set_x_velocity(10);
	enemy->set_y_velocity(10);
	enemy->set_width(40*2);
	enemy->set_height(56*2);
	enemy->set_bound(1);
	enemy->setImage(enemy_image);
	objects.push_back(enemy);

	//Sounds & Musics
	al_reserve_samples(1);
	bg_music = al_load_sample("A Night of Dizzy Spells.ogg");
	bgInstance = al_create_sample_instance(bg_music);
	al_set_sample_instance_playmode(bgInstance, ALLEGRO_PLAYMODE_LOOP);
	//can set other properties here such as speed, gain, etc..
	al_attach_sample_instance_to_mixer(bgInstance, al_get_default_mixer());


	//Load Background
	//background = al_load_bitmap("background.png");

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

	//Create Timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the timer",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Event Queue
	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the event queue",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Font
	font_pirulen_72 = al_load_ttf_font("pirulen.ttf", 72, 0);
	font_pirulen_24= al_load_ttf_font("pirulen.ttf", 24, 0);
	font_pirulen_18 = al_load_ttf_font("pirulen.ttf", 18, 0);
	if (!font_pirulen_72 && !font_pirulen_18)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the font",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Register Event Sources
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display events
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer events
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	//Start playing the music
	al_play_sample_instance(bgInstance);

	al_start_timer(timer); //Start the timer

	//Game Loop
	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
	
			//al_get_keyboard_state();
			
			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->Update(key);


		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = true;
					break;
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				game_done=true;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty befor redrawing.
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_bitmap_region(background, 0, 0, 800, 600, 0, 0,0);
			for (std::list<GameObject*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
				(*iter)->Draw();

			al_draw_text(font_pirulen_24, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTER, "IRON MAN vs. HULK");
			//al_draw_textf(font_pirulen_18, al_map_rgb(255, 0, 0), 0, 10, ALLEGRO_ALIGN_CENTER, "%f fps",);
			al_flip_display();
		}
	}

	//Destroy
	delete player;
	delete enemy;
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

	return 0;
}