#include "Pop.h"
#include <queue>

Pop::Pop(void)
{
	curIndex = 0;
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
			temp = new node(false);

			switch( atoi(str) )
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

		population[count] = new Player(false);
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
				if( temp->left->type >= prog3 )
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
					if( temp->mid->type >= prog3 )
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
				if( temp->right->type >= prog3 )
					fill.push(temp->right);
			}
			else
			{
				temp->right = NULL;
			}
		}

	}
	i.close();
}


void Pop::write_pop(void)
{
	std::ofstream o;
	o.open( "init.dat" );
	
	for( int count = 0; count < POP_SIZE; count++ )
	{
		population[count] = new Player(true);
		//population[count]->root->generate(DEPTH,NULL,root);
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
		//i_player->Evaluate();
		//population[curIndex]->Evaluate();
		curIndex++;
	}
}

void Pop::FillFitness(){
	for(int i = 0; i < POP_SIZE; i++){
		//population[i]->Evaluate();
	}
}

void Pop::ResetFitness(){
	for(int i = 0; i < POP_SIZE; i++){
		fitnessPopulation[i] = 0;
	}
}

void Pop::ResetPopulation(){
	curIndex = 0;
	for(int i = 0; i < POP_SIZE; i++){
		population[i] = NULL;
		delete population[i];
	}
	ResetFitness();
}