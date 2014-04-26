#pragma once

#include "util.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Bullet
{
public:
	Bullet(void);
	~Bullet(void);

	double speed;
	int x_pos;	//ints for pixel loc
	int y_pos;	//ints for pixel loc

	direction dir;

	bool collision;

	bool isCollided();
	void Update();
	void DrawBullet();
};

