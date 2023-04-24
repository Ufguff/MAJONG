#ifndef _MENU_
#define _MENU_
#include "graphics.h"

#define ELVOLT COLOR(131, 158, 23)
#define FONTS COLOR(239, 222, 194)
#define width 800
#define height 600

typedef struct button {
   int x, y, dx, dy;
   IMAGE * bmp;
   } Button;



void init_menu();
int menu(int st);
void drawmenu();

#endif