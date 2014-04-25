#include "Player.h"


Player::Player(void)
{
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