#ifndef _GAME_
#define _GAME_
#define AVOCADO COLOR(82, 102, 0)

typedef struct TILE {
   char name[20];
   int id, count, i, j, k;
   int x, y;
   IMAGE * bmp;
   }Tile;

void new_game();
void init_menu_pole();
void draw_pole();
void init_game();
void maj_init();
void debug();
   
void core_game();
void click();
void delete_pair(int id1,int i1, int j1, int k1, int id2, int i2, int j2, int k2);
#endif