#ifndef _BULLET_H
#define _BULLET_H

#include "util.h"
#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
class Bullet
{
public:
	Bullet();
	Bullet(float, int, int);
	~Bullet(void);

	//Player *parent;
	//Player *opponent;


	double speed;
	float x_pos;	//ints for pixel loc
	float y_pos;	//ints for pixel loc
	float velX;
	float velY;

	float dir;

	bool collision;
	bool isAlive;

	bool isCollided(Player *);	//should be called every update
	int Update(Player *);
	void DrawBullet();
};

#endif
