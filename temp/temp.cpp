







//#include <omp.h>






using namespace std;
const int le = 9, wi = 7, he = 5;      // размеры пирамиды
TILE Pole[le][wi][he];     // под пирамиду
const int tileW = 45, tileH = 55;
vector <pair<int, int>> layout;
vector<int> avl_tile;
auto rd = random_device {}; // для рандомизации раскладки
auto rng = default_random_engine {rd()};
int begOfX = floor((width - (tileW * le)) / 2);
int begOfY = floor((height - (tileH * wi)) / 2) + 50;
int pairAVL, CON_TILES;
int hours = 0, minutes = 0, seconds = 0;        //время прохождения
button lose, win;
TILE library[42];    //библиотка для фишек
thread SW;


void new_game(){
   CON_TILES = 144;
   hours = 0; minutes = 0; seconds = 0;
   init_menu_pole();
   init_game();
   draw_pole(); 
   core_game();
}
   
void maj_init() 
{
   //============обьявление маджонга
   for(int k = 0; k < he; k++)
   for(int j = 0; j < wi; j++)
      for(int i = 0; i < le; i++)
      {
         Pole[i][j][k].id = -1;
         switch(k){
         case 4:
            if((i == 4 && j == 3) || (i == 4 && j == 2))     Pole[i][j][k].id = 0;
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
               Pole[i][j][k].x = begOfX + (i * tileW) - k*4;
               Pole[i][j][k].y = begOfY + (tileH * j) + k*4;
               Pole[i][j][k].bmp = library[layout[0].first].bmp;
               layout.erase(layout.begin()); 
               } 
         }
         
         acc_avl();
}
   
void draw_pole(){       //отрисовывает фишки на поле, а также сколько осталось и сколько пар доступно
   clearviewport();
   char output[20];
   setcolor(BEIGE);
   sprintf(output, "Осталось фишек: %d", CON_TILES);
   outtextxy(400, 50, output);
   sprintf(output, "Осталось ходов: %d", pairAVL);
   outtextxy(600, 50, output); 
   for(int k = 0; k < he; k++)
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
                 {      
                    if (Pole[i][j][k].id != -1) {
                     putimage(Pole[i][j][k].x, Pole[i][j][k].y, Pole[i][j][k].bmp, TRANSPARENT_PUT);}
                  }
   swapbuffers();
   }


void init_game(){       // создание маджонга
   lose.bmp = loadBMP(".//MENU_STUFF/lose.bmp");
   win.bmp = loadBMP(".//MENU_STUFF/win.bmp");
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
   }

void core_game()        // основной процесс игры
{
   int i1, i2, j1, j2, k1, k2;
   thread SW(stopwatch);
      while(1)
      {
         if (CON_TILES == 0)       victory();
         else if (pairAVL == 0)    end();
         
         click(&i1, &j1);
         for (int k = he - 1; k >= 0; k--) {
            if(Pole[i1][j1][k].id == -1)      continue;
            else{k1 = k; break;}
            }
         //border(&Pole[i1][j1][k1]);
            
         click(&i2, &j2);
         for (int k = he - 1; k >= 0; k--)  {
            if(Pole[i2][j2][k].id == -1)      continue;
            else{k2 = k; break;}
            }
         //border(&Pole[i2][j2][k2]);
         
         if (i1 == i2 && j1 == j2 && k1 == k2)     continue;      //если одна и та же фишка
         
         if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(Pole[i1][j1][k1].id, Pole[i2][j2][k2].id)) && is_avalible(&Pole[i1][j1][k1]) && is_avalible(&Pole[i2][j2][k2])){     //удаление
            delete_pair(&Pole[i1][j1][k1], &Pole[i2][j2][k2]);
            acc_avl();
         }
         
         CON_TILES = 0;
         draw_pole();
      }
   
}

void delete_pair(TILE *tile1, TILE *tile2)  //  удаление
{
      TILE temp;   temp.id = -1;
      *(tile1) = temp;
      *(tile2) = temp;
      CON_TILES -= 2;
}

bool is_season(int tile1, int tile2)  //      проверка сезонная ли фишка
{
   if(tile1 >= 34 && tile2 >= 34)  
      return ((tile1 + 4) == tile2 || (tile2 + 4) == tile1);
   else return false;
}

bool is_avalible(TILE* tile1)   //обновление доступности фишек
{
   int i = tile1->i, j = tile1->j, k = tile1->k;
   // фишка под не получает доступ
   if (((Pole[i][j][k+1].id == -1) && (k + 1) <= he) && ((i+1) < 9 && Pole[i + 1][j][k].id == -1) || ((i - 1) >= 0 && Pole[i - 1][j][k].id == -1) || i == 0 || i == (le - 1))     return true;
      return false;
}
   
void click(int *i, int *j)      //клик
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
   if ((x < begOfX || x > begOfX + le*tileW) && (y < begOfY || y > begOfY + wi*tileH)) click(i, j);
   *i = ceil((x - begOfX) / tileW);
   *j = ceil((y - begOfY) / tileH);
   
}

void acc_avl()  //пересчет доступных пар фишек
{
   char output[11];
   int i = 0;
   pairAVL = 0;
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].id != -1 && is_avalible(&Pole[i][j][k]) && (Pole[i][j][k+1].id == -1))      avl_tile.push_back(Pole[i][j][k].id);
   sort(begin(avl_tile), end(avl_tile));
   
   while((i + 1) < avl_tile.size())
   {
      if (avl_tile[i] == avl_tile[i + 1] || is_season(avl_tile[i], avl_tile[i+1])){pairAVL++;    avl_tile.erase(avl_tile.begin() + i, avl_tile.begin() + i + 2);}
      else      i++;
      }
   avl_tile.clear();
}

void mix_at_end()       // перемешивание при отсутсвующих фишках
{
   TILE temp;
   temp.id = 0;
   vector <TILE> curTiles;
   for(int k = 0; k < he; k++)
      for(int j = 0; j < wi; j++)
         for(int i = 0; i < le; i++)
            if(Pole[i][j][k].id != -1)     {curTiles.push_back(Pole[i][j][k]);     Pole[i][j][k].id = 0;}
             
    
   shuffle(curTiles.begin(), curTiles.end(), rng);

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

void border(TILE *tile) // доделать
{
   setcolor(WHITE);
   rectangle(tile->x, tile->y, tile->x + tileW, tile->y + tileH);
   swapbuffers();
}

void stopwatch()
{
   time_t start;
   struct tm *now;
   int s1, s0 = 0;
   start = time(NULL);
   now = localtime(&start);
   s0 = now->tm_sec;
   while(1)
   {
      start = time(NULL);
      now = localtime(&start);
      s1 = now->tm_sec;
      if (s1 != s0){
         s0 = s1;
         seconds++;
         printf("Timer - %02d:%02d:%02d\n", hours, minutes, seconds);
         if (minutes == 59 && seconds == 59){ hours++;  minutes = 0;  seconds = -1;}
         if (seconds == 59){ minutes++;   seconds = -1; }
         
      }
   }
}

void end()
{
   button but[3];
   char s[25];
   clearviewport();
   
   _abracadabra_cast(SW);