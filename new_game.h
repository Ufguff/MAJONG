#ifndef _GAME_
#define _GAME_
#define AVOCADO COLOR(82, 102, 0)

typedef struct TILE {
   char name[20];
   int id, count, x, y, i, j, k;
   bool access;
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
void gain_access(TILE *tile1);
bool is_season(TILE tile1, TILE tile2);
void acc_avl();
void mix_at_end();
#endif