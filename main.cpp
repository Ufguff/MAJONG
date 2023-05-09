#include "menu.h"
#include "new_game.h"

int main()
{
   initwindow(width, height, "Majong", 200, 200, true); //обьявление графического окна
   begin();     // инициализация и работа с меню (определена в menu.cpp)
   return 0;   
}