#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv)
{
	//Consts
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//Intitializations
	
	//Intitalize allegro
	if (!al_init())
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to initialize",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Create Display
	ALLEGRO_DISPLAY *display = NULL;
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display)
	{
		al_show_native_message_box(al_get_current_display(), "Error", "Error", "Allegro failed to create the display",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Load addons

	al_clear_to_color(al_map_rgb(0, 0, 0));

	//al_draw_filled_circle(320, 240, 10, al_map_rgb(255, 255, 255));

	al_flip_display();

	al_show_native_message_box(al_get_current_display(),
		"Window Title",
		"Content Title",
		"The error message here",
		NULL, ALLEGRO_MESSAGEBOX_ERROR);

	al_rest(10.0);

	al_destroy_display(display);

	return 0;
}