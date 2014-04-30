#pragma once
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef enum direction
{
	up,
	down,
	left,
	right
}direction;

std::vector <Bullet *> bulletList;