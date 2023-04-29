

typedef struct ma{
   int x, y;
   IMAGE * bmp;
}ma;
const int w = 800, h = 600;
int main()
{
   initwindow(w, h, "MAf", 200, 200);
   setbkcolor(RED);
   getch();
   //clearviewport();
   ma logo;
   logo.bmp = loadBMP("tile2.gif");
   logo.x = 400;
   logo.y = 300;
   while(1) {
   putimage(logo.x, logo.y, logo.bmp, COPY_PUT);
      getch();
   freeimage(_abracadabra_cast(logo);