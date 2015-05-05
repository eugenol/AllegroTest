#include "HUD.h"


HUD::HUD(GameObject *owner)
{ 
	HUD::owner = owner;
}


HUD::~HUD()
{
}

void HUD::Update()
{

}

void HUD::Draw()
{
	al_draw_rectangle(SCREEN_WIDTH - 116, SCREEN_HEIGHT - 20, SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10, al_map_rgba(255, 0, 0, 100), 2);
	al_draw_filled_rectangle(SCREEN_WIDTH - 113, SCREEN_HEIGHT - 17, SCREEN_WIDTH - 113 + owner->getHealth(), SCREEN_HEIGHT - 13, al_map_rgba(255, 0, 0, 50));
}