#include<iostream>
#include<vector>
#include<random>
#include <algorithm>
#include <utility>
#include <string>
#include<cmath>

#include "menu.h"
#include "new_game.h"
#include "graphics.h"

using namespace std;
const int le = 9, wi = 7, he = 5;      // размеры пирамиды
TILE Pole[le][wi][he];     // под пирамиду
int CON_TILES = 144;
const int tileW = 45, tileH = 55;
vector <pair<int, int>> layout;
vector <pair<int, int>> clickXY;
auto rd = random_device {}; // для рандомизации раскладки
auto rng = default_random_engine {rd()};
int begOfX = floor((width - (tileW * le)) / 2);
int begOfY = floor((height - (tileH * wi)) / 2);


TILE library[42];    //библиотка для фишек
vector<TILE> tiles;
void new_game(){
   init_menu_pole();
   
   init_game();
   draw_pole(); //вывод маджонга
   core_game();

   
   while(1)     getch();    // чтобы не выходило
}
   
   void maj_init()
   {
      //============обьявление маджонга
      for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
         {
            switch(k){
            case 4:
               if((i == 4 && j == 3) || (i == 4 && j == 2))     Pole[i][j][k].id = 0;
               else     Pole[i][j][k].id = -1;
               break;
            case 3:
               if ((i >= 3 && i <= 5) && (j >= 2 && j <= 4))    Pole[i][j][k].id = 0;
               else     Pole[i][j][k].id = -1;
               break;
            case 2:
               if ((i >= 2 && i <= 6) && (j >= 1 && j <= 5))    Pole[i][j][k].id = 0;
               else     Pole[i][j][k].id = -1;
               break;
            case 1:
               if ((i >= 2 && i <= 6))  Pole[i][j][k].id = 0;
               else if ((i == 1) && (j >= 1 && j <= 5) || (i == 7) && (j >= 1 && j <= 5))       Pole[i][j][k].id = 0;
               else     Pole[i][j][k].id = -1;
               break;
            case 0:
               Pole[i][j][k].id = 0;   // 2            10
               break;
            }
         
         }
            //debug();// печать
            
            printf("\n//==============заполнение маджонга фишками\n");
      for(int k = 0; k < he; k++)
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
            {
               if (Pole[i][j][k].id == 0)  {       
                  Pole[i][j][k].id = layout[0].first;
                  strcpy(Pole[i][j][k].name, library[layout[0].first].name);
                  Pole[i][j][k].x = begOfX + (i * tileW) + k*2;
                  Pole[i][j][k].y = begOfY + (tileH * j) - k*2;
                  Pole[i][j][k].bmp = library[layout[0].first].bmp;
                  switch(k){
                  case 4:
                     if ((i == 4 && j == 3) || (i == 4 && j == 2)) Pole[i][j][k].access = true;
                     break;
                  case 3:
                     if ((i == 3 || i == 5))    Pole[i][j][k].access = true;
                     else Pole[i][j][k].access = false;
                     break;
                  case 2:
                     if ((i == 2 || i == 6))    Pole[i][j][k].access = true;
                     else Pole[i][j][k].access = false;
                     break;
                  case 1:
                     if (i == 1 || i == 7)      Pole[i][j][k].access = true;
                     else if((i == 2 || i == 6) && (j == 0 || j == 6))  Pole[i][j][k].access = true;
                     else Pole[i][j][k].access = false;
                     break;
                  case 0:
                     if (i == 0 || i == 8)    Pole[i][j][k].access = true;
                     else Pole[i][j][k].access = false;
                     break;
                  }
                  
                  cout << Pole[i][j][k].access << endl;
                  if (Pole[i][j][k].bmp == 0)        { printf("Нет картинки %d %s\n",CON_TILES, Pole[i][j][k].name);   exit(1);}
                  layout.erase(layout.begin());
                  tiles.push_back(Pole[i][j][k]);
               } 
            }
            
            /*
            //всякие дебаги
            //debug();
            
            if(layout.size() == 0) printf("YYYEEEEAH");
            else {
               printf(":(\n");
               for(int i = 0; i < layout.size(); i++)       {  printf("%d: %d    2: %d\n", i+1, layout[i].first, layout[i].second);}
            }   
            */
   }
   
void draw_pole(){
   clearviewport();
   for(int k = 0; k < he; k++)
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
                 {      if (Pole[i][j][k].id != -1) putimage(Pole[i][j][k].x, Pole[i][j][k].y, Pole[i][j][k].bmp, TRANSPARENT_PUT);}
   }


void init_game(){
   // создание маджонга
   for (int i = 0; i < 42; i++) { // создание пар
         library[i].id = i;
         if (i < 34)        library[i].count = 4; 
         else library[i].count = 1; 
         sprintf(library[i].name, ".//TILES/tile%d.bmp", i+1);    
         library[i].bmp = loadBMP(library[i].name); 
	}
        
        
   for (int i = 0; i < 42; i++) { for (int j = 1; j <= library[i].count; j++) {    layout.push_back(make_pair(library[i].id, j));     } }
   cout << layout.size() <<endl;


   shuffle(layout.begin(), layout.end(), rng);        //перемешивание
      
   //  откладка
   //for(int i = 0; i < layout.size(); i++)       { printf("%d: 1 - %d    2 - %d\n", i+1, layout[i].first, layout[i].second); }

   maj_init();
   }

void init_menu_pole(){
   setbkcolor(AVOCADO); 
   clearviewport();
   // здесь должны быть кнопки меню а также время и очки //
   }

void core_game()
{
   int i1, i2, j1, j2, k1, k2;
   
   while(1)
   {
      for (int i = 0; i < 2; i++)
      {
         click();
         printf("%d %d\n", clickXY[i].first, clickXY[i].second);
      }
      printf("\n");
      
      i1 = clickXY[0].first;       i2 = clickXY[1].first;          j1 = clickXY[0].second;         j2 = clickXY[1].second;
      
      for (int k = he - 1; k >= 0; k--) {
         if(Pole[i1][j1][k].id == -1)      continue;
         else{printf("\n%d", Pole[i1][j1][k].id);  k1 = k; break;}
         }
         
      for (int k = he - 1; k >= 0; k--)  {
         if(Pole[i2][j2][k].id == -1)      continue;
         else{printf("\n%d", Pole[i2][j2][k].id);  k2 = k; break;}
         }
      
      if (i1 == i2 && j1 == j2 && k1 == k2)    {clickXY.clear();        continue;}      //если одна и та же фишка
         
      // реализация границ определения ??????????
      // время, очки
      
      
      if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(Pole[i1][j1][k1], Pole[i2][j2][k2])) && Pole[i1][j1][k1].access != false && Pole[i2][j2][k2].access != false)     //удаление
         delete_pair(&Pole[i1][j1][k1], &Pole[i2][j2][k2]);
      
      clickXY.clear();
   }
}   

void delete_pair(TILE *tile1, TILE *tile2)  //смещение     
{
      TILE temp;   temp.id = -1;
      *(tile1) = temp;
      *(tile2) = temp;
      CON_TILES -= 2;
      draw_pole();
}

bool is_season(TILE tile1, TILE tile2)  //всё гуд но нужно протестить
{
   if(tile1.id >= 34 && tile2.id >= 34)  return ((tile1.id + 4) == tile2.id || (tile2.id + 4) == tile1.id);
}

   
void click()
{
   int x, y, i , j;
   while(mousebuttons()==1);
   while(mousebuttons() != 1){
      x = mousex();
      y = mousey();
   }
   while(mousebuttons()==1);
   i = ceil((x - begOfX) / tileW);
   j = ceil((y - begOfY) / tileH);
   clickXY.push_back(make_pair(i, j));
}

   void debug()
   {
      
      for(int k = 0; k < he; k++){
         for(int j = 0; j < wi; j++){
            for(int i = 0; i < le; i++)
            {   cout << Pole[i][j][k].access << "       ";   }
            printf("\n");       
            }
            printf("\n\n");
         }
            
   }