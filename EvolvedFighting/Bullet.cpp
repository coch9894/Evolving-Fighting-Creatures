#include "Bullet.h"


Bullet::Bullet(void)
{
	this->y_pos = 50;
	this->x_pos = 50;
}


Bullet::~Bullet(void)
{
}

void Bullet::DrawBullet(){
	al_draw_filled_circle(x_pos, y_pos, 2, al_map_rgb(255, 255, 255));
}
