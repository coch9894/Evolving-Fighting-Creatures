#include "Pop.h"
#include <stdio.h>
#include <allegro5/allegro.h>
 
int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   Pop* p = new Pop();

   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }
 
   al_clear_to_color(al_map_rgb(1,1,1));
 
   al_flip_display();
 
   al_rest(10.0);
 
   al_destroy_display(display);
 
   return 0;
}