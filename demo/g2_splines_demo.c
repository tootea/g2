/*
 * g2_splines_demo.c
 * 06/16/99
 */

#include <stdio.h>

#include <g2.h>
#ifdef DO_PS
#include <g2_PS.h>
#endif
#ifdef DO_X11
#include <g2_X11.h>
#endif
#ifdef DO_GIF
#include <g2_GIF.h>
#endif
#ifdef DO_WIN32
#include <g2_win32.h>
#endif
#ifdef DO_WMF32
#include <g2_win32.h>
#endif



#define n	14
#define o	60
#define tn	0.6

#define X11	0
#define PS	1
#define GIF     2

int otp=X11;

int id=-1 ;	           /* default output device */


void curves()
{
   int i;
   double points[(2*n)];
   double dy[n]   =   {  10., 280., 140., 200.,  60., 120., 380.,
			500., 480., 400., 220., 180., 260., 340.};

   for (i = 0; i < n; i++) {
      points[(i+i)]	= (i*o)+20.;       /* from 20 to 800 (20+(13*60)) */
      points[(i+i+1)]	= dy[i];
   }
   g2_pen(id, 1);
   g2_poly_line(id, n, points);
   g2_pen(id, 3);
   g2_spline(id, n, points, o);
   g2_pen(id, 7);
   g2_b_spline(id, n, points, o);
   g2_pen(id, 10);
   g2_raspln(id, n, points, tn);
   g2_pen(id, 19);
   g2_para_3(id, n, points);
   g2_pen(id, 22);
   g2_para_5(id, n, points);
}

void axes()
{
   g2_line(id, 5, 300, 810, 300);
   g2_line(id, 400, 5, 400, 560);
}

void draw()
{
   g2_rectangle(id, 5, 5, 810, 560);	/* window: 815 x 565 */
   axes();
   curves();
}

int main(int argc, char *argv[])
{
    int dev[5]={-1, -1, -1, -1, -1};

    id=g2_open_vd();				  /* open virtual device */

    printf("\nAdding..");
    
#ifdef DO_PS
    printf("..PS");
    dev[0]=g2_open_PS("g2_splines_demo.ps", g2_A4, g2_PS_land);
    g2_attach(id, dev[0]);
#endif
#ifdef DO_X11
    printf("..X11");
    dev[1]=g2_open_X11(850, 600);
    g2_attach(id, dev[1]);
#endif
#ifdef DO_GIF
    printf("..GIF");
    dev[2]=g2_open_GIF("g2_splines_demo.gif", 850, 600);
    g2_attach(id, dev[2]);
#endif
#ifdef DO_WIN32
    printf("..WIN32");
    dev[3]=g2_open_win32(850, 600,"g2_splines_demo",0);
	g2_set_auto_flush(dev[3],0);
    g2_attach(id, dev[3]);
#endif
#ifdef DO_WMF32
    printf("..WMF32");
    dev[4]=g2_open_win32(850, 600,"g2_splines_demo.emf",1);
	g2_set_auto_flush(dev[3],0);
    g2_attach(id, dev[4]);
#endif
    
    g2_set_auto_flush(id,0);   
    g2_set_coordinate_system(id, 12, 15, 1., 1.);
    
    draw();
    g2_flush(id);
    if (otp==X11) {
	printf("\nDone.\n[Enter]\n");
	getchar();
    }
    g2_close(id);
    return 0;
}