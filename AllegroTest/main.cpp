/*#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
*/

#include "GameObject.h"
#include "Player.h"


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
	bool key[8] = { false, false, false, false, false, false, false, false };

	//Intitializations
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font_pirulen_18 = NULL;
	ALLEGRO_FONT *font_pirulen_24 = NULL;
	ALLEGRO_FONT *font_pirulen_72 = NULL;
	ALLEGRO_BITMAP *player1_image = NULL;
	ALLEGRO_BITMAP *player2_image = NULL;
	//ALLEGRO_BITMAP *background = NULL;

	//Intitalize allegro
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to initialize",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Intitialize addons
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();

	//New Player Object
	player1_image = al_load_bitmap("ironman.png");
	player2_image = al_load_bitmap("captainamerica_shield.png");

	Player *player[2];

	for (int i = 0; i < 2; i++)
	{
		player[i] = new Player;
		player[i]->set_x(SCREEN_WIDTH / 4 *(2*i+1));
		player[i]->set_y(SCREEN_HEIGHT / 2);
		player[i]->set_x_velocity(5);
		player[i]->set_y_velocity(5);
		player[i]->set_width(32);
		player[i]->set_height(48);
		player[i]->set_bound(1);
	}
	player[0]->setImage(player1_image);
	player[0]->setLeft(true);
	player[1]->setImage(player2_image);
	player[1]->setLeft(false);

	//Load Background
	//background = al_load_bitmap("background.png");

	//Create Display
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

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

	al_start_timer(timer); //Start the timer

	//Game Loop
	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			
			for (int i = 0; i < 2; i++)
				player[i]->Update(key);

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
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

				case ALLEGRO_KEY_W:
					key[KEY_W] = true;
					break;
				case ALLEGRO_KEY_S:
					key[KEY_S] = true;
					break;
				case ALLEGRO_KEY_A:
					key[KEY_A] = true;
					break;
				case ALLEGRO_KEY_D:
					key[KEY_D] = true;
					break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
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

			case ALLEGRO_KEY_W:
				key[KEY_W] = false;
				break;
			case ALLEGRO_KEY_S:
				key[KEY_S] = false;
				break;
			case ALLEGRO_KEY_A:
				key[KEY_A] = false;
				break;
			case ALLEGRO_KEY_D:
				key[KEY_D] = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done = true;

		if (redraw && al_is_event_queue_empty(event_queue)) //have to wait until event queue is empty befor redrawing.
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			//al_draw_bitmap_region(background, 0, 0, 800, 600, 0, 0,0);
			for (int i = 0; i < 2; i++)
				player[i]->Draw();
			al_draw_text(font_pirulen_24, al_map_rgb(255, 0, 0), SCREEN_WIDTH / 2, 10, ALLEGRO_ALIGN_CENTER, "IRON MAN vs. CAPTAIN AMERICA");
			al_flip_display();
		}
	}

	//Destroy
	//al_destroy_bitmap(background);
	for (int i = 0; i < 2; i++)
		delete player[i];
	al_destroy_bitmap(player2_image);
	al_destroy_bitmap(player1_image);
	al_destroy_font(font_pirulen_72);
	al_destroy_font(font_pirulen_24);
	al_destroy_font(font_pirulen_18);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}