#include "Pop.h"
#include <queue>

Pop::Pop(void)
{
}

Pop::~Pop(void)
{
	for( int i = 0; i < POP_SIZE; i++ )
	{
		delete population[i];
	}
}

void Pop::load_pop(void)
{
	std::ifstream i;
	i.open("init.dat");

	/* deletion for later
	for( int count = 0; count < POP_SIZE; count++ )
	{
		delete population[count];
		population[count] = NULL;
	}
	*/
	
	for( int count = 0; count < POP_SIZE; count++ )
	{
		char* str;
		std::queue<node*> q;

		str = new char[10];
		i.getline(str,10);

		if( str[0] == '\n' && count < POP_SIZE )
		{
			char temp;
			std::cout << "Error in loading population" << std::endl;
			std::cin >> temp;
			exit(-1);
		}

		while( str[0] != '8' )
		{
			node * temp;
			temp = new node();

			switch( str[0] )
			{
			case turn_left:
				temp->type = turn_left;
				break;
			case turn_right:
				temp->type =  turn_right;
				break;
			case move:
				temp->type = move;
				break;
			case aim:
				temp->type = aim;
				break;
			case shoot:
				temp->type = shoot;
				break;
			case prog3:
				temp->type = prog3;
				break;
			case prog2:
				temp->type = prog2;
				break;
			}

			q.push(temp);

			i.getline(str,10);
		}

		population[count] = new Player();
		population[count]->root = q.front();
		population[count]->root->parent = NULL;
		population[count]->root->loc = root;
		q.pop();

		node * temp = population[count]->root;
		std::queue<node*> fill;
		fill.push(temp);

		while( !fill.empty() && !q.empty() )
		{
			temp = fill.front();
			fill.pop();

			if( !q.empty() )
			{
				temp->left = q.front();
				temp->left->parent = temp;
				temp->left->loc = nleft;
				q.pop();
				fill.push(temp->left);
			}
			else
			{
				temp->left = NULL;
			}

			if( temp->type == prog3 )
			{
				if( !q.empty() )
				{
					temp->mid = q.front();
					temp->mid->parent = temp;
					temp->mid->loc = nmid;
					q.pop();
					fill.push(temp->mid);
				}
				else
				{
					temp->mid = NULL;
				}
			}

			if( !q.empty() )
			{
				temp->right = q.front();
				temp->right->parent = temp;
				temp->right->loc = nright;
				q.pop();
				fill.push(temp->right);
			}
			else
			{
				temp->right = NULL;
			}
		}

	}
}


void Pop::write_pop(void)
{
	std::ofstream o;
	o.open( "init.dat" );
	
	for( int count = 0; count < POP_SIZE; count++ )
	{
		population[count] = new Player();
		population[count]->root->generate(DEPTH,NULL,root);
	}

	for( int count = 0; count < POP_SIZE; count++ )
	{
		std::queue<node*> q;
		
		q.push(population[count]->root);

		while( !q.empty() )
		{
			node * temp;
			temp = q.front();
			q.pop();

			if( temp->left != NULL )
			{
				q.push(temp->left);
			}
			if( temp->mid != NULL )
			{
				q.push(temp->mid);
			}
			if( temp->right != NULL )
			{
				q.push(temp->right);
			}

			switch( temp->type )
			{
			case turn_left:
				o << "0\n";
				break;
			case turn_right:
				o << "1\n";
				break;
			case move:
				o << "2\n";
				break;
			case aim:
				o << "3\n";
				break;
			case shoot:
				o << "4\n";
				break;
			case prog3:
				o << "5\n";
				break;
			case prog2:
				o << "6\n";
				break;
			}
		}

		// end of the tree print separating char
		o << "8\n";
	}
}
//*/

Player *Pop::GetIndividual(int pIndex){
	return population[pIndex];
}

void Pop::AddIndividual(Player *i_player){
	if(curIndex < POP_SIZE){
		population[curIndex] = i_player;
		i_player->Evaluate();
		population[curIndex]->Evaluate();
		curIndex++;
	}
}

void Pop::FillFitness(){
	for(int i = 0; i < POP_SIZE; i++){
		population[i]->Evaluate();
	}
}


/*
*	POSSIBLE GLOBAL FUNCTION
*
void Pop::Evaluate(Player *one, Player *two){
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
	while(numSteps > 0){
		if(team1stack.empty()){
			team1 = one->root;
		}
		if(team2stack.empty()){
			team2 = two->root;
		}

		team1stack.push(team1);
		team2stack.push(team2);
		while(!team1stack.empty() && !team2stack.empty()){
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
						double x1 = one->GetX();
						double y1 = one->GetY();
						double x2 = two->GetX();
						double y2 = two->GetY();

						double angle = atan( (y2-y1)/(x2-x1) );

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
						numSteps--;
						break;
					case shoot:
						one->Shoot(two);
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
						double x1 = two->GetX();
						double y1 = two->GetY();
						double x2 = one->GetX();
						double y2 = one->GetY();

						double angle = atan( (y2-y1)/(x2-x1) );

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
						numSteps--;
						break;
					case shoot:
						two->Shoot(one);
						numSteps--;
						break;
				}
			}

			team1 = team1stack.top();
			team1stack.pop();
			team2 = team2stack.top();
			team2stack.pop();

			//DRAW ENVIRONMENT
		}


	}
	one->Normalize_Fitness();
	two->Normalize_Fitness();
}
*/