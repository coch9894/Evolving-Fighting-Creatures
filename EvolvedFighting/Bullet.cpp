#include "Bullet.h"

Bullet::Bullet(){

}

Bullet::Bullet(float d, int x, int y)
{
	//this->parent = p;
	this->dir = d;
	this->y_pos = sin(dir)*RADIUS*2 + y;
	this->x_pos = cos(dir)*RADIUS*2 + x;
	
	speed = 5;
	this->velX = speed*cos(this->dir);
	this->velY = speed*sin(this->dir);
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
		this->isAlive = false;
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
	float dx = speed*cos(this->dir);
	//float dy;
	//make sure this is working for both sides currently only working for one side
	if(this->dir > 3.14159/2 && this->dir < 3.14159 * 3/2){
		this->x_pos = this->x_pos + dx - 0.5;
	}
	else{
		this->x_pos = this->x_pos + dx + 0.5;
	}
	//int dy = sin(this->dir) + 0.5;

	this->x_pos += this->velX;
	this->y_pos += this->velY;
	//this->x_pos = this->x_pos + this->speed*dx;
	//this->y_pos = this->y_pos + this->speed*dy;

	if(this->isAlive){
		if(this->isCollided(opp)){
			return 2;
		}
	}
	if( this->x_pos > WINDOW_WIDTH || this->x_pos < 0 ||
		this->y_pos > WINDOW_HEIGHT || this->y_pos < 0 ){
		this->isAlive = false;
		return 0;
	}
	return 1;
}
