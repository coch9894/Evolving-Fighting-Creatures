#include "Player.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

Player::Player( bool b )
{
	this->x_pos = 0;
	this->y_pos = 0;
	this->direction = -3.14159/2;	//straight up and down
	this->fitness = 0;
	this->numFail = 0;
	this->numSuccess = 0;
	this->speed = 1;		//subject to change?
	this->totalBullets = 100;	//do we need to limit this?
	if( b )
	{
		this->root = new node();
		this->root->type = prog3;
		this->root->generate(DEPTH, NULL, (NODELOC)0);
	}
	//this->root = NULL;		//generate the root;
}

Player::Player()
{
}

Player::~Player(void)
{
}

void Player::Evaluate_Fitness(int fit){
	switch(fit){
		case 0:	//MAX MAX
			this->MaxMax();
			break;
		case 1: //MIN MAX
			this->MinMax();
			break;
		case 2:	//MIN MIN
			this->MinMin();
			break;
		case 3:	//MAX MIN
			this->MaxMin();
			break;
	}
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

void Player::MaxMax()
{
	training_fitness = numSuccess * numFail;
}

void Player::MinMax()
{
	if(this->numSuccess == this->numFail){
		this->fitness = 1;
	}
	else{
		if(this->numSuccess == 0){
			this->numSuccess += 0.01;
		}
		this->fitness = numFail/numSuccess;
	}
}

void Player::MinMin()
{
	if( numSuccess == 0 )
		numSuccess += 0.01;
	if( numFail == 0 )
		numFail += 0.01;
	training_fitness = (1/numSuccess) * (1/numFail);
}

void Player::MaxMin()
{
	Normalize_Fitness();
	training_fitness = fitness;
}

void Player::DrawPlayer(int side){
	//draw line for direction facing
	al_draw_line(x_pos, y_pos, x_pos + cos(direction)*RADIUS*2, y_pos + sin(direction)*RADIUS*2, al_map_rgb(0, 255, 0), 2);
	if(side == 1){
		al_draw_filled_circle(x_pos, y_pos, RADIUS, al_map_rgb(0, 0, 255));
	}
	if(side == 2){
		al_draw_filled_circle(x_pos, y_pos, RADIUS, al_map_rgb(255, 0, 0));
	}
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
	this->x_pos += cos(this->direction)*speed + 0.5;
	this->y_pos += sin(this->direction)*speed + 0.5;
	if(y_pos > WINDOW_HEIGHT){
		y_pos = WINDOW_HEIGHT;
	}
	else if(y_pos < 0){
		y_pos = 0;
	}
}

/* @param int player is the player firing the bullet
void Player::Shoot(int player){
	Bullet *b = new Bullet(this->direction, this->x_pos, this->y_pos);
	if(player == 1)
		bulletListTeam1.push_back(b);
	else if(player == 2)
		bulletListTeam2.push_back(b);
}
*/

void Player::mutate(){
	this->root->mutate();
}