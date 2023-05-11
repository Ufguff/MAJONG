#include<iostream>
#include<vector>
#include<random>
#include <algorithm>
#include <utility>
#include <string>
#include <cmath>
#include <ctime>
#include <thread>

#include "menu.h"
#include "new_game.h"
#include "graphics.h"

using namespace std;
const int le = 9, wi = 7, he = 5;      // ������� ������� ��������
TILE Pole[le][wi][he];     // ���������� ����������� �������
const int tileW = 45, tileH = 55;       //������� ����� � ��������
vector <pair<int, int>> layout; //��������� �����
vector<int> avl_tile;   //������ ��������� ����� ��� �� ����������� ��������
vector <TILE> for_find; // ������������� ������ ��� ������ find_tiles
pair<TILE,TILE> founds; // ��������� ���� ��� find_tiles
// ��� ������������ ���������
auto rd = random_device {}; 
auto rng = default_random_engine {rd()};
//
int begOfX = floor((width - (tileW * le)) / 2) - 50; //��������� ���������� �� X ��� ������ ���� ��������
int begOfY = floor((height - (tileH * wi)) / 2) + 30;   //��������� ���������� �� Y ��� ������ ���� ��������
int pairAVL, CON_TILES; //���������� ��������� �����, ���������� ���� �����
int hours, minutes, seconds;        //����� �����������
button lose, win, exitOn, findTiles;       //���� ��� ������ ��������� ��� ��������
TILE library[42];    //��������� ��� �����
thread SW;      //���������� ������ ��� �����������
bool threadAcc; //��� ���������/���������� �������

void new_game(){        //��������� ������� � ������ ����
   CON_TILES = 144;
   hours = 0; minutes = 0; seconds = 0;
   threadAcc = true;
   
   settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
   
   init_game();
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
               Pole[i][j][k].x = begOfX + (i * tileW) - k*4;
               Pole[i][j][k].y = begOfY + (tileH * j) + k*4;
               Pole[i][j][k].bmp = library[layout[0].first].bmp;
               layout.erase(layout.begin()); 
               } 
         }
         
         acc_avl();     //�������� ��������� ��� �����
}
   
void draw_pole(){       //������������ ����� �� ����, � ����� ������� �������� � ������� ��� ��������
   setVSPage();
   clearviewport();
   setcolor(WHITE);
   char output[20];
   sprintf(output, "�������� �����: %d", CON_TILES);    // ����� ���������� �����
   outtextxy(350, 30, output);
   sprintf(output, "�������� �����: %d", pairAVL);      // ����� ���������� �����
   outtextxy(560, 30, output); 
   printSW();   // ����� �����������
   
   for(int k = 0; k < he; k++)  // ��������� �������� �����
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
                 {      
                    if (Pole[i][j][k].id != -1) {
                     putimage(Pole[i][j][k].x, Pole[i][j][k].y, Pole[i][j][k].bmp, TRANSPARENT_PUT);}
                  }
   putimage(10, 10, exitOn.bmp);
   putimage(700, 300, findTiles.bmp);
   setACPage();
   }


void init_game(){       // ������������� ���������� � ���������
   setbkcolor(AVOCADO); 
   clearviewport();
   lose.bmp = loadBMP(".//MENU_STUFF/lose.bmp");
   win.bmp = loadBMP(".//MENU_STUFF/win.bmp");
   exitOn.bmp = loadBMP(".//MENU_STUFF/exit2.bmp");
   findTiles.bmp = loadBMP(".//MENU_STUFF/find.bmp");
   exitOn.bmp = imageresize(exitOn.bmp, 180, 60, COLORONCOLOR_RESIZE);
   for (int i = 0; i < 42; i++) { // �������� ���������� �����
         library[i].id = i;
         if (i < 34)        library[i].count = 4; 
         else library[i].count = 1; 
         sprintf(library[i].name, ".//TILES/tile%d.bmp", i+1);    
         library[i].bmp = loadBMP(library[i].name); 
	}
        
   for (int i = 0; i < 42; i++) { for (int j = 1; j <= library[i].count; j++) {    layout.push_back(make_pair(library[i].id, j));     } }       //�������� ���������


   shuffle(layout.begin(), layout.end(), rng);        //���������� ������������(������������� ���������)
   
   maj_init();
   }

void core_game()        // �������� ������� ����
{
   int i1, i2, j1, j2, k1, k2;  //��� ���������� ������� � �������
   turn_SW();   //��������� ����������� � ������ ������
      while(1)
      {
         if (CON_TILES == 0)       victory();   //������� ��� ��������� ��� ��������
         else if (pairAVL == 0)    end();
         
         definition_XY(&i1, &j1, &k1);
         
         definition_XY(&i2, &j2, &k2);
         
         if (i1 == i2 && j1 == j2 && k1 == k2)     {    draw_pole();    continue;   }      //���� ���� � �� �� ����� �� ����������
         
         //���� ����� ��������� ��� ��� ���������� ��� ��������
         if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(Pole[i1][j1][k1].id, Pole[i2][j2][k2].id)) && is_avalible(&Pole[i1][j1][k1]) && is_avalible(&Pole[i2][j2][k2])){     
            delete_pair(&Pole[i1][j1][k1], &Pole[i2][j2][k2]);  // �������� ����� �� �������
            acc_avl(); //�������� ��������� ��� �����
         }
         draw_pole();   //��������� ����
      }
   
}

void definition_XY(int *i, int *j, int *k)      // ����������� ��������� � �������
{
   click(i, j);         // ����������� ��������� �� XY � � �������
   for (int kn = he - 1; kn >= 0; kn--) {       // ����������� �� ����� ����� ��������� �����
      if(Pole[*i][*j][kn].id == -1)      continue;
      else{(*k) = kn; break;}
      }
   border(&Pole[*i][*j][*k]);
   delay(300);  //��� ������� ��������� delay
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
   if(tile1 >= 34 && tile2 >= 34)  
      return ((tile1 + 4) == tile2 || (tile2 + 4) == tile1);
   else return false;
}

bool is_avalible(TILE* tile1)   //�������� �� �����
{
   int i = tile1->i, j = tile1->j, k = tile1->k;
   if (((Pole[i][j][k+1].id == -1) && (k + 1) <= he) && ((i+1) < 9 && Pole[i + 1][j][k].id == -1) || ((i - 1) >= 0 && Pole[i - 1][j][k].id == -1) || i == 0 || i == (le - 1))     return true;
      return false;
}
   
void click(int *i, int *j)      // ����������� ����� ����� ������ ������������
{
   int x, y;    // ��������� ���������
   while(mousebuttons()==1);
   do{
   while(mousebuttons() != 1){
      x = mousex();
      y = mousey();
   }
   while(mousebuttons()==1);   //����� ����� ����� � �������
   
   if (x >= 10 && x <= 190 && y >= 10 && y <= 70){threadAcc = false;     begin();}      //�����
   if (x >= 700 && x <= 750 && y >= 300 && y <= 350){find_tiles();}  // ���������� ���

   }while(!(begOfX <= x && x <= begOfX + (tileW * le)) || !(begOfY <= y && y <= begOfY + (tileH * wi)));
   if ((x < begOfX || x > begOfX + le*tileW) && (y < begOfY || y > begOfY + wi*tileH)) click(i, j);
   *i = ceil((x - begOfX) / tileW);
   *j = ceil((y - begOfY) / tileH);
}

void acc_avl()  //�������� ��������� ��� �����
{
   char output[11];
   int i = 0;
   pairAVL = 0;
   //��������� ���� ��������� ����� � ������
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].id != -1 && is_avalible(&Pole[i][j][k]) && (Pole[i][j][k+1].id == -1))      
            {avl_tile.push_back(Pole[i][j][k].id);      for_find.push_back(Pole[i][j][k]);}
   
   sort(begin(avl_tile), end(avl_tile));        //���������� �� �����������
   
   for(int i = 0; i < for_find.size() - 1; i++) // ���������� 1 ���� ����� � ��������� � pair ��� ������� find_tiles()
      for(int j = i + 1; j < for_find.size(); j++)
         if (for_find[i].id == for_find[j].id)  {founds = make_pair(for_find[i], for_find[j]);   break;}
         
   while((i + 1) < avl_tile.size())     //������� ��������� ���
   {
      if (avl_tile[i] == avl_tile[i + 1] || is_season(avl_tile[i], avl_tile[i+1])){pairAVL++;    avl_tile.erase(avl_tile.begin() + i, avl_tile.begin() + i + 2);}
      else      i++;
      }
   avl_tile.clear();    //�������� ������� �� ���������� �����
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
   turn_SW();   //��������� ����������� � ������ ������
}

void border(TILE *tile) // ������� ��� ������� �� �����(�� �������� � swapbuffers())
{
   //setcolor(BR);
   rectangle(tile->x, tile->y, tile->x + tileW, tile->y + tileH);
}

void find_tiles()       // ���������� ����� ���� ������������ �� �� �����
{
   border(&founds.first);        border(&founds.second);
   
   //rectangle(founds.first.x, founds.first.y, founds.first.x + tileW, founds.first.y + tileH);
   //rectangle(founds.second.x, founds.second.y, founds.second.x + tileW, founds.second.y + tileH);
}

void stopwatch()        // ���������� �����������
{
   time_t start;
   struct tm *now;
   int s1, s0 = 0;
   start = time(NULL);
   now = localtime(&start);
   s0 = now->tm_sec;
   while(threadAcc)
   {
      setcolor(WHITE);
      start = time(NULL);
      now = localtime(&start);
      s1 = now->tm_sec;
      if (s1 != s0){
         s0 = s1;
         seconds++;
         printSW();
         //printf("Timer - %02d:%02d:%02d\n", hours, minutes, seconds);
         if (minutes == 59 && seconds == 59){ hours++;  minutes = 0;  seconds = -1;}
         if (seconds == 59){ minutes++;   seconds = -1; }
         
      }
   }
}

void printSW()  // ����� �����������
{
   char s[20];
   sprintf(s, "�����: %02d:%02d", minutes, seconds);
   outtextxy(210 , 30, s);
}

void turn_SW(){thread SW(stopwatch);    SW.detach();}   //��������� ����������� � ������ ������

void end()      //���� ��� ������������� ��������� �����
{
   button but[3];
   char s[25];
   threadAcc = false;   // ����������� ������ �������
   
   setVSPage();
   clearviewport();
   for(int i = 0; i < 3; i++)   // ���� ��������� ������ � �� �����
   {
      sprintf(s, "MENU_STUFF/exit%d.bmp", i);
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
   
   if(st == 2)  {threadAcc = true;   mix_at_end();}
   else begin();
}

void victory()  // ���� ������ � ������� � ������� ����
{
   setcolor(BEIGE);     //��������� ����� ��� ������
   char res[30];
   setVSPage();
   clearviewport();
   while(kbhit())       getch();
   threadAcc = false;   // ����������� ������ �������
   putimage(0, 0, win.bmp, COPY_PUT);   //����������� ���� ��������
   sprintf(res, "���� ����� �����������: %d ����� %d ������!", minutes, seconds);
   outtextxy(400, 300, res);    // ����� ������� �����������
   setACPage();
   getch();
   clearviewport();
   begin(); 
}