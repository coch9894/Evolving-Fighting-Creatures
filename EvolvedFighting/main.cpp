#include "Pop.h"
#include "GeneticProgram.h"
#include "util.h"
#include "Bullet.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
 
int main(int argc, char **argv)
{
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
 
   al_init_primitives_addon();

   al_clear_to_color(al_map_rgb(1,1,1));
 
   Pop *p = new Pop();
   GeneticProgram *GP = new GeneticProgram();
   p->load_pop();
   GP->Evaluate(p->GetIndividual(5), p->GetIndividual(10), true);

   system("PAUSE");
   
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