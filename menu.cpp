#include "menu.h"
#include "new_game.h"
#include "graphics.h"

button but[4];  //обьявление массива кнопок для меню
button logo;    // лого игры для меню
button rulAbt;      // кнопка для выведения окна "Правила"/"О программе"

const int buttonW = 280, buttonH = 90;  //размеры кнопок меню
const int mid_width = width / 2, mid_height = height / 2;       
int currentPage = -1;    // для новых окон и анимации
bool contGame = false;

void begin()// приготовление меню и переназначение на окна
{
   
   int st = 1;  //статус - какой пункт меню будет нажат
   init_menu(); //подготовка и отрисовка меню
   do{
      st = menu(st);
      switch(st){       // переназначение на окно которое выбрал пользователь
         case 1: 
            if (contGame)       continue_game();
            else new_game(); 
            break;     // Новая игра 
         default:       //Правила/О программе
            if (st != 4)        rules_about(st);
            break;
      }
   } while(st != 4);
   close_game();        //закрытие графического окна
}

void continue_game()
{
   button res[3];
   char s[25];
   
   setVSPage();
   clearviewport();
   for(int i = 0; i < 3; i++)   // указ координат кнопок и их адрес
   {
      sprintf(s, ".//MENU_STUFF/restart%d.bmp", i);
      if(i != 0)
      {
         res[i].dx = 280;        res[i].dy = 90;
         res[i].x = 100 + res[i].dx*(i - 1) + (i - 1)*40;       res[i].y = 450;
      }
      res[i].bmp = loadBMP(s);
   }
   for(int i = 0; i < 3; i++)   // вывод экрана проигрыша и кнопок для выбора
   {
      if (i == 0)       putimage(0, 0, res[i].bmp, COPY_PUT);
      else putimage(res[i].x, res[i].y, res[i].bmp, COPY_PUT);
   }
   
   setACPage();
   
   int flag = 0, x, y, st = 0;       //какая кнопка была нажата
   do {
      while(mousebuttons() != 1){
         x = mousex();
         y = mousey();}
         for(int i = 1; i < 3; i++){
            if (x >= res[i].x && x <= res[i].x + res[i].dx && y >= res[i].y && y <= res[i].y + res[i].dy)
            {flag = 1; st = i+1;  break; }
            }
   }while(!flag);
   
   if(st == 2)  {contGame = true;}
   else contGame = false;
   new_game();
}

void init_menu(){
   
   setbkcolor(ELVOLT);  //      установка цвета фона
   char file[30];       //массив для обозначения пути файла кнопки
   for(int i=0; i <4; i++){     // присваивание координат кнопкам а также указание пути
         but[i].dx = 280; but[i].dy = 90; 
         but[i].x = (width / 2) - (buttonW / 2); but[i].y = 180 + i * (but[i].dy+10);   
         sprintf(file,".//MENU_STUFF/menu%d.bmp", i+1);
         but[i].bmp = loadBMP(file);
   }
   // тоже самое отдельно для лого
   logo.dx = 150; logo.dy = 100;
   logo.x = 60; logo.y = 5;
   logo.bmp = loadBMP(".//MENU_STUFF/menu_majong.gif");
}



void drawmenu() // отрисовка лого и кнопок меню
{
   setVSPage();
   clearviewport();
   putimage(logo.x, logo.y, logo.bmp, TRANSPARENT_PUT);
   for(int i=0; i <4; i++){     //вставка на экран лого и кнопок
        putimage(but[i].x , but[i].y, but[i].bmp, COPY_PUT); 
   }
   setACPage();
}

int menu(int st)
{
   int flag = 0, x, y;
   drawmenu();  //отрисовка меню
   do {
      while(mousebuttons() != 1){       //нахождение координат куда нажал пользователь а также определение статуса
         x = mousex();
         y = mousey();}
         for(int i = 0; i < 4; i++){
            if (x >= but[i].x && x <= but[i].x + but[i].dx && y >= but[i].y && y <= but[i].y + but[i].dy)       //проверка что клик находится в границах кнопки
            {flag = 1; st = i+1;  break; }
            }
   }while(!flag);
   return st;
}

void rules_about(int st)
{
   setVSPage();
   clearviewport();
   if (st == 2) rulAbt.bmp = loadBMP(".//MENU_STUFF/rules.bmp");        //проверка какой файл надо вывести на экран
   else rulAbt.bmp = loadBMP(".//MENU_STUFF/about.bmp");
   putimage(0, 0, rulAbt.bmp, COPY_PUT);        //вывод
   
   setACPage();
   while(kbhit())       getch();
   getch();     //ожидание нажатия кнопки
   //begin();     // выход в меню
}

void close_game(){  closegraph();   }       // закрытие графического окна

void setVSPage()
{
   if(currentPage == 3)        currentPage = 0;
   currentPage++;
   setactivepage(currentPage);
}

void setACPage(){       setvisualpage(currentPage);     }