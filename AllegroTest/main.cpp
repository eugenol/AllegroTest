#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(800, 600);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	//al_draw_filled_circle(320, 240, 10, al_map_rgb(255, 255, 255));

	al_flip_display();

	al_rest(10.0);

	al_destroy_display(display);

	return 0;
}