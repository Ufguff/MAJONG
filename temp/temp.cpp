











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
button lose, win;
TILE library[42];    //библиотка для фишек

void new_game(){
   CON_TILES = 144;
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
               Pole[i][j][k].access = false;
               switch(k){
               case 4:
                  if ((i == 4 && j == 3) || (i == 4 && j == 2)) Pole[i][j][k].access = true;
                  break;
               case 3:
                  if ((i == 3 || i == 5))    Pole[i][j][k].access = true;
                  break;
               case 2:
                  if ((i == 2 || i == 6))    Pole[i][j][k].access = true;
                  break;
               case 1:
                  if (i == 1 || i == 7)      Pole[i][j][k].access = true;
                  else if((i == 2 || i == 6) && (j == 0 || j == 6))  Pole[i][j][k].access = true;
                  break;
               case 0:
                  if (i == 0 || i == 8)    Pole[i][j][k].access = true;
                  break;
               }
               layout.erase(layout.begin()); 
               } 
         }
         
         acc_avl();
}
   
void draw_pole(){       //отрисовывает фишки на поле, а также сколько осталось и сколько пар доступно
   clearviewport();
   char output[20];
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
   int count = 0;
   while(1)
   {
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
      
      if ((Pole[i1][j1][k1].id == Pole[i2][j2][k2].id || is_season(_abracadabra_cast(Pole[i1][j1][k1]);