#include "menu.h"
#include "new_game.h"

void init();
void rules();
void about();
void close_game();

int main()
{
   int st = 1;
   init();
   do{
      st = menu(st);
      switch(st){
         case 1: new_game(); break;
         case 2: rules(); break;
         case 3: about(); break;
      }
   } while(st != 4);
   close_game(); 
   return 0;   
}

void init()    // инициализация
{
   initwindow(width, height, "Majong", 200, 200, true);
   setbkcolor(ELVOLT);
   // cleardevice();
   init_menu();
}

void rules(){}

void about(){}

void close_game(){      closegraph();   }


