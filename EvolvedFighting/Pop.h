#pragma once

#include "Player.h"
#include "Bullet.h"
#include "node.h"
#include <fstream>

/*
enum OPTYPE {turn_left, turn_right, move, aim, shoot, prog3, prog2, iflookingat, last};

enum NODELOC {root, nleft, nmid, nright};
*/

#define POP_SIZE 100
#define DEPTH 3

class Pop
{
public:
	Pop(void);
	~Pop(void);

	// Players
	Player player1;
	Player player2;

	// Population for use with players
	node* population[POP_SIZE];
	void write_pop(void);
	void load_pop(void);
};

