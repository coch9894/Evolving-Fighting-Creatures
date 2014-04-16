#pragma once

#include "util.h"

class Bullet
{
public:
	Bullet(void);
	~Bullet(void);

	double speed;

	direction dir;

	bool collision;
};

