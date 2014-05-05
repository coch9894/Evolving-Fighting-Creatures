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
	int x_pos;	//ints for pixel loc
	int y_pos;	//ints for pixel loc

	float dir;

	bool collision;
	bool isAlive;

	bool isCollided(Player *);	//should be called every update
	int Update(Player *);
	void DrawBullet();
};

#endif
