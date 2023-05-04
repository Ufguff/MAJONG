#ifndef _GAME_
#define _GAME_
#define AVOCADO COLOR(82, 102, 0)

typedef struct TILE {
   char name[20];
   int id, count, x, y, i, j, k;
   IMAGE * bmp;
   }Tile;

void new_game();
void init_menu_pole();
void draw_pole();
void init_game();
void maj_init();
   
void core_game();
void click(int *i, int *j);
void delete_pair(TILE *tile1, TILE *tile2);
bool is_avalible(TILE* tile1);
       //is_avalible(TILE*)
bool is_season(int tile1, int tile2);
void acc_avl();
void mix_at_end();
void end();
void restart();
#endif