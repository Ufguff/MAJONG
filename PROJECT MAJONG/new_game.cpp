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
int Pole[le][wi][he];     // под пирамиду
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
               if((i == 4 && j == 3) || (i == 4 && j == 2))     Pole[i][j][k] = 0;
               else     Pole[i][j][k] = -1;
               break;
            case 3:
               if ((i >= 3 && i <= 5) && (j >= 2 && j <= 4))    Pole[i][j][k] = 0;
               else     Pole[i][j][k] = -1;
               break;
            case 2:
               if ((i >= 2 && i <= 6) && (j >= 1 && j <= 5))    Pole[i][j][k] = 0;
               else     Pole[i][j][k] = -1;
               break;
            case 1:
               if ((i >= 2 && i <= 6))  Pole[i][j][k] = 0;
               else if ((i == 1) && (j >= 1 && j <= 5) || (i == 7) && (j >= 1 && j <= 5))       Pole[i][j][k] = 0;
               else     Pole[i][j][k] = -1;
               break;
            case 0:
               Pole[i][j][k] = 0;   // 2            10
               break;
            }
         
         }
            debug();// печать
            
            printf("\n//==============заполнение маджонга фишками\n");
      TILE tile;
      for(int k = 0; k < he; k++)
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
            {
               if (Pole[i][j][k] == 0)  {       
                  //printf("%d %d\n", layout.size(), layout[0].first);
                  Pole[i][j][k] = layout[0].first;
                  tile.id = layout[0].first;
                  strcpy(tile.name, library[layout[0].first].name);
                  tile.i = i;
                  tile.j = j;
                  tile.k = k;
                  tile.x = begOfX + (i * tileW) + k*2;
                  tile.y = begOfY + (tileH * j) - k*2;
                  tile.bmp = library[layout[0].first].bmp;
                  switch(k){
                  case 4:
                     tile.access = true;
                     break;
                  case 3:
                     if ((i == 3 && i == 5))    tile.access = true;
                  
                     break;
                  case 2:
                     if ((i == 2 && i == 6))    tile.access = true;

                     break;
                  case 1:
                     if (i == 1 || i == 7)      tile.access = true;
                     else if((i == 2 || i == 6) && (j == 0 || j == 6))  tile.access = true;

                     break;
                  case 0:
                     if (i == 0 || i == 8)    tile.access = true;

                     break;
                  }
                  
                  if (tile.bmp == 0)        { printf("Нет картинки %d %s\n",CON_TILES, tile.name);   exit(1);}
                  layout.erase(layout.begin());
                  tiles.push_back(tile);
               } 
            }
            
            /*
            //всякие дебаги
            debug();
            if(layout.size() == 0) printf("YYYEEEEAH");
            else {
               printf(":(\n");
               for(int i = 0; i < layout.size(); i++)       {  printf("%d: %d    2: %d\n", i+1, layout[i].first, layout[i].second);}
            }   
            */
   }
   
void draw_pole(){
   clearviewport();
   
   for(int i = 0; i < CON_TILES; i++){
        putimage(tiles[i].x, tiles[i].y, tiles[i].bmp, TRANSPARENT_PUT);      
   }
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
         if(Pole[i1][j1][k] == -1)      continue;
         else{printf("\n%d", Pole[i1][j1][k]);  k1 = k; break;}
         }
         
      for (int k = he - 1; k >= 0; k--)  {
         if(Pole[i2][j2][k] == -1)      continue;
         else{printf("\n%d", Pole[i2][j2][k]);  k2 = k; break;}
         }
      
      if (i1 == i2 && j1 == j2 && k1 == k2)    {clickXY.clear();        continue;}      //если одна и та же фишка
         
      printf("---- %d %d ----- %d %d\n", Pole[i1][j1][k1], Pole[i2][j2][k2], k1, k2);

      //реализовать фишки времен года
      // реализация границ определения ??????????
      // время, очки
      
      if (Pole[i1][j1][k1] == Pole[i2][j2][k2])     //добавить удаление картинок
      {
            delete_pair(Pole[i1][j1][k1], i1, j1, k1, Pole[i2][j2][k2], i2, j2, k2);
      }
      
      clickXY.clear();
   }
}   

void delete_pair(int id1,int i1, int j1, int k1, int id2, int i2, int j2, int k2)  //некоторые активирует, надо отладить куда true + смещение     
{
   vector<TILE> temp;
   for(int i = 0; i < tiles.size(); i++)
   {
      if (!((tiles[i].id == Pole[i1][j1][k1] && tiles[i].i == i1 && tiles[i].j == j1 && tiles[i].k == k1) || 
         (tiles[i].id == Pole[i2][j2][k2] && tiles[i].i == i2 && tiles[i].j == j2 && tiles[i].k == k2)))       temp.push_back(tiles[i]);
      else { 
         if(tiles[i].access != true)
         {
            temp.clear();
            return;
         }
      }
   }
   tiles = temp;
   Pole[i1][j1][k1] = -1; 
   Pole[i2][j2][k2] = -1;
   CON_TILES -= 2;
   draw_pole();
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
            {   printf("%3d ", Pole[i][j][k]);   }
            printf("\n");       
            }
            printf("\n\n");
         }
            
   }