#include "Bullet.h"

Bullet::Bullet(){

}

Bullet::Bullet(float d, int x, int y)
{
	//this->parent = p;
	this->dir = d;
	this->y_pos = sin(dir)*RADIUS*2 + y;
	this->x_pos = cos(dir)*RADIUS*2 + x;

	speed = 10;
}


Bullet::~Bullet(void)
{
}

void Bullet::DrawBullet(){
	al_draw_filled_circle(x_pos, y_pos, 2, al_map_rgb(255, 255, 255));
}

//returns true if it collides with the opponent
bool Bullet::isCollided(Player *opp){
	float dx = this->x_pos - opp->GetX();
	float dy = this->y_pos - opp->GetY();

	float distance = sqrt(dx*dx + dy*dy);
	if(distance < RADIUS){
		opp->GotHit();
		return true;
	}

	return false;
}


//returns 0 if outside of range of board
//returns 1 if still alive
//returns 2 if it's a hit
//calling function will delete bullet if this returns false;
int Bullet::Update(Player *opp){
	this->x_pos += this->x_pos + this->speed*cos(this->dir);
	this->y_pos += this->y_pos + this->speed*sin(this->dir);
	if(this->isCollided(opp)){
		return 2;
	}
	if( this->x_pos > WINDOW_WIDTH || this->x_pos < 0 ||
		this->y_pos > WINDOW_HEIGHT || this->y_pos < 0 ){
		return 0;
	}
	return 1;
}
