#include<iostream>
#include<vector>
#include<random>
#include <algorithm>
#include <utility>
#include <cmath>
#include <ctime>

#include "menu.h"
#include "new_game.h"
#include "graphics.h"

using namespace std;
const int le = 9, wi = 7, he = 5;      // ������� ������� ��������
TILE Pole[le][wi][he];     // ���������� ����������� �������
const int tileW = 45, tileH = 55;       //������� ����� � ��������
vector <pair<int, int>> layout; //��������� �����

vector <TILE> for_find; // ������������� ������ ��� ������ find_tiles
pair<TILE,TILE> founds; // ��������� ���� ��� find_tiles
// ��� ������������ ���������
auto rd = random_device {}; 
auto rng = default_random_engine {rd()};
//
int begOfX = floor((width - (tileW * le)) / 2) - 50; //��������� ���������� �� X ��� ������ ���� ��������
int begOfY = floor((height - (tileH * wi)) / 2) + 30;   //��������� ���������� �� Y ��� ������ ���� ��������
int pairAVL, CON_TILES; //���������� ��������� �����, ���������� ���� �����
button lose, win, gMenu, findTiles;       //���� ��� ������ ��������� ��� ��������
TILE library[42];    //��������� ��� �����
bool pereB; //��� ���������/���������� �������
extern bool contGame;
clock_t t0;
int baseTime, seconds;


void new_game(){        //��������� ������� � ������ ����
   settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
   
   if (!contGame){
   CON_TILES = 144;
   baseTime = 0;
   seconds = 0;
   init_game();
   }
   draw_pole(); 
   core_game();
}
   
void maj_init() //��������������� �������� ���� � ��� ����������
{
   for(int k = 0; k < he; k++)
   for(int j = 0; j < wi; j++)
      for(int i = 0; i < le; i++)
      {
         Pole[i][j][k].id = -1; //���� �������� id ����� -1 -- ��� ������� ����������
         switch(k){     //������������ ���� ��� ����� ������ ����
         case 4:
            if((i == 4 && j == 3) || (i == 4 && j == 2))     Pole[i][j][k].id = 0;      //���� id ����� 0 -- ������� ��������
            break;
         case 3:
            if ((i >= 3 && i <= 5) && (j >= 2 && j <= 4))    Pole[i][j][k].id = 0;
            break;
         case 2:
            if ((i >= 2 && i <= 6) && (j >= 1 && j <= 5))    Pole[i][j][k].id = 0;
            break;
         case 1:
            if ((i >= 2 && i <= 6))  Pole[i][j][k].id = 0;
            else if ((i == 1) && (j >= 1 && j <= 5) || (i == 7) && (j >= 1 && j <= 5))       Pole[i][j][k].id = 0;
            break;
         case 0:
            Pole[i][j][k].id = 0;   
            break;
         }
      }
      //���������� ������ ��������� ��� ���������� � �������, ���������� �� ���� � ����� ��� ���������� ��������
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
               Pole[i][j][k].x = begOfX + (i * tileW) - k*4 + 10;
               Pole[i][j][k].y = begOfY + (tileH * j) + k*4;
               Pole[i][j][k].bmp = library[layout[0].first].bmp;
               layout.erase(layout.begin()); 
               } 
         }
         
   acc_avl();     //�������� ��������� ��� �����
}
   
void draw_pole(){       //������������ ����� �� ����, � ����� ������� �������� � ������� ��� ��������
   char output[50];
   setVSPage();
   clearviewport();
   setcolor(WHITE);
   sprintf(output, "�������� �����: %d", CON_TILES);    // ����� ���������� �����
   outtextxy(350, 30, output);
   sprintf(output, "�������� �����: %d", pairAVL);      // ����� ���������� �����
   outtextxy(560, 30, output); 
   sprintf(output, "�����: %02d:%02d", (seconds) / 60, (seconds) % 60); // ����� ����������� ��������� ����
   outtextxy(210 , 30, output);
   
   for(int k = 0; k < he; k++)  // ��������� �������� �����
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
                 {      
                    if (Pole[i][j][k].id != -1) {
                     putimage(Pole[i][j][k].x, Pole[i][j][k].y, Pole[i][j][k].bmp, TRANSPARENT_PUT);}
                  }
   putimage(10, 10, gMenu.bmp);
   putimage(700, 300, findTiles.bmp);
   setACPage();
   }


void init_game(){       // ������������� ���������� � ���������
   setbkcolor(AVOCADO); 
   clearviewport();
   lose.bmp = loadBMP("./MENU_STUFF/lose.bmp");
   win.bmp = loadBMP("./MENU_STUFF/win.bmp");
   gMenu.bmp = loadBMP("./MENU_STUFF/gMenu.bmp");
   findTiles.bmp = loadBMP("./MENU_STUFF/find.bmp");
   for (int i = 0; i < 42; i++) { // �������� ���������� �����
         library[i].id = i;
         if (i < 34)        library[i].count = 4; 
         else library[i].count = 1; 
         sprintf(library[i].name, "./TILES/tile%d.bmp", i+1);    
         library[i].bmp = loadBMP(library[i].name); 
   }
        
   for (int i = 0; i < 42; i++) { for (int j = 1; j <= library[i].count; j++) {    layout.push_back(make_pair(library[i].id, j));     } }       //�������� ���������
   
   shuffle(layout.begin(), layout.end(), rng);        //���������� ������������(������������� ���������)
   maj_init();
   }

void core_game()        // �������� ������� ����
{
   t0 = clock();       
   int i1, i2, j1, j2, k1, k2;  //��� ���������� ������� � �������
   while(1)
   {
         if (pairAVL == 0)    {end();   if(pereB)       {pereB = false; break; }}
         else{
            if(definition_XY(&i1, &j1, &k1))       break;
            
            if(definition_XY(&i2, &j2, &k2))       break;
            delay(300); 
            if (i1 == i2 && j1 == j2 && k1 == k2)     {    draw_pole();    continue;   }      //���� ���� � �� �� ����� �� ����������
               
            //���� ����� ��������� ��� ��� ���������� ��� ��������
            if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(Pole[i1][j1][k1].id, Pole[i2][j2][k2].id)) && is_avalible(&Pole[i1][j1][k1]) && is_avalible(&Pole[i2][j2][k2])){     
               delete_pair(&Pole[i1][j1][k1], &Pole[i2][j2][k2]);  // �������� ����� �� �������
               if (CON_TILES != 0)      acc_avl(); //�������� ��������� ��� �����
            }
      }
      
      if(CON_TILES != 0)     draw_pole();   //��������� ����
      else {victory();       break;}
   }
}

bool definition_XY(int *i, int *j, int *k)      // ����������� ��������� � �������
{
   (*k) = -1;
   if(click(i, j))      return true;         // ����������� ��������� �� XY � � �������
   for (int kn = he - 1; kn >= 0; kn--) {       // ����������� �� ����� ����� ��������� �����
      if(Pole[*i][*j][kn].id == -1)      continue;
      else{(*k) = kn; break;}
      }
   if (!is_avalible(&Pole[*i][*j][*k]))  return false;
   if (*k != -1){setcolor(WHITE);       border(&Pole[*i][*j][*k]);}
   return false;
}

void delete_pair(TILE *tile1, TILE *tile2)  //  �������� �����
{
   TILE temp;   temp.id = -1;
   *(tile1) = temp;
   *(tile2) = temp;
   CON_TILES -= 2;
}

bool is_season(int tile1, int tile2)  // �������� �������� �� �����
{
   if(tile1 >= 34 && tile2 >= 34)  return ((tile1 + 4) == tile2 || (tile2 + 4) == tile1);
   return false;
}

bool is_avalible(TILE* tile1)   //�������� �� �����
{
   int i = tile1->i, j = tile1->j, k = tile1->k;
   if (((k == (he - 1)) || Pole[i][j][k+1].id == -1) && (( i == le - 1 || Pole[i + 1][j][k].id == -1) || (i == 0 || Pole[i - 1][j][k].id == -1)))     return true;
   return false;
}
   
bool click(int *i, int *j)      // ����������� ����� ����� ������ ������������
{
   int x, y;    // ��������� ���������
   do{
      while(mousebuttons() != 1){       //������� � ����� �����������
         if (mousebuttons() != 1)       stopwatch();
         x = mousex();
         y = mousey();
         }
      while(mousebuttons()==1);   //����� ����� ����� � �������
      
      if (x >= 10 && x <= 100 && y >= 10 && y <= 55){
         contGame = true;
         seconds += baseTime % 60;
         return true;
         }      // ����� � ����
      if (x >= 700 && x <= 750 && y >= 300 && y <= 350){find_tiles();}  // ���������� ���
   }while(!(begOfX <= x && x <= begOfX + (tileW * le)) || !(begOfY <= y && y <= begOfY + (tileH * wi)));
   if ((x < begOfX || x > begOfX + le*tileW) && (y < begOfY || y > begOfY + wi*tileH)) click(i, j);
   *i = ceil((x - begOfX) / tileW);
   *j = ceil((y - begOfY) / tileH);
   return false;
}

void acc_avl()  //�������� ��������� ��� �����
{
   vector<int> avl_tile;   //������ ��������� ����� ��� �� ����������� ��������
   int i = 0;
   pairAVL = 0;
   //��������� ���� ��������� ����� � ������
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].id != -1 && is_avalible(&Pole[i][j][k]))      
            {avl_tile.push_back(Pole[i][j][k].id);      for_find.push_back(Pole[i][j][k]);}
   
   sort(begin(avl_tile), end(avl_tile));        //���������� �� �����������
   
   for(int i = 0; i < for_find.size() - 1; i++) // ���������� 1 ���� ����� � ��������� � pair ��� ������� find_tiles()
      for(int j = i + 1; j < for_find.size(); j++)
         if (for_find[i].id == for_find[j].id || is_season(for_find[i].id, for_find[j].id))  {founds = make_pair(for_find[i], for_find[j]);   break;}
         
   while((i + 1) < avl_tile.size())     //������� ��������� ���
   {
      if (avl_tile[i] == avl_tile[i + 1] || is_season(avl_tile[i], avl_tile[i+1])){pairAVL++;    avl_tile.erase(avl_tile.begin() + i, avl_tile.begin() + i + 2);}
      else      i++;    // ����� ������ ���� ������ ��� ����� ����
   }
   for_find.clear();
}

void mix_at_end()       // ������������� ��� ������������ ������
{
   TILE temp;
   temp.id = 0;
   vector <TILE> curTiles;
   //�������� �������
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].id != -1)     {curTiles.push_back(Pole[i][j][k]);     Pole[i][j][k].id = 0;}
             
    
   shuffle(curTiles.begin(), curTiles.end(), rng);      //����� �������������

   //�������������� �������� � ���������
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].id == 0)   {
               Pole[i][j][k] = curTiles[0];
               Pole[i][j][k].i = i;
               Pole[i][j][k].j = j;
               Pole[i][j][k].k = k;
               Pole[i][j][k].x = begOfX + (i * tileW) - k*4;
               Pole[i][j][k].y = begOfY + (tileH * j) + k*4;
               curTiles.erase(curTiles.begin());
               }
               
   acc_avl();     
   draw_pole();
}

void border(TILE *tile) // ������� ��� ������� �� �����(�� �������� � swapbuffers())
{
   rectangle(tile->x, tile->y, tile->x + tileW, tile->y + tileH);
}

void find_tiles()       // ���������� ����� ���� ������������ �� �� �����
{
   setcolor(PROMPT);
   border(&founds.first);        border(&founds.second);
   TILE temp;   temp.id = -1;
   temp.x = 800;        temp.y = 600;
   founds.first = temp;
   founds.second = temp;
}
void printSW()  // ����� �����������
{
   setcolor(WHITE);
   char s[50];
   sprintf(s, "�����: %02d:%02d", (baseTime + seconds) / 60, (baseTime + seconds) % 60);
   outtextxy(210 , 30, s);
}
void stopwatch()        // ���������� �����������
{
   int dt = 0;
   clock_t t1 = clock();
   baseTime = (int)((double)(t1 - t0) / CLOCKS_PER_SEC);
   if (dt != baseTime){
   printSW();
   dt = baseTime;
   }
}

void end()      //���� ��� ������������� ��������� �����
{
   button but[3];
   char s[25];
   setVSPage();
   clearviewport();
   for(int i = 0; i < 3; i++)   // ���� ��������� ������ � �� �����
   {
      sprintf(s, "./MENU_STUFF/exit%d.bmp", i);
      if(i != 0)
      {
         but[i].dx = 280;        but[i].dy = 90;
         but[i].x = 100 + but[i].dx*(i - 1) + (i - 1)*40;       but[i].y = 450;
      }
      but[i].bmp = loadBMP(s);
   }
   for(int i = 0; i < 3; i++)   // ����� ������ ��������� � ������ ��� ������
   {
      if (i == 0)       putimage(0, 0, but[i].bmp, COPY_PUT);
      else putimage(but[i].x, but[i].y, but[i].bmp, COPY_PUT);
   }
   
   setACPage();
   
   int flag = 0, x, y, st = 0;       //����� ������ ���� ������
   do {
      while(mousebuttons() != 1){
         x = mousex();
         y = mousey();}
         for(int i = 1; i < 3; i++){
            if (x >= but[i].x && x <= but[i].x + but[i].dx && y >= but[i].y && y <= but[i].y + but[i].dy)
            {flag = 1; st = i+1;  break; }
            }
   }while(!flag);
   
   if(st == 2)  {mix_at_end();      pereB = false;}
   else        pereB = true;
}

void victory()  // ���� ������ � ������� � ������� ����
{
   char res[100];
   setVSPage();
   clearviewport();
   while(kbhit())       getch();
   putimage(0, 0, win.bmp, COPY_PUT);   //����������� ���� ��������
   sprintf(res, "���� ����� �����������: %d ����� %d ������!", (baseTime + seconds) / 60, (baseTime + seconds) % 60);
   setcolor(BEIGE);
   outtextxy(370, 300, res);    // ����� ������� �����������
   setACPage();
   getch();
}