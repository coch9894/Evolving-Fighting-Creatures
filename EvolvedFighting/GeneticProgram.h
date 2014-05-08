
#ifndef _GP_H
#define _GP_H

#include "Pop.h"
#include "Bullet.h"
#include <fstream>

#define NUM_GENERATIONS 100
#define ELITE_SIZE NUM_GENERATIONS/5
class GeneticProgram
{
private:
	Pop *searchTeam1Pop;
	Pop *selectTeam1Pop;

	Pop *searchTeam2Pop;
	Pop *selectTeam2Pop;

	int TourneySize;	//test
	int team1Fitness;	//which fitness are we using?
	int team2Fitness;	//which fitness are we using?

	std::ofstream debugFile;

	void ComparePopulation();

public:
	void PrintPopulation(Pop *);
	void PrintPopulation();
	void PrintFitness();
	void Init();

	GeneticProgram(void);
	GeneticProgram(int, int);
	~GeneticProgram(void);

	void Select(Pop *, Pop *, int);
	void Search();
	int GetBestIndividualIndex(const Pop *);
	int TourneySelect(Pop *, int);
	void Crossover(Player *, Player *);
	void Mutate(Player *);

	void CopyPopulation(Pop *, Pop *);
	void CalcFitness(Pop *);
	void PrintIndividual();

	void GetBestAndAverage();

	Player *CopyIndividual(Player *, Player *);

	Player *GetBest();

	void Evaluate(Player *, Player *, bool);

	void DrawEnviron(Player *, Player *, std::vector<Bullet *>, std::vector<Bullet *>);

	void FillFitness(Pop *);

	Player *GetElite(Pop *, int);

	Player *BestPop[ELITE_SIZE];
	int BestIndex;

};

#endif