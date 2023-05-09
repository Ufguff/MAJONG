#ifndef _MENU_
#define _MENU_
#include "graphics.h"
#define ELVOLT COLOR(131, 158, 23)      //цвет, используемый для фона

// длина и ширина графического окна
#define width 800
#define height 600

typedef struct button { // обьявление структуры кнопок
   int x, y, dx, dy;
   IMAGE * bmp;
   } Button;


// прототипы функций
void begin();   //
void init_menu();       //инициализация меню
int menu(int st);       // выбор куда пользователь зашел
void drawmenu();        // отрисовка лого и кнопок меню
void rules_about(int st);
//void about();
void close_game();
   
#endif