/*****************************************************************************
**  Copyright (C) 1998  Ljubomir Milanovic & Horst Wagner
**  This file is part of the g2 library
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License (version 2) as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/
#ifndef _G2_H
#define _G2_H

#if defined(__cplusplus)
extern "C"
{
#endif


/* Common Library header for DLL and application */
#ifdef WIN32
#ifdef G2DLL
#ifdef MAKEDLL
/* Create DLL */
#pragma message( "Building DLL library")
#define G2L __declspec( dllexport)
#else
/* Use DLL */
#define G2L __declspec( dllimport)
#endif
#else 
/* Use static win32 */
#define G2L
#endif
#else
/* Use non-win32 */
#define G2L
#endif


#define G2_VERSION "0.41a"

#define G2LD g2_ld()

enum QPshape {
    QPrect,
    QPcirc
};

/* compatibility with old versions */
#define g2_draw_string(dev, x, y, text) g2_string((dev), (x), (y), (text))



G2L int  g2_open_vd(void);
G2L void g2_attach(int vd_dev, int dev);
G2L void g2_detach(int vd_dev, int dev);

G2L void g2_close(int dev);
G2L void g2_set_auto_flush(int dev, int on_off);
G2L void g2_flush(int dev);
G2L void g2_save(int dev);
G2L void g2_set_coordinate_system(int dev, double x_origin, double y_origin,
			      double x_mul,    double y_mul);

G2L int  g2_ld();
G2L void g2_set_ld(int dev);

G2L int  g2_ink(int pd_dev, double red, double green, double blue);
G2L void g2_pen(int dev, int color);
G2L void g2_set_dash(int dev, int N, double *dashes);
G2L void g2_set_font_size(int dev, double size);
G2L void g2_set_line_width(int dev, double w);
G2L void g2_clear_palette(int dev);
G2L void g2_reset_palette(int dev);
G2L void g2_allocate_basic_colors(int dev);

G2L void g2_clear(int dev);
G2L void g2_set_background(int dev, int color);

G2L void g2_move(int dev, double x, double y);
G2L void g2_move_r(int dev, double dx, double dy);

G2L void g2_plot(int dev, double x, double y);
G2L void g2_plot_r(int dev, double dx, double dy);
G2L void g2_line(int dev, double x1, double y1, double x2, double y2);
G2L void g2_line_r(int dev, double dx, double dy);
G2L void g2_line_to(int dev, double x, double y);
G2L void g2_poly_line(int dev, int N_pt, double *points);
G2L void g2_triangle(int dev, double x1, double y1,
		 double x2, double y2,
		 double x3, double y3);
G2L void g2_filled_triangle(int dev, double x1, double y1,
			double x2, double y2,
			double x3, double y3);
G2L void g2_rectangle(int dev, double x1, double y1, double x2, double y2);
G2L void g2_filled_rectangle(int dev,
			     double x1, double y1, double x2, double y2);
G2L void g2_polygon(int dev, int N_pt, double *points);
G2L void g2_filled_polygon(int dev, int N_pt, double *points);
G2L void g2_circle(int dev, double x, double y, double r);
G2L void g2_filled_circle(int dev, double x, double y, double r);
G2L void g2_ellipse(int dev, double x, double y, double r1, double r2);
G2L void g2_filled_ellipse(int dev, double x, double y, double r1, double r2);
G2L void g2_arc(int dev,
	    double x, double y,
	    double r1, double r2,
	    double a1, double a2);
G2L void g2_filled_arc(int dev, double x, double y,
		   double r1, double r2,
		   double a1, double a2);
G2L void g2_string(int dev, double x, double y, char *text);
G2L void g2_image(int dev,
		  double x, double y, int x_size, int y_size, int *pens);

G2L void g2_set_QP(int dev, double d, enum QPshape shape);
G2L void g2_plot_QP(int dev, double x, double y);

G2L void g2_query_pointer(int dev, double *x, double *y, unsigned int *button);

    
 /* Tijs Michels */
 /* 06/16/99	 */

G2L void g2_spline(int id, int n, double *points, int o);
G2L void g2_b_spline(int id, int n, double *points, int o);
G2L void g2_raspln(int id, int n, double *points, double tn);
G2L void g2_para_3(int id, int n, double *points);
G2L void g2_para_5(int id, int n, double *points);
G2L void g2_filled_spline(int id, int n, double *points, int o);
G2L void g2_filled_b_spline(int id, int n, double *points, int o);
G2L void g2_filled_raspln(int id, int n, double *points, double tn);
G2L void g2_filled_para_3(int id, int n, double *points);
G2L void g2_filled_para_5(int id, int n, double *points);


/** Actualy private function, but... **/
G2L int g2_device_exist(int dix);

    
#if defined(__cplusplus)
} /* end extern "C" */
#endif

#endif /* _G2_H */
