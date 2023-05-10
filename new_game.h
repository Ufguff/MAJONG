#ifndef _GAME_
#define _GAME_
#define AVOCADO COLOR(82, 102, 0)
#define BEIGE COLOR(247, 224, 193)

typedef struct TILE {   //��������� �����
   char name[20];
   int id, count, x, y, i, j, k;        //id �����, � ���������� � ����, ���������� �� x � y, ���������� ����� � �������
   IMAGE * bmp;
   }Tile;

void new_game();        //��������� ������� � ������ ����
void draw_pole();       //������������ ����� �� ����, � ����� ������� �������� � ������� ��� ��������
void init_game();       // ������������� ���������� � ���������
void maj_init();        //��������������� �������� ���� � ��� ����������
   
   
void definition_XY(int *i, int *y, int *k);
void core_game();       // �������� ������� ����
void click(int *i, int *j);     // ����������� ����� ����� ������ ������������
void delete_pair(TILE *tile1, TILE *tile2);     //  �������� �����
bool is_avalible(TILE* tile1);  //�������� �� �����
bool is_season(int tile1, int tile2);   //  �������� �������� �� �����
void acc_avl(); //�������� ��������� ��� �����
void mix_at_end();      // ������������� ��� ������������ ������
void border(TILE *tile);        // ������� ��� ������� �� �����(�� �������� � swapbuffers())
void stopwatch();       // ���������� �����������
void turn_SW(); //��������� ������� � ������ ������
void end();     //���� ��� ������������� ��������� �����
void victory(); // ���� ������ � ������� � ������� ����
#endif