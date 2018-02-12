// Mandelbrotova mnozina v rastru 4096x4096 s vyuzitim vypocetni metody
// "distance estimation"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "allegro.h"

#define MAXITER    1000
#define PER_CHECK  0.1
#define PER_PERIOD 16

BITMAP *bmp;
PALLETE pal;

double ldabs (double x)
{
    return (x<0) ? -x : x;
}

int mtest(double ccx,double ccy)
{
    double  zx,zy,zx2,zy2,zzx,zzy,zzx2,zzy2;
    int     i;
    int     result1,result2;
    int     period=0;
    double  dst;

    result1=0;
    result2=0;
    i=0;
    zx=0; zy=0;
    zzx=0;zzy=0;
    do {
        if (period==PER_PERIOD) {
          zzx2=zzx*zzx;
          zzy2=zzy*zzy;
          zzy=2.0*zzx*zzy+ccy;
          zzx=zzx2-zzy2+ccx;
          period=0;
        }
        zx2=zx*zx;
        zy2=zy*zy;
        zy=2.0*zx*zy+ccy;
        zx=zx2-zy2+ccx;
        i++;
        period++;
        dst=ldabs(zx-zzx)+ldabs(zy-zzy);
        if (dst<PER_CHECK) {
          i=MAXITER;
          result2=1;
        }
    } while (i<MAXITER && zx2+zy2<4.0);

    if (i==MAXITER) {
      if (result2) result1=10;
      else         result1=15;
    }
    else {
      if (result2) result1=9;
      else         result1=0;
    }

    return (result1);
}

void mandel(void)
{
    double  zx,zy,zx2,zy2,cx,cy;
    int     x,y,i;
    int     color;

    cy=-2.0;
    cx=-2.0;
    for (y=0;y<4800;y++) {
        cx=-2.0;
        for (x=0;x<4800;x++) {
            i=0;
            zx=0;zy=0;
            color=mtest(cx,cy);
            if (color==15 || color==10) {
                putpixel(screen,x/10,y/10,1);
                putpixel(bmp,x,y,1);
            }
            else {
                putpixel(screen,x/10,y/10,2);
                putpixel(bmp,x,y,0);
            }
            cx=cx+4.0/4800.0;
        }
        cy=cy+4.0/4800.0;
    }
    drawing_mode(DRAW_MODE_XOR,NULL,0,0);
    for (y=0;y<=4800;y+=600) {
        line(bmp,0,y,4799,y,1);
        line(bmp,y,0,y,4799,1);
    }
}

int main(int argc, char *argv[])
{
   int x,y;

   allegro_init();
   install_keyboard();
   bmp=create_bitmap(4800,4800);
/*   if (bmp==NULL) {
     printf("error creating bitmap\n");
     return(-1);
   }
   printf("Clearing bitmap:");*/
   for (y=0;y<4800;y++) {
     printf("%d\n",y);
     for (x=0;x<4800;x++)
       putpixel(bmp,x,y,0);
   }

   set_gfx_mode(GFX_VESA1,640,480,0,0);
   mandel();
//   set_gfx_mode(GFX_TEXT,80,25,0,0);
   save_pcx("pokus.pcx",bmp,default_palette);
   destroy_bitmap(bmp);
   readkey();
   remove_keyboard();
   return 0;
}

