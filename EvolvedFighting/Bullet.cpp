#include "Bullet.h"


Bullet::Bullet(void)
{
}

Bullet::Bullet(Player *p, Player *o)
{
	this->parent = p;
	this->dir = p->GetDirection();
	this->y_pos = sin(dir)*RADIUS*2 + p->GetY();
	this->x_pos = cos(dir)*RADIUS*2 + p->GetX();

	speed = 10;




	this->opponent = o;
}


Bullet::~Bullet(void)
{
}

void Bullet::DrawBullet(){
	al_draw_filled_circle(x_pos, y_pos, 2, al_map_rgb(255, 255, 255));
}

//returns true if it collides with the opponent
bool Bullet::isCollided(){
	float dx = this->x_pos - opponent->GetX();
	float dy = this->y_pos - opponent->GetY();

	float distance = sqrt(dx*dx + dy*dy);
	if(distance < RADIUS){
		opponent->GotHit();
		parent->Hit();
		return true;
	}

	return false;
}


//returns true if the bullet is still alive
//calling function will delete bullet if this returns false;
bool Bullet::Update(){
	this->x_pos += this->x_pos + this->speed*cos(this->dir);
	this->y_pos += this->y_pos + this->speed*sin(this->dir);
	if(this->isCollided()){
		return false;
	}
	if( this->x_pos > WINDOW_WIDTH || this->x_pos < 0 ||
		this->y_pos > WINDOW_HEIGHT || this->y_pos < 0 ){
		return false;
	}
	return true;
}
