#include "menu.h"

#include "graphics.h"

button but[4];
button logo;
button ins;


const int buttonW = 280, buttonH = 90;  //размеры кнопок меню
const int mid_width = width / 2, mid_height = height / 2;

void init_menu(){
   char file[11];
   for(int i=0; i <4; i++){
         but[i].dx = 280; but[i].dy = 90; 
         but[i].x = (width / 2) - (buttonW / 2); but[i].y = 180 + i * (but[i].dy+10);   
         sprintf(file,"menu%d.bmp", i+1);
         but[i].bmp = loadBMP(file);
   }
   logo.dx = 150; logo.dy = 100;
   logo.x = mid_width / 2; logo.y = 50;
   ins.dx = 120; ins.dy = 100;
   ins.x = mid_width + mid_width / 2; ins.y = 90;
   logo.bmp = loadBMP("logo.bmp");
   ins.bmp = loadBMP("ins.bmp");
}



void drawmenu() // отрисовка кнопок и лого
{
   clearviewport();
   putimage(logo.x, logo.y, logo.bmp, COPY_PUT);
   putimage(ins.x, ins.y, ins.bmp, COPY_PUT);
   for(int i=0; i <4; i++){
        putimage(but[i].x , but[i].y, but[i].bmp, COPY_PUT); // imageresize
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