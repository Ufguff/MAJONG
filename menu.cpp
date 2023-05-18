#include "menu.h"
#include "new_game.h"
#include "graphics.h"

button but[4];  //���������� ������� ������ ��� ����
button logo;    // ���� ���� ��� ����
button rulAbt;      // ������ ��� ��������� ���� "�������"/"� ���������"

const int buttonW = 280, buttonH = 90;  //������� ������ ����
const int mid_width = width / 2, mid_height = height / 2;       
int currentPage = -1;    // ��� ����� ���� � ��������
bool contGame = false;

void begin()// ������������� ���� � �������������� �� ����
{
   
   int st = 1;  //������ - ����� ����� ���� ����� �����
   init_menu(); //���������� � ��������� ����
   do{
      st = menu(st);
      switch(st){       // �������������� �� ���� ������� ������ ������������
         case 1: 
            if (contGame)       continue_game();
            else new_game(); 
            break;     // ����� ���� 
         default:       //�������/� ���������
            if (st != 4)        rules_about(st);
            break;
      }
   } while(st != 4);
   close_game();        //�������� ������������ ����
}

void continue_game()
{
   button res[3];
   char s[25];
   
   setVSPage();
   clearviewport();
   for(int i = 0; i < 3; i++)   // ���� ��������� ������ � �� �����
   {
      sprintf(s, ".//MENU_STUFF/restart%d.bmp", i);
      if(i != 0)
      {
         res[i].dx = 280;        res[i].dy = 90;
         res[i].x = 100 + res[i].dx*(i - 1) + (i - 1)*40;       res[i].y = 450;
      }
      res[i].bmp = loadBMP(s);
   }
   for(int i = 0; i < 3; i++)   // ����� ������ ��������� � ������ ��� ������
   {
      if (i == 0)       putimage(0, 0, res[i].bmp, COPY_PUT);
      else putimage(res[i].x, res[i].y, res[i].bmp, COPY_PUT);
   }
   
   setACPage();
   
   int flag = 0, x, y, st = 0;       //����� ������ ���� ������
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
   
   setbkcolor(ELVOLT);  //      ��������� ����� ����
   char file[30];       //������ ��� ����������� ���� ����� ������
   for(int i=0; i <4; i++){     // ������������ ��������� ������� � ����� �������� ����
         but[i].dx = 280; but[i].dy = 90; 
         but[i].x = (width / 2) - (buttonW / 2); but[i].y = 180 + i * (but[i].dy+10);   
         sprintf(file,".//MENU_STUFF/menu%d.bmp", i+1);
         but[i].bmp = loadBMP(file);
   }
   // ���� ����� �������� ��� ����
   logo.dx = 150; logo.dy = 100;
   logo.x = 60; logo.y = 5;
   logo.bmp = loadBMP(".//MENU_STUFF/menu_majong.gif");
}



void drawmenu() // ��������� ���� � ������ ����
{
   setVSPage();
   clearviewport();
   putimage(logo.x, logo.y, logo.bmp, TRANSPARENT_PUT);
   for(int i=0; i <4; i++){     //������� �� ����� ���� � ������
        putimage(but[i].x , but[i].y, but[i].bmp, COPY_PUT); 
   }
   setACPage();
}

int menu(int st)
{
   int flag = 0, x, y;
   drawmenu();  //��������� ����
   do {
      while(mousebuttons() != 1){       //���������� ��������� ���� ����� ������������ � ����� ����������� �������
         x = mousex();
         y = mousey();}
         for(int i = 0; i < 4; i++){
            if (x >= but[i].x && x <= but[i].x + but[i].dx && y >= but[i].y && y <= but[i].y + but[i].dy)       //�������� ��� ���� ��������� � �������� ������
            {flag = 1; st = i+1;  break; }
            }
   }while(!flag);
   return st;
}

void rules_about(int st)
{
   setVSPage();
   clearviewport();
   if (st == 2) rulAbt.bmp = loadBMP(".//MENU_STUFF/rules.bmp");        //�������� ����� ���� ���� ������� �� �����
   else rulAbt.bmp = loadBMP(".//MENU_STUFF/about.bmp");
   putimage(0, 0, rulAbt.bmp, COPY_PUT);        //�����
   
   setACPage();
   while(kbhit())       getch();
   getch();     //�������� ������� ������
   //begin();     // ����� � ����
}

void close_game(){  closegraph();   }       // �������� ������������ ����

void setVSPage()
{
   if(currentPage == 3)        currentPage = 0;
   currentPage++;
   setactivepage(currentPage);
}

void setACPage(){       setvisualpage(currentPage);     }