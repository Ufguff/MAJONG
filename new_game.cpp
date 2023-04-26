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
vector<TILE> avl_tile;
auto rd = random_device {}; // для рандомизации раскладки
auto rng = default_random_engine {rd()};
int begOfX = floor((width - (tileW * le)) / 2);
int begOfY = floor((height - (tileH * wi)) / 2) + 50;


TILE library[42];    //библиотка для фишек

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

      for(int k = 0; k < he; k++)
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
            {
               if (Pole[i][j][k].id == 0)  {       
                  Pole[i][j][k].id = layout[0].first;
                  strcpy(Pole[i][j][k].name, library[layout[0].first].name);
                  Pole[i][j][k].i = i;
                  Pole[i][j][k].j = j;
                  Pole[i][j][k].k = k;
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
                  layout.erase(layout.begin());
                  if (Pole[i][j][k].bmp == 0)        { printf("Нет картинки %d %s\n",CON_TILES, Pole[i][j][k].name);   exit(1);}
                  
               } 
            }
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


   shuffle(layout.begin(), layout.end(), rng);        //перемешивание
   
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
      acc_avl();
      click(&i1, &j1);       click(&i2, &j2);
      
      for (int k = he - 1; k >= 0; k--) {
         if(Pole[i1][j1][k].id == -1)      continue;
         else{k1 = k; break;}
         }
         
      for (int k = he - 1; k >= 0; k--)  {
         if(Pole[i2][j2][k].id == -1)      continue;
         else{k2 = k; break;}
         }
      
      if (i1 == i2 && j1 == j2 && k1 == k2)     continue;      //если одна и та же фишка
      
      if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(Pole[i1][j1][k1], Pole[i2][j2][k2])) && Pole[i1][j1][k1].access != false && Pole[i2][j2][k2].access != false)     //удаление
         delete_pair(&Pole[i1][j1][k1], &Pole[i2][j2][k2]);
      
   }
}   

void delete_pair(TILE *tile1, TILE *tile2)  //смещение     
{
      TILE temp;   temp.id = -1;
      gain_access(tile1);       gain_access(tile2);
      *(tile1) = temp;
      *(tile2) = temp;
      CON_TILES -= 2;
      draw_pole();
}

bool is_season(TILE tile1, TILE tile2)
{
   if(tile1.id >= 34 && tile2.id >= 34)  
      return ((tile1.id + 4) == tile2.id || (tile2.id + 4) == tile1.id);
}

void gain_access(TILE *tile1)
{
   int i = tile1->i, j = tile1->j, k = tile1->k;
   
   if (Pole[i + 1][j][k].id != -1 && (i+1) < 9)      Pole[i+1][j][k].access = true;
   else if (Pole[i - 1][j][k].id != -1 && (i - 1) >= 0)        Pole[i-1][j][k].access = true;
}
   
void click(int *i, int *j)
{
   int x, y;
   while(mousebuttons()==1);
   do{
   while(mousebuttons() != 1){
      x = mousex();
      y = mousey();
   }
   while(mousebuttons()==1);    
   }while(!(begOfX <= x && x <= begOfX + (tileW * le)) || !(begOfY <= y && y <= begOfY + (tileH * wi)));
   
   *i = ceil((x - begOfX) / tileW);
   *j = ceil((y - begOfY) / tileH);
}

void acc_avl()
{
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].access == true)      avl_tile.push_back(Pole[i][j][k]);
   
   cout << avl_tile.size() / 2 << endl <<endl;
   avl_tile.clear();
}