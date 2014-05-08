#include "Pop.h"
#include "GeneticProgram.h"
#include "util.h"
#include "Bullet.h"
#include <stdio.h>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
 
int main(int argc, char **argv)
{
	srand(time(NULL));
   ALLEGRO_DISPLAY *display = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }
 
   std::ofstream outputFile;
   al_init_primitives_addon();

   al_clear_to_color(al_map_rgb(1,1,1));
 
   GeneticProgram *GP0v1 = new GeneticProgram(0, 1);	//MAXMAX v MINMAX
   GeneticProgram *GP0v2 = new GeneticProgram(0, 2);	//MAXMAX v MINMIN
   GeneticProgram *GP0v3 = new GeneticProgram(0, 3);	//MAXMAX v MAXMIN
   GeneticProgram *GP1v2 = new GeneticProgram(1, 2);	//MINMAX v MINMIN
   GeneticProgram *GP1v3 = new GeneticProgram(1, 3);	//MINMAX v MAXMIN
   GeneticProgram *GP2v3 = new GeneticProgram(2, 3);	//MINMIN v MAXMIN
   //GP->Evaluate(p->GetIndividual(9), p->GetIndividual(7), true);
   outputFile.open("output.txt");
   GP0v1->Search();
   outputFile << "MAXMAX v MINMAX" << std::endl;
   outputFile << "Generation Team Normal_Fitness" << std::endl;
   for(int i = 0; i < ELITE_SIZE; i++){
	   outputFile << i*5 << " " << GP0v1->BestPop[i]->Team << " " << GP0v1->BestPop[i]->getFitness() << std::endl;
   }
   GP0v2->Search();
   outputFile << "MAXMAX v MINMAX" << std::endl;
   outputFile << "Generation Team Normal_Fitness" << std::endl;
   for(int i = 0; i < ELITE_SIZE; i++){
	   outputFile << i*5 << " " << GP0v2->BestPop[i]->Team << " " << GP0v2->BestPop[i]->getFitness() << std::endl;
   }
   GP0v3->Search();
   outputFile << "MAXMAX v MINMAX" << std::endl;
   outputFile << "Generation Team Normal_Fitness" << std::endl;
   for(int i = 0; i < ELITE_SIZE; i++){
	   outputFile << i*5 << " " << GP0v3->BestPop[i]->Team << " " << GP0v3->BestPop[i]->getFitness() << std::endl;
   }
   GP1v2->Search();
   outputFile << "MAXMAX v MINMAX" << std::endl;
   outputFile << "Generation Team Normal_Fitness" << std::endl;
   for(int i = 0; i < ELITE_SIZE; i++){
	   outputFile << i*5 << " " << GP1v2->BestPop[i]->Team << " " << GP1v2->BestPop[i]->getFitness() << std::endl;
   }
   GP1v3->Search();
   outputFile << "MAXMAX v MINMAX" << std::endl;
   outputFile << "Generation Team Normal_Fitness" << std::endl;
   for(int i = 0; i < ELITE_SIZE; i++){
	   outputFile << i*5 << " " << GP1v3->BestPop[i]->Team << " " << GP1v3->BestPop[i]->getFitness() << std::endl;
   }
   GP2v3->Search();
   outputFile << "MAXMAX v MINMAX" << std::endl;
   outputFile << "Generation Team Normal_Fitness" << std::endl;
   for(int i = 0; i < ELITE_SIZE; i++){
	   outputFile << i*5 << " " << GP2v3->BestPop[i]->Team << " " << GP2v3->BestPop[i]->getFitness() << std::endl;
   }
   outputFile.close();

	al_rest(1);
	/*for(int i = 0; i < POP_SIZE-1; i++){
		for(int j = i+1; j < POP_SIZE; j++){
			GP->Evaluate(p->GetIndividual(i), p->GetIndividual(j), true);
			std::cout << "Team left " << i << ":: " << p->population[i]->GetSuccess() << "/" << p->population[i]->GetFail()
					  << " Team right " << j << ":: " << p->population[j]->GetSuccess() << "/" << p->population[j]->GetFail() << std::endl;
			system("PAUSE");
		}
	}*/
   
   /*
   Player *p = new Player(480, 240);
   Player *o = new Player(160, 240);
   p->DrawPlayer();
   o->DrawPlayer();
   Bullet *b = new Bullet(p->GetDirection(), p->GetX(), p->GetY());
   b->DrawBullet();
   al_flip_display();
   */
 
   al_destroy_display(display);
 
   return 0;
}