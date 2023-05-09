#include "menu.h"
#include "new_game.h"

#include "graphics.h"

button but[4];  //обьявление массива кнопок для меню
button logo;    // лого игры для меню
button rule_about;      // кнопка для выведения окна "Правила"/"О программе"

const int buttonW = 280, buttonH = 90;  //размеры кнопок меню
const int mid_width = width / 2, mid_height = height / 2;       

void begin()
{
   int st = 1;
   init_menu();
   do{
      st = menu(st);
      switch(st){
         case 1: new_game(); break;
         case 2: rules(); break;
         case 3: about(); break;
      }
   } while(st != 4);
   close_game(); 
}

void init_menu(){
   setbkcolor(ELVOLT);
   char file[30];
   for(int i=0; i <4; i++){
         but[i].dx = 280; but[i].dy = 90; 
         but[i].x = (width / 2) - (buttonW / 2); but[i].y = 180 + i * (but[i].dy+10);   
         sprintf(file,".//MENU_STUFF/menu%d.bmp", i+1);
         but[i].bmp = loadBMP(file);
   }
   logo.dx = 150; logo.dy = 100;
   logo.x = 60; logo.y = 5;
   logo.bmp = loadBMP(".//MENU_STUFF/menu_majong.gif");
}



void drawmenu() // отрисовка кнопок и лого
{
   clearviewport();
   putimage(logo.x, logo.y, logo.bmp, TRANSPARENT_PUT);
   for(int i=0; i <4; i++){
        putimage(but[i].x , but[i].y, but[i].bmp, COPY_PUT); 
   }
   swapbuffers();
}


int menu(int st)
{
   int flag = 0, x, y;       // пока не выбран пункт меню
   drawmenu();
   do {
      while(mousebuttons() != 1){
         x = mousex();
         y = mousey();}
         for(int i = 0; i < 4; i++){
            if (x >= but[i].x && x <= but[i].x + but[i].dx && y >= but[i].y && y <= but[i].y + but[i].dy)
            {flag = 1; st = i+1;  break; }
            }
   }while(!flag);
   return st;
}

void rules_about(int st)
{
   clearviewport();
   if (st == 2) rule_about.bmp = loadBMP(".//MENU_STUFF/rules.bmp");
   else rule_about.bmp = loadBMP(".//MENU_STUFF/about.bmp");
   putimage(0, 0, rule_about.bmp, COPY_PUT);
   swapbuffers();
   getch();
   begin();
}
/*
void about()
{
   clearviewport();
   
   putimage(0, 0, rule_about.bmp, COPY_PUT);
   swapbuffers();
   getch();
   begin();   
}
*/

void close_game(){      closegraph();   }       // закрытие графического окна