
#ifndef _POP_H
#define _POP_H

#include "Player.h"
#include "Bullet.h"
#include "node.h"
#include <fstream>

/*
enum OPTYPE {turn_left, turn_right, move, aim, shoot, prog3, prog2, last};

enum NODELOC {root, nleft, nmid, nright};
*/

#define POP_SIZE 100

class Pop
{
public:
	int curIndex;
	double fitnessPopulation[POP_SIZE];	//normalized fitness
	Pop(void);
	~Pop(void);

	// Players
	Player player1;
	Player player2;

	// Population for use with players
	Player* population[POP_SIZE];

	void FillFitness();
	void write_pop(void);
	void load_pop(void);

	Player *GetIndividual(int);
	void AddIndividual(Player *);

	void Evaluate(Player *,Player *);

	// Fitness
	void Fitness(void);
};

#endif
