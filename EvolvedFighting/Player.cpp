#include "Player.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>


Player::Player(){

}

Player::Player(int x, int y )
{
	this->x_pos = x;
	this->y_pos = y;
	this->direction = -90;	//straight up and down
	this->fitness = 0;
	this->numFail = 0;
	this->numSuccess = 0;
	this->speed = 5;		//subject to change?
	this->root = NULL;		//generate the root;
}


Player::~Player(void)
{
}

void Player::Normalize_Fitness(){
	if(this->numSuccess == this->numFail){
		this->fitness = 1;
	}
	else{
		if(this->numFail == 0){
			this->numFail += 0.01;
		}
		this->fitness = numSuccess/numFail;
	}
}

void Player::DrawPlayer(){
	//draw line for direction facing
	al_draw_line(x_pos, y_pos, x_pos + cos(direction)*RADIUS*2, y_pos + sin(direction)*RADIUS*2, al_map_rgb(0, 255, 0), 2);
	al_draw_filled_circle(x_pos, y_pos, RADIUS, al_map_rgb(0, 0, 255));
}

void Player::Evaluate(){
	
}

double Player::getFitness(){
	return this->fitness;
}

void Player::TurnLeft(){
	this->direction += BASE_ANGLE;
}

void Player::TurnRight(){
	this->direction -= BASE_ANGLE;
}

void Player::MoveForward(){
	this->x_pos = cos(this->direction)*speed + 0.5;
	this->y_pos = sin(this->direction)*speed + 0.5;
}

void Player::Shoot(Player *o){
	Bullet *b = new Bullet(this, o);
	bulletList.push_back(b);
}