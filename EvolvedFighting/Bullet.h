#pragma once

#include "util.h"
#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Bullet
{
public:
	Bullet(void);
	Bullet(Player *, Player *);
	~Bullet(void);

	Player *parent;
	Player *opponent;

	double speed;
	int x_pos;	//ints for pixel loc
	int y_pos;	//ints for pixel loc

	float dir;

	bool collision;

	bool isCollided();	//should be called every update
	bool Update();
	void DrawBullet();
};

