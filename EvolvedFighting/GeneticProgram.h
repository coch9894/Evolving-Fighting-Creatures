
#ifndef _GP_H
#define _GP_H

#include "Pop.h"
#include "Bullet.h"
#include <fstream>

#define NUM_GENERATIONS 250
class GeneticProgram
{
private:
	Pop *searchTeam1Pop;
	Pop *selectTeam1Pop;

	Pop *searchTeam2Pop;
	Pop *selectTeam2Pop;
	int TourneySize;	//test

	std::ofstream debugFile;

	void ComparePopulation();

public:
	void PrintPopulation(Pop *);
	void PrintPopulation();
	void PrintFitness();
	void Init();

	GeneticProgram(void);
	~GeneticProgram(void);

	void Select(Pop *, Pop *);
	void Search();
	int GetBestIndividualIndex(const Pop *);
	int TourneySelect(Pop *);
	void Crossover(Player *, Player *);
	void Mutate(Player *);

	void CopyPopulation(Pop *, Pop *);
	void CalcFitness(Pop *);
	void PrintIndividual();

	void GetBestAndAverage();

	Player *CopyIndividual(Player *, Player *);

	Player *GetBest();

	void Evaluate(Player *, Player *, bool);

	void DrawEnviron(Player *, Player *);

	void FillFitness(Pop *);

	std::vector <Bullet *> bulletListTeam1;
	std::vector <Bullet *> bulletListTeam2;

};

#endif