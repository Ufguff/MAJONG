#ifndef _GAME_
#define _GAME_
#define AVOCADO COLOR(82, 102, 0)
#define BEIGE COLOR(247, 224, 193)

typedef struct TILE {   //структура фишки
   char name[20];
   int id, count, x, y, i, j, k;        //id фишки, её количество в игре, координата по x и y, координаты фишки в массиве
   IMAGE * bmp;
   }Tile;

void new_game();        //отрисовка массива и движок игры
void draw_pole();       //отрисовывает фишки на поле, а также сколько осталось и сколько пар доступно
void init_game();       // инициализация библиотеки и раскладки
void maj_init();        //предварительное создание поля и его заполнение
   
   
void definition_XY(int *i, int *y, int *k);
void core_game();       // основной процесс игры
void click(int *i, int *j);     // определение какую фишку выбрал пользователь
void delete_pair(TILE *tile1, TILE *tile2);     //  удаление фишек
bool is_avalible(TILE* tile1);  //доступна ли фишка
bool is_season(int tile1, int tile2);   //  проверка сезонная ли фишка
void acc_avl(); //пересчет доступных пар фишек
void mix_at_end();      // перемешивание при отсутсвующих фишках
void border(TILE *tile);        // границы при нажатии на фишку(не работает с swapbuffers())
void stopwatch();       // реализация секундомера
void turn_SW(); //включение таймера в другом потоке
void end();     //окно при закончившихся доступных фишек
void victory(); // окно победы с выходом в главное меню
#endif