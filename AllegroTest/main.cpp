#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv)
{
	//Consts
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float FPS = 60;

	bool game_done = false;
	bool redraw = false;

	//Intitializations
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//Intitalize allegro
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to initialize",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Display
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Timer
	timer = al_create_timer(1 / FPS);
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


	//Register Event Sources
	al_register_event_source(event_queue, al_get_display_event_source(display)); //display events
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); // timer events

	//Load addons

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_start_timer(timer); //Start the timer

	//Game Loop
	while (!game_done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
			redraw = true;
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			game_done=true;

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_flip_display();
		}
	}
	//Destroy
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}