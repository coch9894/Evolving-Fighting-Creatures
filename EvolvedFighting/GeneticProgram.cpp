#include "GeneticProgram.h"
#include <stack>


GeneticProgram::GeneticProgram(void)
{
	searchTeam1Pop = new Pop();
	selectTeam1Pop = new Pop();
	searchTeam1Pop->load_pop();

	BestIndex = 0;
	TourneySize = 2;	//subject to change
	//Init();
}

GeneticProgram::GeneticProgram(int fit1, int fit2)
{
	searchTeam1Pop = new Pop();
	selectTeam1Pop = new Pop();
	searchTeam1Pop->load_pop();

	searchTeam2Pop = new Pop();
	selectTeam2Pop = new Pop();
	searchTeam2Pop->load_pop();
	this->team1Fitness = fit1;
	this->team2Fitness = fit2;

	BestIndex = 0;

	TourneySize = 2;	//subject to change
	//Init();
}


GeneticProgram::~GeneticProgram(void)
{
}

void GeneticProgram::Init(){
	searchTeam1Pop->FillFitness();
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

Player *GeneticProgram::GetElite(Pop *pop, int fit){
	Player *one;
	Player *two;
	for(int i = 0; i < POP_SIZE - 1; i++){
		one = pop->GetIndividual(i);
		for(int j = i+1; j < POP_SIZE; j++){
			two = pop->GetIndividual(j);
			Evaluate(one, two, false);
			one->Evaluate_Fitness(fit);
			two->Evaluate_Fitness(fit);
			pop->fitnessPopulation[i] += one->GetTrainingFitness();
			pop->fitnessPopulation[j] += two->GetTrainingFitness();
		}
		pop->fitnessPopulation[i] = pop->fitnessPopulation[i]/POP_SIZE;
	}
	pop->fitnessPopulation[POP_SIZE] = pop->fitnessPopulation[POP_SIZE]/POP_SIZE;
	int winningIndex = 0;
	for(int i = 0; i < POP_SIZE; i++){
		if(pop->fitnessPopulation[winningIndex] < pop->fitnessPopulation[i]){
			winningIndex = i;
		}
	}
	return pop->GetIndividual(winningIndex);
}

void GeneticProgram::Search(){
	Player *bestIndivTeam1 = NULL;
	int bestIndexTeam1;
	Player *bestIndivTeam2 = NULL;
	int bestIndexTeam2;

	Player *highMan1 = NULL;
	Player *highMan2 = NULL;

	
	//debugFile.open("debug.txt");
	searchTeam1Pop->FillFitness();
	searchTeam2Pop->FillFitness();
	//searchPop->OutputFitness();
	//std::cout << std::endl;

	for(int i = 0; i < NUM_GENERATIONS; i++){
		std::cout << "CURRENT GENERATION IS " << i << std::endl;
		searchTeam1Pop->ResetFitness();
		selectTeam1Pop->ResetPopulation();

		searchTeam2Pop->ResetFitness();
		selectTeam2Pop->ResetPopulation();

		if(highMan1 == NULL){
			bestIndivTeam1 = GetElite(searchTeam1Pop, team1Fitness);
		}
		else{
			bestIndivTeam1 = highMan1;
		}
		if(highMan2 == NULL){
			bestIndivTeam2 = GetElite(searchTeam2Pop, team2Fitness);
		}
		else{
			bestIndivTeam2 = highMan2;
		}

		/*
		*	ELITISM
		*/
		selectTeam1Pop->AddIndividual(bestIndivTeam1);
		selectTeam2Pop->AddIndividual(bestIndivTeam2);
		std::cout << "Team 1 SELECT " << std::endl;
		//system("PAUSE");
		while(selectTeam1Pop->curIndex < POP_SIZE){
			Select(searchTeam1Pop, selectTeam1Pop, team1Fitness);
		}
		std::cout << "Team 2 SELECT " << std::endl;
		//system("PAUSE");
		while(selectTeam2Pop->curIndex < POP_SIZE){
			std::cout << selectTeam2Pop->curIndex << std::endl;
			Select(searchTeam2Pop, selectTeam2Pop, team2Fitness);
		}
		
		CopyPopulation(selectTeam1Pop, searchTeam1Pop);
		CopyPopulation(selectTeam2Pop, searchTeam2Pop);

		//searchTeam1Pop->FillFitness();
		//searchTeam2Pop->FillFitness();


		if(i % 5 == 0){
			highMan1 = GetElite(searchTeam1Pop, team1Fitness);
			highMan2 = GetElite(searchTeam2Pop, team2Fitness);
			Evaluate(highMan1, highMan2, true);
			if(highMan1->getFitness() < highMan2->getFitness()){
				highMan2->Team = this->team2Fitness;
				BestPop[BestIndex] = highMan2;
				BestIndex++;
			}
			else{
				highMan1->Team = this->team1Fitness;
				BestPop[BestIndex] = highMan2;
				BestIndex++;
			}
			// attack pops
			//bestIndiv = searchPop->GetBestIndividual();
			//debugFile << i << " " << searchPop->GetAverageFitness() << " " << bestPlayer->GetFood() << std::endl;
		}
		else{
			highMan1 = NULL;
			highMan2 = NULL;
		}
		
	}
	//debugFile.close();
}

void GeneticProgram::CalcFitness(Pop *pop){
	//pop->FillFitness();
}

//used previously for debugging
void GeneticProgram::ComparePopulation(){
	Player *searchIndiv = NULL;
	Player *selectIndiv = NULL;
	/*
	for(int i = 0; i < POP_SIZE; i++){
		if(searchPop->fitnessPopulation[i] != selectPop->fitnessPopulation[i]){
			searchIndiv = searchPop->GetIndividual(i);
			selectIndiv = selectPop->GetIndividual(i);
			searchIndiv->Evaluate();
			selectIndiv->Evaluate();
			std::cout << "searchPlayer " << i << ":: " << searchIndiv->getFitness() << "! Fitness array:: " << searchPop->fitnessPopulation[i] << std::endl;
			std::cout << "selectPlayer " << i << ":: " << selectIndiv->getFitness() << "! Fitness array:: " << selectPop->fitnessPopulation[i] << std::endl;
			system("PAUSE");
		}
	}
	*/
}

void GeneticProgram::Select(Pop * searchPop, Pop *selectPop, int teamfit){
	int firstWinnerIndex = TourneySelect(searchPop, teamfit);
	int secondWinnerIndex = TourneySelect(searchPop, teamfit);

	Player *firstPlayer = searchPop->GetIndividual(firstWinnerIndex);
	Player *secondPlayer = searchPop->GetIndividual(secondWinnerIndex);

	Crossover(firstPlayer, secondPlayer);

	Mutate(firstPlayer);
	Mutate(secondPlayer);

	selectPop->AddIndividual(firstPlayer);
	selectPop->AddIndividual(secondPlayer);
}

int GeneticProgram::GetBestIndividualIndex(const Pop *pop){
	int index = 0;
	for(int i = 0; i < POP_SIZE; i++){
		if(pop->fitnessPopulation[i] > pop->fitnessPopulation[index]){
			//std::cout << "new:: " << searchPop->fitnessPopulation[i] << std::endl;
			//std::cout << "old:: " << searchPop->fitnessPopulation[index] << std::endl;
			index = i;
		}
	}
	//system("PAUSE");
	return index;
}

int GeneticProgram::TourneySelect(Pop *pop, int fit){
	int oneIndex = rand()%POP_SIZE;
	int twoIndex = rand()%POP_SIZE;

	while(oneIndex == twoIndex){
		oneIndex = rand()%POP_SIZE;
	}

	Player *one = pop->GetIndividual(oneIndex);
	Player *two = pop->GetIndividual(twoIndex);
	Evaluate(one, two, false);
	one->Evaluate_Fitness(fit);
	two->Evaluate_Fitness(fit);
	if(two->GetTrainingFitness() > one->GetTrainingFitness()){
		return twoIndex;
	}

	return oneIndex;
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
	player->mutate();

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

/*
*	THIS NEEDS TO CREATE A NEW PLAYER EACH TIME
*/

void GeneticProgram::CopyPopulation(Pop *i_pop, Pop *m_pop){
	Player *tmpPlayer;
	node *tmpNode;
	node *copyNode;
	for(int i = 0; i < POP_SIZE; i++){
		tmpPlayer = new Player(false);
		copyNode = i_pop->population[i]->GetRoot();
		tmpNode = copyNode->copyTree(copyNode, NULL);
		tmpPlayer->SetRoot(tmpNode);
		tmpPlayer->SetSuccess(i_pop->population[i]->GetSuccess());
		tmpPlayer->SetFail(i_pop->population[i]->GetFail());

		m_pop->population[i] = tmpPlayer;
		//CopyIndividual(i_pop->GetIndividual(i), m_pop->GetIndividual(i));
		//m_pop[i] = CopyIndividual(i_pop->GetIndividual(i));
	}
}

void GeneticProgram::FillFitness(Pop *pop){
	for(int i = 0; i < POP_SIZE; i+=2){
		Evaluate(pop->population[i], pop->population[i+1], false);
		pop->fitnessPopulation[i] = pop->population[i]->getFitness();
		pop->fitnessPopulation[i+1] = pop->population[i+1]->getFitness();
	}
}

void GeneticProgram::Evaluate(Player *one, Player *two, bool isDrawn = false){
		int numSteps = 600;
	//InitBoard();	reset the environ list
	one->SetX(WINDOW_WIDTH/4);
	one->SetY(WINDOW_HEIGHT/2);

	two->SetX(3*WINDOW_WIDTH/4);
	two->SetY(WINDOW_HEIGHT/2);

	one->SetSuccess(0);
	one->SetFail(0);
	
	two->SetSuccess(0);
	two->SetFail(0);

	node *team1 = one->root;
	node *team2 = two->root;
	std::stack <node *> team1stack;
	std::stack <node *> team2stack;

	std::vector <Bullet *> bulletListTeam1;
	std::vector <Bullet *> bulletListTeam2;

	double angle = 0;
	double x1 = 0;
	double x2 = 0;
	double y1 = 0;
	double y2 = 0;


	// CREATE EVENT TIMER
	int frames = 0;
	float gameTime = 0;
	bool render = false;	//only draw every 60 seconds
	int gameFPS = 0;

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0/60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	gameTime = al_current_time();

	while(numSteps > 0){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(team1stack.empty()){
			team1 = one->root;
		}
		if(team2stack.empty()){
			team2 = two->root;
		}

		team1stack.push(team1);
		team2stack.push(team2);
		while(!team1stack.empty() && !team2stack.empty()){
			if(ev.type == ALLEGRO_EVENT_TIMER){
				render = true;
				frames++;

				if(al_current_time() - gameTime >= 1){
					gameTime = al_current_time();
					gameFPS = frames;
					frames = 0;
				}
				if(team1 != NULL){
					switch(team1->type){
						case prog3:
							team1stack.push(team1->right);
							team1stack.push(team1->mid);
							team1stack.push(team1->left);
							break;
						case prog2:
							team1stack.push(team1->right);
							team1stack.push(team1->left);
							break;
						case aim:
							x1 = one->GetX();
							y1 = one->GetY();
							x2 = two->GetX();
							y2 = two->GetY();

							if(x2 == x1) x2 += 1;
							angle = atan( (y2-y1)/(x2-x1) );

							one->SetDirection(angle);
						
							numSteps--;
							break;
						case turn_left:
							one->TurnLeft();
							numSteps--;
							break;
						case turn_right:
							one->TurnRight();
							numSteps--;
							break;
						case move:
							one->MoveForward();
							if(one->GetX() > WINDOW_WIDTH/2){
								one->SetX(WINDOW_WIDTH/2);
							}
							else if(one->GetX() < 0){
								one->SetX(0);
							}
							numSteps--;
							break;
						case shoot:
							if(one->totalBullets > 0){
								Bullet *b = new Bullet(one->GetDirection(), one->GetX(), one->GetY());
								bulletListTeam1.push_back(b);
								//one->totalBullets--;
							}

							numSteps--;
							break;
					}
				}

				if(team2 != NULL){
					switch(team2->type){
						case prog3:
							team2stack.push(team2->right);
							team2stack.push(team2->mid);
							team2stack.push(team2->left);
							break;
						case prog2:
							team2stack.push(team2->right);
							team2stack.push(team2->left);
							break;
						case aim:
							x1 = two->GetX();
							y1 = two->GetY();
							x2 = one->GetX();
							y2 = one->GetY();

							if(x2 == x1) x2 += 1;
							angle = atan( (y2-y1)/(x2-x1) );
							angle += 3.14159;

							two->SetDirection(angle);

							numSteps--;
							break;
						case turn_left:
							two->TurnRight();
							numSteps--;		//num steps from team 2 also
							break;
						case turn_right:
							two->TurnLeft();
							numSteps--;
							break;
						case move:
							two->MoveForward();
							if(two->GetX() > WINDOW_WIDTH){
								two->SetX(WINDOW_WIDTH);
							}
							if(two->GetX() < WINDOW_WIDTH/2){
								two->SetX(WINDOW_WIDTH/2);
							}
							numSteps--;
							break;
						case shoot:
							if(two->totalBullets > 0){
								Bullet *b = new Bullet(two->GetDirection(), two->GetX(), two->GetY());
								bulletListTeam2.push_back(b);
								//two->totalBullets--;
							}
							numSteps--;
							break;
					}
				}

				//update all the bullets
				int hit;
				if(!bulletListTeam1.empty()){
					for(std::vector<Bullet *>::iterator it = bulletListTeam1.begin(); it != bulletListTeam1.end(); ++it){
						if((*it) == NULL) continue;
						hit = (*it)->Update(two);
						if( hit == 0){
							//(*it)->~Bullet();
							//delete (*it);
						}
						else if(hit == 2){
							one->Hit();
							//(*it)->~Bullet();
							//delete (*it);
						}
					}
				}

				if(!bulletListTeam2.empty()){
					for(std::vector<Bullet *>::iterator it = bulletListTeam2.begin(); it != bulletListTeam2.end(); ++it){
						if((*it) == NULL) continue;
						hit = (*it)->Update(one);
						if( hit == 0){
							//(*it)->~Bullet();
							//delete (*it);
						}
						else if(hit == 2){
							two->Hit();
							//(*it)->~Bullet();
							//delete (*it);
						}
					}
				}

				team1 = team1stack.top();
				team1stack.pop();
				team2 = team2stack.top();
				team2stack.pop();

			}

			if(render && al_is_event_queue_empty(event_queue)){
				render = false;
				//if we're ready to draw... do this
				if(isDrawn){
					DrawEnviron(one, two, bulletListTeam1, bulletListTeam2);
					al_flip_display();
					al_clear_to_color(al_map_rgb(0, 0, 0));
					//system("PAUSE");
				}
			}
		}


	}
	one->Normalize_Fitness();
	two->Normalize_Fitness();
	bulletListTeam1.clear();
	bulletListTeam2.clear();
	al_destroy_event_queue(event_queue);
}

void GeneticProgram::DrawEnviron(Player *one, Player *two, std::vector<Bullet *> v1, std::vector<Bullet *> v2){
	one->DrawPlayer(1);
	two->DrawPlayer(2);
	if(!v1.empty()){
		for(std::vector<Bullet *>::iterator it = v1.begin(); it != v1.end(); ++it){
			if((*it) == NULL) continue;
			(*it)->DrawBullet();
		}
	}

	if(!v2.empty()){
		for(std::vector<Bullet *>::iterator it = v2.begin(); it != v2.end(); ++it){
			if((*it) == NULL) continue;
			(*it)->DrawBullet();
		}
	}

}