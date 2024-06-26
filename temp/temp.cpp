













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
int minutes, seconds;        //����� �����������
button lose, win, gMenu, findTiles;       //���� ��� ������ ��������� ��� ��������
TILE library[42];    //��������� ��� �����
thread SW;      //���������� ������ ��� �����������
bool threadAcc, pereB, vicB; //��� ���������/���������� �������
extern bool contGame;



void new_game(){        //��������� ������� � ������ ����
   settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
   
   if (!contGame){
   CON_TILES = 144;
   minutes = 0; seconds = 0;
   
   init_game();
   }
   
   threadAcc = true;
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
   putimage(10, 10, gMenu.bmp);
   putimage(700, 300, findTiles.bmp);
   setACPage();
   }


void init_game(){       // ������������� ���������� � ���������
   setbkcolor(AVOCADO); 
   clearviewport();
   lose.bmp = loadBMP(".//MENU_STUFF/lose.bmp");
   win.bmp = loadBMP(".//MENU_STUFF/win.bmp");
   gMenu.bmp = loadBMP(".//MENU_STUFF/gMenu.bmp");
   findTiles.bmp = loadBMP(".//MENU_STUFF/find.bmp");
   //exitOn.bmp = imageresize(exitOn.bmp, 180, 60, COLORONCOLOR_RESIZE);
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
   int count = 0;
   turn_SW();   //��������� ����������� � ������ ������
      while(1)
      {
         if(definition_XY(&i1, &j1, &k1))       break;
         
         if(definition_XY(&i2, &j2, &k2))       break;
         
         if (i1 == i2 && j1 == j2 && k1 == k2)     {    draw_pole();    continue;   }      //���� ���� � �� �� ����� �� ����������
         
         //���� ����� ��������� ��� ��� ���������� ��� ��������
         if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(Pole[i1][j1][k1].id, Pole[i2][j2][k2].id)) && is_avalible(&Pole[i1][j1][k1]) && is_avalible(&Pole[i2][j2][k2])){     
            delete_pair(&Pole[i1][j1][k1], &Pole[i2][j2][k2]);  // �������� ����� �� �������
            if(CON_TILES != 0) acc_avl(); //�������� ��������� ��� �����
         }
        //if (count == 3) 
           CON_TILES = 0;
         //if (CON_TILES == 0)       {victory(); if(vicB) {vicB = false; break; }}   //������� ��� ��������� ��� ��������
         // ����� -1 ������� // ����� ��������� 
         if (pairAVL == 0)    {end();   if(pereB)       {pereB = false; break; }}
         
         if(CON_TILES != 0)     draw_pole();   //��������� ����
         else {victory();       break;}
         count++;
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
   if (*k != -1)border(&Pole[*i][*j][*k]);
   delay(300);  //��� ������� ��������� delay
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
   if(tile1 >= 34 && tile2 >= 34)  
      return ((tile1 + 4) == tile2 || (tile2 + 4) == tile1);    //���������� ??
   else return false;
}

bool is_avalible(TILE* tile1)   //�������� �� �����
{
   int i = tile1->i, j = tile1->j, k = tile1->k;
   if (((Pole[i][j][k+1].id == -1) && (k + 1) <= he) && ((i+1) < 9 && Pole[i + 1][j][k].id == -1) || ((i - 1) >= 0 && Pole[i - 1][j][k].id == -1) || i == 0 || i == (le - 1))     return true;
      return false;
}
   
bool click(int *i, int *j)      // ����������� ����� ����� ������ ������������
{
   int x, y;    // ��������� ���������
   while(mousebuttons()==1);
   do{
   while(mousebuttons() != 1){
      x = mousex();
      y = mousey();
   }
   while(mousebuttons()==1);   //����� ����� ����� � �������
   
   if (x >= 10 && x <= 100 && y >= 10 && y <= 55){threadAcc = false;    contGame = true;     return true;}      //����      1
   if (x >= 700 && x <= 750 && y >= 300 && y <= 350){find_tiles();}  // ���������� ���

   }while(!(begOfX <= x && x <= begOfX + (tileW * le)) || !(begOfY <= y && y <= begOfY + (tileH * wi)));
   if ((x < begOfX || x > begOfX + le*tileW) && (y < begOfY || y > begOfY + wi*tileH)) click(i, j);
   *i = ceil((x - begOfX) / tileW);
   *j = ceil((y - begOfY) / tileH);
   return false;
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
   rectangle(tile->x, tile->y, tile->x + tileW, tile->y + tileH);
}

void find_tiles()       // ���������� ����� ���� ������������ �� �� �����
{
   border(&founds.first);        border(&founds.second);
   TILE temp;   temp.id = -1;
   temp.x = 800;        temp.y = 600;
   founds.first = temp;
   founds.second = temp;
}

void stopwatch()        // ���������� �����������
{
   clock_t t0 = clock();
   //seconds = 0, minutes = 0;
   int temp = 0;
   while(threadAcc){
      clock_t t1 = clock();
      temp = (int)((double)(t1 - t0) / CLOCKS_PER_SEC);
      seconds = temp % 60;
      minutes = temp / 60;
      printSW();
   }
}

void printSW()  // ����� �����������
{
   char s[20];
   sprintf(s, "�����: %02d:%02d", minutes, seconds);
   outtextxy(210 , 30, s);
   cout << s << endl;
}

void turn_SW(){thread SW(stopwatch);    _abracadabra_cast(SW);