











using namespace std;
const int le = 9, wi = 7, he = 5;      // размеры пирамиды
TILE Pole[le][wi][he];     // под пирамиду
int CON_TILES = 144;
const int tileW = 45, tileH = 55;
vector <pair<int, int>> layout;
vector<int> avl_tile;
auto rd = random_device {}; // для рандомизации раскладки
auto rng = default_random_engine {rd()};
int begOfX = floor((width - (tileW * le)) / 2);
int begOfY = floor((height - (tileH * wi)) / 2) + 50;
int pairAVL;
button= loadBMP("back.bmp");
button at_end[2];

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
                  Pole[i][j][k].x = begOfX + (i * tileW) - k*4;
                  Pole[i][j][k].y = begOfY + (tileH * j) + k*4;
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
   setcolor(WHITE);
   char output[20];
   sprintf(output, "Осталось фишек: %d", CON_TILES);
   outtextxy(400, 50, output);
   acc_avl();
   sprintf(output, "Осталось ходов: %d", pairAVL);
   outtextxy(600, 50, output); 
   
   for(int k = 0; k < he; k++)
         for(int j = 0; j < wi; j++)
            for(int i = 0; i < le; i++)
                 {      if (Pole[i][j][k].id != -1) putimage(Pole[i][j][k].x, Pole[i][j][k].y, Pole[i][j][k].bmp, TRANSPARENT_PUT);}
   swapbuffers();
   }


void init_game(){
   // создание маджонга
   back.x = 100;        back.y = 100;   back.bmp = loadBMP("back.bmp");
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
   char output[11];
   
   while(1)
   {
      if (pairAVL == 0){
         putimage(_abracadabra_cast(back);