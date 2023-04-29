#include <utility>
#include <vector>
#include<cmath>
#include "graphics.h"
using namespace std;
typedef struct ma{
   int x, y;
   IMAGE * bmp;
}ma;
const int width = 800, height = 600;
const int le = 13, wi = 7, he = 5;  
const int tileW = 45, tileH = 55;
int begOfX = floor((width - (tileW * le)) / 2);
int begOfY = floor((height - (tileH * wi)) / 2);
vector <pair<int, int>> clickXY;
void core_game();
pair<int, int> click();
int waitclick(int *x1, int *y1, int *x2, int *y2);


int main()
{
   initwindow(width, height, "MAf", 200, 200);
   setbkcolor(RED);
   clearviewport();
   getch();
   //clearviewport();
   ma logo, m2;
   logo.bmp = loadBMP("tile2.gif");
   logo.x = 400;
   logo.y = 300;
   m2.bmp = loadBMP("tile6.bmp");
   m2.x = 300;
   m2.y = 300;
   putimage(logo.x, logo.y, logo.bmp, COPY_PUT);
    putimage(m2.x, m2.y, m2.bmp, TRANSPARENT_PUT);
   
   core_game();
   //clearviewport();
   
   
   while(1) {
      getch();
      }
   return 0;
}


void core_game()
{
   int g1, g2;
   g1 = mousex();
   g2 = mousey();
            for (int i = 0; i < 2; i++){
               clickXY.push_back(click());
               //printf("%d %d\n", clickXY[i].first, clickXY[i].second);
               
            }
            printf("%d %d\n", clickXY[0].first, clickXY[0].second);
            printf("%d %d\n", clickXY[1].first, clickXY[1].second);
}   
   
pair<int, int> click()
{/*
      int x, y, i , j;
      if (mousebuttons() == 1){ int g1 = mousex(); int g2 = mousey();}
      while(mousebuttons() == 0){}6
         x = mousex();
         y = mousey();   
         printf("%d %d\n", x, y);
      i = ceil((x - begOfX) / tileW);
      j = ceil((y - begOfY) / tileH);
     return make_pair(i, j);
   */
   int flag = 0, x, y, i, j, x2, y2;       // пока не выбран пункт меню
   do {
         waitclick(&x, &y, &x2, &y2);
         i = ceil((x - begOfX) / tileW);
         j = ceil((y - begOfY) / tileH);
         flag = 1;
   }while(!flag);
   return make_pair(i, j);
      
}

int waitclick(int *x1, int *y1, int *x2, int *y2) {
  int b;
  while((b=mousebuttons())==0) { // ждем нажатия кнопки
     if(kbhit()) return 0; // если нажата клавиша - выйти
  }
  *x1=mousex();
  *y1=mousey();
  while(mousebuttons()==0); // ждем отпускания кнопки
  *x2=mousex();
  *y2=mousey();
  return b;
}