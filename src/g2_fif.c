/*****************************************************************************
**  This is part of the g2 library
**  Copyright (C) 1998  Ljubomir Milanovic & Horst Wagner
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
#include <stdio.h>
#include <string.h>
#include "g2.h"
#include "g2_util.h"

/*
 *
 * g2 Fortran Interface
 *
 */
#ifdef LINUX
#define FIF(funame) funame ## __
#else
#define FIF(funame) funame ## _
#endif

#define F_REAL         float    /* everything is float (real) !!!!!!!!!!!!!! */
#define F_CHAR         char     /* only char is char */
#define F_CHAR_LENGTH  int      /* and char length is integer */


/**********************************************************/

#ifdef DO_PS

#include "PS/g2_PS.h"

F_REAL FIF(g2_open_ps)(F_CHAR *text, F_REAL *paper, F_REAL *orientation,
		       F_CHAR_LENGTH length)
{
    char *str;
    int rv;

    str=g2_malloc((length+1)*sizeof(char));
    strncpy(str, text, length);
    str[length]='\0';
    rv=g2_open_PS(str, dtoi(*paper), dtoi(*orientation));
    g2_free(str);
    
    return (F_REAL)rv;
}

#endif /* DO_PS */

/**********************************************************/

#ifdef DO_X11

#include "X11/g2_X11.h"

F_REAL FIF(g2_open_x11)(F_REAL *width, F_REAL *height)
{
    return (F_REAL)g2_open_X11(*width, *height);
}

/* g2_open_x11x will be implemented in next releases */

#endif /* DO_X11 */

/**********************************************************/

#ifdef DO_GIF

#include "GIF/g2_GIF.h"

F_REAL FIF(g2_open_gif)(F_CHAR *text, F_REAL *width, F_REAL *height,
			F_CHAR_LENGTH length)
{
    char *str;
    int rv;
    
    str=g2_malloc((length+1)*sizeof(char));
    strncpy(str, text, length);
    str[length]='\0';

    rv=0;
    
    g2_free(str);
    
    return (F_REAL)rv;
}

#endif /* DO_GIF */

/**********************************************************/


F_REAL FIF(g2_open_vd)(void)
{
    return (F_REAL)g2_open_vd();
}


void FIF(g2_attach)(F_REAL *vd_dev, F_REAL *dev)
{
    g2_attach(dtoi(*vd_dev), dtoi(*dev));
}


void FIF(g2_detach)(F_REAL *vd_dev, F_REAL *dev)
{
    g2_detach(dtoi(*vd_dev), dtoi(*dev));
}



void FIF(g2_close)(F_REAL *dev)
{
    g2_close(dtoi(*dev));
}


void FIF(g2_set_auto_flush)(F_REAL *dev, F_REAL *on_off)
{
    g2_set_auto_flush(dtoi(*dev), dtoi(*on_off));
}


void FIF(g2_set_coordinate_system)(F_REAL *dev,
				   F_REAL *x_origin, F_REAL *y_origin,
				   F_REAL *x_mul,    F_REAL *y_mul)
{
    g2_set_coordinate_system(dtoi(*dev),
			     *x_origin, *y_origin,
			     *x_mul,    *y_mul);
}


F_REAL FIF(g2_ld)(void)
{
    return (F_REAL)g2_ld();
}


void FIF(g2_set_ld)(F_REAL *dev)
{
    g2_set_ld(dtoi(*dev));
}



void FIF(g2_flush)(F_REAL *dev)
{
    g2_flush(dtoi(*dev));
}


void FIF(g2_save)(F_REAL *dev)
{
    g2_save(dtoi(*dev));
}




void FIF(g2_arc)(F_REAL *dev, F_REAL *x, F_REAL *y,
		 F_REAL *r1, F_REAL *r2, F_REAL *a1, F_REAL *a2)
{
    g2_arc(dtoi(*dev), *x,  *y, *r1,  *r2,  *a1,  *a2);
}


void FIF(g2_circle)(F_REAL *dev, F_REAL *x, F_REAL *y, F_REAL *r)
{
    g2_circle(dtoi(*dev), *x, *y, *r);
}


void FIF(g2_clear)(F_REAL *dev)
{
    g2_clear(dtoi(*dev));
}


void FIF(g2_clear_palette)(F_REAL *dev)
{
    g2_clear_palette(dtoi(*dev));
}


void FIF(g2_string)(F_REAL *dev, F_REAL *x, F_REAL *y, F_CHAR *text,
		    F_CHAR_LENGTH length)
{
    char *str;
    str=g2_malloc((length+1)*sizeof(char));
    strncpy(str, text, length);
    str[length]='\0';
    g2_string(dtoi(*dev), *x, *y, str);
    g2_free(str);
}


void FIF(g2_ellipse)(F_REAL *dev, F_REAL *x, F_REAL *y, F_REAL *r1, F_REAL *r2)
{
    g2_ellipse(dtoi(*dev), *x, *y, *r1, *r2);
}


void FIF(g2_filled_arc)(F_REAL *dev, F_REAL *x, F_REAL *y,
			F_REAL *r1, F_REAL *r2,
			F_REAL *a1, F_REAL *a2)
{
    g2_filled_arc(dtoi(*dev), *x, *y, *r1, *r2, *a1, *a2);
}


void FIF(g2_filled_circle)(F_REAL *dev, F_REAL *x, F_REAL *y, F_REAL *r)
{
    g2_filled_circle(dtoi(*dev), *x, *y, *r);
}


void FIF(g2_filled_ellipse)(F_REAL *dev, F_REAL *x, F_REAL *y, F_REAL *r1, F_REAL *r2)
{
    g2_filled_ellipse(dtoi(*dev), *x, *y, *r1, *r2);
}


void FIF(g2_filled_triangle)(F_REAL *dev, F_REAL *x1, F_REAL *y1,
			     F_REAL *x2, F_REAL *y2,
			     F_REAL *x3, F_REAL *y3)
{
    g2_filled_triangle(dtoi(*dev), *x1, *y1, *x2, *y2, *x3, *y3);
}


F_REAL  FIF(g2_ink)(F_REAL *dev, F_REAL *red, F_REAL *green, F_REAL *blue)
{
    return (F_REAL)g2_ink(dtoi(*dev), *red, *green, *blue);
}


void FIF(g2_line)(F_REAL *dev, F_REAL *x1, F_REAL *y1, F_REAL *x2, F_REAL *y2)
{
    g2_line(dtoi(*dev), *x1, *y1, *x2, *y2);
}


void FIF(g2_poly_line)(F_REAL *dev, F_REAL N, F_REAL **points)
{
}


void FIF(g2_polygon)(F_REAL *dev, F_REAL N, F_REAL **points)
{
}


void FIF(g2_filled_polygon)(F_REAL *dev, F_REAL N, F_REAL **points)
{
}


void FIF(g2_line_r)(F_REAL *dev, F_REAL *dx, F_REAL *dy)
{
    g2_line_r(dtoi(*dev), *dx, *dy);
}


void FIF(g2_line_to)(F_REAL *dev, F_REAL *x, F_REAL *y)
{
    g2_line_to(dtoi(*dev), *x, *y);
}


void FIF(g2_move)(F_REAL *dev, F_REAL *x, F_REAL *y)
{
    g2_move(dtoi(*dev), *x, *y);
}


void FIF(g2_move_r)(F_REAL *dev, F_REAL *dx, F_REAL *dy)
{
    g2_move_r(dtoi(*dev), *dx, *dy);
}


void FIF(g2_pen)(F_REAL *dev, F_REAL *color)
{
    g2_pen(dtoi(*dev), dtoi(*color));
}


void FIF(g2_plot)(F_REAL *dev, F_REAL *x, F_REAL *y)
{
    g2_plot(dtoi(*dev), *x, *y);
}


void FIF(g2_plot_r)(F_REAL *dev, F_REAL *dx, F_REAL *dy)
{
    g2_plot_r(dtoi(*dev), *dx, *dy);
}


void FIF(g2_rectangle)(F_REAL *dev,
		       F_REAL *x1, F_REAL *y1,
		       F_REAL *x2, F_REAL *y2)
{
    g2_rectangle(dtoi(*dev), *x1, *y1, *x2, *y2);
}


void FIF(g2_filled_rectangle)(F_REAL *dev,
			      F_REAL *x1, F_REAL *y1,
			      F_REAL *x2, F_REAL *y2)
{
    g2_filled_rectangle(dtoi(*dev), *x1, *y1, *x2, *y2);
}


void FIF(g2_reset_palette)(F_REAL *dev)
{
    g2_reset_palette(dtoi(*dev));
}


void FIF(g2_set_background)(F_REAL *dev, F_REAL *color)
{
    g2_set_background(dtoi(*dev), dtoi(*color));
}


void FIF(g2_set_dash)(F_REAL *dev, F_REAL *N, F_REAL **dashes)
{
}


void FIF(g2_set_font_size)(F_REAL *dev, F_REAL *size)
{
    g2_set_font_size(dtoi(*dev), *size);
}


void FIF(g2_set_line_width)(F_REAL *dev, F_REAL *w)
{
    g2_set_line_width(dtoi(*dev), *w);
}


void FIF(g2_triangle)(F_REAL *dev, F_REAL *x1, F_REAL *y1,
		      F_REAL *x2, F_REAL *y2,
		      F_REAL *x3, F_REAL *y3)
{
    g2_triangle(dtoi(*dev), *x1, *y1, *x2, *y2, *x3, *y3);
}


void FIF(g2_set_qp)(F_REAL *dev, F_REAL *d, F_REAL *shape)
{
    g2_set_QP(dtoi(*dev), *d, dtoi(*shape));
}


void FIF(g2_plot_qp)(F_REAL *dev, F_REAL *x, F_REAL *y)
{
    g2_plot_QP(dtoi(*dev), *x, *y);
}
