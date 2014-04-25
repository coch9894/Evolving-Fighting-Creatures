#pragma once
#include "Pop.h"
#include <fstream>

#define NUM_GENERATIONS 250
class GeneticProgram
{
private:
	Pop *searchPop;
	Pop *selectPop;
	int TourneySize;

	std::ofstream debugFile;

	void ComparePopulation();

public:
	void PrintPopulation(Pop *);
	void PrintPopulation();
	void PrintFitness();
	void Init();

	GeneticProgram(void);
	~GeneticProgram(void);

	void Select();
	void Search();
	int GetBestIndividualIndex();
	int TourneySelect();
	void Crossover(Player *, Player *);
	void Mutate(Player *);

	void CopyPopulation(Pop *, Pop *);
	void CalcFitness(Pop *);
	void PrintIndividual();

	void GetBestAndAverage();

	Player *CopyIndividual(Player *, Player *);

	Player *GetBest();

};

