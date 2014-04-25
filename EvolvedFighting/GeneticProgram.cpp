#include "GeneticProgram.h"
#include <stack>


GeneticProgram::GeneticProgram(void)
{
	searchPop = new Pop();
	selectPop = new Pop();
	TourneySize = 3;	//subject to change
	Init();
}


GeneticProgram::~GeneticProgram(void)
{
}

void GeneticProgram::Init(){
	//searchPop->FillFitness();
}

void GeneticProgram::PrintPopulation(){
//	searchPop->Output();
}

void GeneticProgram::PrintPopulation(Pop *pop){
	//pop->Output();
}

void GeneticProgram::PrintFitness(){
//	saerchPop->OutputFitness();
}

void GeneticProgram::Search(){
	Player *bestIndiv = NULL;
	int bestIndex;

	
	debugFile.open("debug.txt");
	//searchPop->FillFitness();
	//searchPop->OutputFitness();
	std::cout << std::endl;
	//system("PAUSE");

	for(int i = 0; i < NUM_GENERATIONS; i++){
		//selectPop->ResetPopulation();

		bestIndex = GetBestIndividualIndex();
		//bestIndiv = searchPop->GetIndividual(bestIndex);
		bestIndiv->Evaluate();
		//selectPop->AddIndividual(bestIndiv);
		//selectPop->AddIndividual(bestIndiv);
		//system("PAUSE");
		while(selectPop->curIndex < POP_SIZE){
			Select();
		}
		
		// THIS IS WORKING NOW
		CopyPopulation(selectPop, searchPop);
		//searchPop->FillFitness();
		if(i % 5 == 0){
			//bestIndiv = searchPop->GetBestIndividual();
			//debugFile << i << " " << searchPop->GetAverageFitness() << " " << bestPlayer->GetFood() << std::endl;
		}
		
	}
	debugFile.close();
}

void GeneticProgram::CalcFitness(Pop *pop){
	//pop->FillFitness();
}

void GeneticProgram::ComparePopulation(){
	Player *searchIndiv = NULL;
	Player *selectIndiv = NULL;
	for(int i = 0; i < POP_SIZE; i++){
		if(searchPop->fitnessPopulation[i] != selectPop->fitnessPopulation[i]){
			searchIndiv = searchPop->GetIndividual(i);
			selectIndiv = selectPop->GetIndividual(i);
			searchIndiv->Evaluate();
			selectIndiv->Evaluate();
			std::cout << "searchPlayer " << i << ":: " << searchIndiv->GetFitness() << "! Fitness array:: " << searchPop->fitnessPopulation[i] << std::endl;
			std::cout << "selectPlayer " << i << ":: " << selectIndiv->GetFitness() << "! Fitness array:: " << selectPop->fitnessPopulation[i] << std::endl;
			system("PAUSE");
		}
	}
}

void GeneticProgram::Select(){
	int firstWinnerIndex = TourneySelect();
	int secondWinnerIndex = TourneySelect();

	//GetIndividual might be shallow copying and that's why we're getting weird results
	//write a node copy function
	Player *firstPlayer = searchPop->GetIndividual(firstWinnerIndex);
	Player *secondPlayer = searchPop->GetIndividual(secondWinnerIndex);

	Crossover(firstPlayer, secondPlayer);

	Mutate(firstPlayer);
	Mutate(secondPlayer);

	selectPop->AddIndividual(firstPlayer);
	selectPop->AddIndividual(secondPlayer);
}

int GeneticProgram::GetBestIndividualIndex(){
	int index = 0;
	for(int i = 0; i < POP_SIZE; i++){
		if(searchPop->fitnessPopulation[i] > searchPop->fitnessPopulation[index]){
			//std::cout << "new:: " << searchPop->fitnessPopulation[i] << std::endl;
			//std::cout << "old:: " << searchPop->fitnessPopulation[index] << std::endl;
			index = i;
		}
	}
	//system("PAUSE");
	return index;
}

int GeneticProgram::TourneySelect(){
	int winningIndex = rand()%POP_SIZE;
	int tmpIndex;

	for(int i = 0; i < TourneySize; i++){
		tmpIndex = rand()%POP_SIZE;
		if(searchPop->fitnessPopulation[tmpIndex] > searchPop->fitnessPopulation[winningIndex]){
			winningIndex = tmpIndex;
		}
	}

	return winningIndex;
}

void GeneticProgram::Crossover(Player *first, Player *second){
	//do this
	int firstNodeNum = rand() % first->GetSize();
	node *firstNode = first->root;

	std::stack<node *> firstStack;
	firstStack.push(firstNode);
	while(firstNodeNum > 0 && !firstStack.empty()){
		if(firstNode->left != NULL){
			firstStack.push(firstNode->left);
		}
		if(firstNode->mid != NULL){
			firstStack.push(firstNode->mid);
		}
		if(firstNode->right != NULL){
			firstStack.push(firstNode->right);
		}

		firstNode = firstStack.top();
		firstStack.pop();
		firstNodeNum--;
	}
	while(!firstStack.empty()){
		firstStack.pop();
	}

	//firstNode should be a random node
	//do the same with second node
	node *secondNode = second->root;
	int secondNodeNum = rand() % second->GetSize();

	std::stack<node *> secondStack;
	secondStack.push(secondNode);
	while(secondNodeNum > 0 && !secondStack.empty()){
		if(secondNode->left != NULL){
			secondStack.push(secondNode->left);
		}
		if(secondNode->mid != NULL){
			secondStack.push(secondNode->mid);
		}
		if(secondNode->right != NULL){
			secondStack.push(secondNode->right);
		}

		secondNode = secondStack.top();
		secondStack.pop();
		secondNodeNum--;
	}
	while(!secondStack.empty()){
		secondStack.pop();
	}

	//now we have both subtree nodes to swap
	node *tmpNode = firstNode->copyTree(firstNode, firstNode->parent);
	firstNode = firstNode->copyTree(secondNode, firstNode->parent);
	secondNode = secondNode->copyTree(tmpNode, secondNode->parent);

	//make sure the parent has the right spot
	if(firstNode->parent != NULL){
		switch(firstNode->loc){
			case nleft:
				firstNode->parent->left = firstNode;
				break;
			case nmid:
				firstNode->parent->mid = firstNode;
				break;
			case nright:
				firstNode->parent->right = firstNode;
				break;
		}
	}
	else{
		firstNode->loc = root;
	}
	if(secondNode->parent != NULL){
		switch(secondNode->loc){
			case nleft:
				secondNode->parent->left = secondNode;
				break;
			case nmid:
				secondNode->parent->mid = secondNode;
				break;
			case nright:
				secondNode->parent->right = secondNode;
				break;
		}
	}
	else{
		secondNode->loc = root;
	}

}

void GeneticProgram::Mutate(Player *player){
	// traverse through tree and mutate
	//player->mutate();

}

Player * GeneticProgram::CopyIndividual(Player * inputPlayer, Player *outputPlayer){
	node *tmp = inputPlayer->GetRoot();
	outputPlayer->SetRoot(tmp);
	/*
	inputPlayer->Evaluate();
	outputPlayer->Evaluate();
	if( inputPlayer->GetFood() != outputPlayer->GetFood()){
		inputPlayer->PrintBoard();
		outputPlayer->PrintBoard();
		system("PAUSE");
	}
	*/
	return NULL;
}

void GeneticProgram::CopyPopulation(Pop *i_pop, Pop *m_pop){
	for(int i = 0; i < POP_SIZE; i++){
		m_pop->population[i] = i_pop->population[i];
		//CopyIndividual(i_pop->GetIndividual(i), m_pop->GetIndividual(i));
		//m_pop[i] = CopyIndividual(i_pop->GetIndividual(i));
	}
}