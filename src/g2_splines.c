/*****************************************************************************
**  Copyright (C) 1998-2001  Ljubomir Milanovic & Horst Wagner
**  Copyright (C) 1999-2006  Tijs Michels
**  This file is part of the g2 library
**
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the GNU Lesser General Public
**  License as published by the Free Software Foundation; either
**  version 2.1 of the License, or (at your option) any later version.
**
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  Lesser General Public License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License along with this library; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/
/*
 * g2_splines.c
 * Tijs Michels
 * tijs@users.sourceforge.net
 * 16/06/99 : initial release
 * 19/02/06 : eliminated duplicates by using pointers to functions
 * 17/02/07 : added cyclic splines
 * 17/03/07 : added Hermite splines (normal and cyclic), which are like the now
 *            deprecated raspln splines, except that the formerly fixed number
 *            of interpolated points per data point is now a function argument
 * 27/10/09 : fixed two array-out-of-bounds bugs and refactored a bit
 * 20/11/09 : added g2_splines_set_points_per_cycle
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "g2.h"
#include "g2_util.h"

/**
 * \ingroup graphic
 * \defgroup splines splines
 */

typedef void calc_f( int, const double *, int, double *);
typedef void calc_d( int, const double *, double, int, double *);

static calc_f g2_c_spline;
static calc_f g2_c_b_spline;
static calc_d g2_c_hermite;
static calc_f g2_c_para_3;
static calc_f g2_c_para_5;

static int points_per_cycle = -1;

static int not_continuously_ascending(int n, const double *x_coord)
{
   const double * const end = x_coord + n + n;
   double prv = *x_coord;
   while((x_coord += 2) < end) {
      double cur = *x_coord;
      if(cur <= prv) {
         fputs("\nERROR: points should have continuously ascending x-coordinates\n", stderr);
         return 1;
      }
      prv = cur;
   }
   return 0;
}

static void surround_points(int nn, const double *points, double *cxy) {
   const double x_step = points[2] - points[0];
   const int ppc = 2 * points_per_cycle;
   int i;
   for (i=0; i < nn; i++) cxy[i+6] = points[i]; /* original points in the middle */
   for (i=0; i < 6; i++) {
      const double x_offset = (3-i/2)*x_step;
      cxy[i]       = points[0]    - x_offset;
      cxy[nn+10-i] = points[nn-2] + x_offset;
      i++; /* y-coordinates */
      if (points_per_cycle == -1) {
         cxy[i]      = points[nn-6+i]; /* copy the last points before the first */
         cxy[nn+6+i] = points[i]; /* and the first points after the last */
      } else {
         cxy[i]      = points[ppc-6+i]; /* copy the last points of the first cycle before the first */
         cxy[nn+6+i] = points[nn-ppc+i]; /* and the first points of the last cycle after the last */
      }
   }
}

static void extend_to_base(int nn, int o, double *slice) {
   int i;
   double base;
   for (i=3, nn *= o, base = slice[1]; i < nn; i+=2) if (slice[i] < base) base = slice[i]; /* need not check slice[nn+1], it should equal slice[1] */
   slice[-2] = slice[0];
   slice[-1] = base;
   slice[nn+2] = slice[nn];
   slice[nn+3] = base;
}

static void g2_print_spline_statistics(int m, int o, const double *sxy)
{
   int i;
   double y, x_min_y, x_max_y, min_y_val, max_y_val, mean, stddev;
   float base, step_y;

   const char * const base_step_y = getenv("G2_SPLINES_VERBOSE");
   if (base_step_y == NULL) return;

   x_min_y = x_max_y = stddev = 0;
   min_y_val = max_y_val = mean = sxy[1];

   for (i = 1; i < m; i++) {
      y = sxy[i+i+1];
      if (y > max_y_val) { max_y_val = y; x_max_y = i; }
      if (y < min_y_val) { min_y_val = y; x_min_y = i; }
      mean += y;
   }
   mean /= m;
   for (i = 1; i < m+m; i += 2) {
      y = sxy[i] - mean;
      stddev += (y * y);
   }
   stddev = sqrt(stddev / m);

   if (sscanf(base_step_y, "%f %f", &base, &step_y) == 2 && step_y != 0) {
      min_y_val = (min_y_val - base) / step_y;
      max_y_val = (max_y_val - base) / step_y;
      mean = (mean - base) / step_y;
      stddev /= step_y;
   }

   printf("\n Min: %.2f at %.2f"
          "\n Max: %.2f at %.2f"
          "\n Range: %.2f"
          "\n Mean: %.3f"
          "\n Standard deviation: %.3f\n",
          min_y_val, x_min_y / o,
          max_y_val, x_max_y / o,
          max_y_val - min_y_val, mean, stddev);
}

/**
 *
 * Set (globally, not per device) the cycle length for cyclic splines.
 * This applies to \e cyclic splines only,
 * and only when they contain \e multiple cycles.
 *
 * Example: for a graph with monthly values spanning multiple years (like
 * \c demo/bargraph/fiveyears.py), set this to 12 (for twelve months), so
 * that the last month of the last year 'connects', not to the first month
 * of the first year (which is likely to be way off), but to the first month
 * of the last year, and the first month of the first year to the last month
 * of the first year, rather than to the last month of the last year.
 *
 * \param n number of points constituting one cycle
 *
 * With \c -1 (the default) the last point of the graph leads
 * to the first, as with graphs that contain just one cycle.
 *
 * \note In g2, splines become cyclic by making parameter \c n
 * (number of data points) negative.
 *
 * \ingroup splines
 */

void g2_splines_set_points_per_cycle(int n) {
   points_per_cycle = n;
}

static void g2_p_cyclic_spline(int id, int n, const double *points, int o, calc_f *f, int filled)
{
   const int m = (n+5)*o+1;
   double * const cxy = (double *) g2_malloc((n+6)*2*sizeof(double));
   double * const sxy = (double *) g2_malloc(m*2*sizeof(double));
   double * const slice = sxy + 5*o;
   surround_points(n+n, points, cxy);

   (*f)(n+6, cxy, m, sxy);
   g2_free(cxy);
   g2_print_spline_statistics(m-5*o, o, sxy+5*o);

   if (filled) {
      extend_to_base(n+n, o, slice);
      g2_filled_polygon(id, n*o+3, slice - 2);
   } else {
      g2_poly_line(id, n*o+1, slice);
   }
   g2_free(sxy);
}

static void g2_p_spline(int id, int n, const double *points, int o, calc_f *f)
{
   if (n < 3) {
      fputs("\nERROR : number of data points input should be at least three\n", stderr);
      return;
   }

   if (not_continuously_ascending(n, points)) return;
   if (o < 0) { /* cyclic graph: the last value should lead to the first */
      if (o % 2) o -= 1; /* make sure o is even */
      g2_p_cyclic_spline(id, n, points, -o, f, 0);
   } else {
      const int m = (n-1)*o+1;
      double * const sxy = (double *) g2_malloc(m*2*sizeof(double));

      (*f)(n, points, m, sxy);
      g2_print_spline_statistics(m, o, sxy);
      g2_poly_line(id, m, sxy);

      g2_free(sxy);
   }
}

static void g2_p_filled_spline(int id, int n, const double *points, int o, calc_f *f)
{
   if (n < 3) {
      fputs("\nERROR : number of data points input should be at least three\n", stderr);
      return;
   }

   if (not_continuously_ascending(n, points)) return;
   if (o < 0) { /* cyclic graph: the last value should lead to the first */
      if (o % 2) o -= 1; /* make sure o is even */
      g2_p_cyclic_spline(id, n, points, -o, f, 1);
   } else {
      const int m = (n-1)*o+3;
      const int mm = m+m;
      double * const sxy = (double *) g2_malloc(mm*sizeof(double));
      double base;
      int i;

      (*f)(n, points, m-2, sxy + 2); /* first and last point are written below */
      g2_print_spline_statistics(m-2, o, sxy+2);
      for (i=5, base = sxy[3]; i < mm-2; i+=2) if (sxy[i] < base) base = sxy[i];
      sxy[0] = sxy[2];
      sxy[1] = base;
      sxy[mm-2] = sxy[mm-4];
      sxy[mm-1] = base;
      g2_filled_polygon(id, m, sxy);
      g2_free(sxy);
   }
}

static void g2_split(int n, const double *points, double *x, double *y)
{
   int i;
   for (i = 0; i < n; i++) {
      x[i] = points[i+i];
      y[i] = points[i+i+1];
   }
}

#define eps 1.e-12

static void g2_c_spline(int n, const double *points, int m, double *sxy)

/*
 *	FUNCTIONAL DESCRIPTION:
 *
 *	Compute a curve of m points (sx[j],sy[j])
 *	-- j being a positive integer < m --
 *	passing through the n data points (x[i],y[i])
 *	-- i being a positive integer < n --
 *	supplied by the user.
 *	The procedure to determine sy[j] involves
 *	Young's method of successive over-relaxation.
 *
 *	FORMAL ARGUMENTS:
 *
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	m			number of interpolated points; m = (n-1)*o+1
 *				for o curve points for every data point
 *	sxy			interpolated points (sx[j],sy[j])
 *
 *	IMPLICIT INPUTS:	NONE
 *	IMPLICIT OUTPUTS:	NONE
 *	SIDE EFFECTS:		NONE
 *
 *	REFERENCES:
 *
 *	1. Ralston and Wilf, Mathematical Methods for Digital Computers,
 *	   Vol. II, John Wiley and Sons, New York 1967, pp. 156-158.
 *	2. Greville, T.N.E., Ed., Proceedings of An Advanced Seminar
 *	   Conducted by the Mathematics Research Center, U.S. Army,
 *	   University of Wisconsin, Madison. October 7-9, 1968. Theory
 *	   and Applications of Spline Functions, Academic Press,
 *	   New York / London 1969, pp. 156-167.
 *
 *	AUTHORS:
 *
 *	Josef Heinen	04/06/88	<J.Heinen@KFA-Juelich.de>
 *	Tijs Michels	06/16/99	<t.michels@vimec.nl>
 */

{
   int i, j;
   double * const x = (double *) g2_malloc(n*4*sizeof(double));
   double * const y = x + n;
   double * const g = y + n;
   double * const h = g + n; /* for the constant copy of g */
   double k, u, delta_g;

   g2_split(n, points, x, y);

   n--; /* last value index */
   k =  x[0]; /* look up once */
   u = (x[n] - k) / (m - 1); /* calculate step outside loop */
   for (j = 0; j < m; j++)	sxy[j+j] = j * u + k; /* x-coordinates */

   g[0] = 0.;
   for (i = 1; i < n; i++) {
      g[i] = 2. * ((y[i+1] - y[i]) / (x[i+1] - x[i]) -
		   (y[i] - y[i-1]) / (x[i] - x[i-1]))
	/ (x[i+1] - x[i-1]); /* whereas g[i] will later be changed repeatedly */
      h[i] = 1.5 * g[i];     /* copy h[i] of g[i] will remain constant */
   }
   g[n] = 0.;

   k = 0.;

   do {
      for (u = 0., i = 1; i < n; i++) {
	 delta_g = .5 * (x[i] - x[i-1]) / (x[i+1] - x[i-1]);
	 delta_g = (h[i] -
		    g[i] -
		    g[i-1] * delta_g -      /* 8. - 4 * sqrt(3.) */
		    g[i+1] * (.5 - delta_g)) * 1.0717967697244907832;
	 g[i] += delta_g;

	 if (fabs(delta_g) > u) u = fabs(delta_g);
      }	/* On loop termination u holds the largest delta_g. */

      if (k == 0.)	k = u * eps;
	/* Only executed once, at the end of pass one. So k preserves
	 * the largest delta_g of pass one, multiplied by eps.
	 */
   } while (u > k);

   m += m, i = 0, j = 0;
   do {
      u = sxy[j++]; /* x-coordinate */
      if (u > x[i+1] && i < n-1) i++; /* i should end on n-1 */
      k = (u - x[i]) / (x[i+1] - x[i]); /* calculate outside loop */
      sxy[j++] = y[i] +
	(y[i+1] - y[i]) * k +
	(u - x[i]) * (u - x[i+1]) *
	((2. - k) * g[i] +
	 (1. + k) * g[i+1]) / 6.; /* y-coordinate */
   } while (j < m);
   g2_free(x);
}

/**
 *
 * Using Young's method of successive over-relaxation,
 * plot a spline curve with \a o interpolated points per data point.
 * So the larger \a o, the more fluent the curve.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 * \param o number of interpolated points per data point, negative for a cyclic spline
 *
 * With \a o < 0, the spline ends are calculated in such a way that the graph
 * begins and ends at the same value. This is meant for cyclic data, like
 * per hour (day cycle), per day (week cycle), or per month (year cycle).
 * See the fluent line from December to January in sample \c bargraph.py.
 *
 * \ingroup splines
 */
void g2_spline(int dev, int n, double *points, int o)
{
   g2_p_spline(dev, n, points, o, g2_c_spline);
}

/**
 *
 * Using Young's method of successive over-relaxation,
 * plot a filled spline curve with \a o interpolated points per data point.
 * So the larger \a o, the more fluent the curve.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 * \param o number of interpolated points per data point, negative for a cyclic spline
 *
 * \ingroup splines
 */
void g2_filled_spline(int dev, int n, double *points, int o)
{
   g2_p_filled_spline(dev, n, points, o, g2_c_spline);
}

static void g2_c_b_spline(int n, const double *points, int m, double *sxy)

/*
 * g2_c_b_spline takes n input points. It uses parameter t
 * to compute sx(t) and sy(t) respectively
 */

{
   int i, j, k;
   double * const x = (double *) g2_malloc(n*2*sizeof(double));
   double * const y = x + n;
   double t, bl1, bl2, bl3, bl4;
   double interval, xi_m1, yi_m1, xi_p2, yi_p2;
   const int o = 2 * (m-1)/(n-1); /* (m-1)/(n-1) = number of curve points per x-step */

   g2_split(n, points, x, y);

   m--;
   n--;
   interval = (double)n / m;

   for (m += m, i = 0, j = 0, k = o; i < n; i++, k+=o) {
      if (i == 0) {
	 xi_m1 = 2 * x[0] - x[1];
	 yi_m1 = 2 * y[0] - y[1];
      } else {
	 xi_m1 = x[i-1];
	 yi_m1 = y[i-1];
      }
      if (i == n-1) {
	 xi_p2 = 2 * x[n] - x[n-1];
	 yi_p2 = 2 * y[n] - y[n-1];
      } else {
	 xi_p2 = x[i+2];
	 yi_p2 = y[i+2];
      }

      t = fmod(j * interval, 1.);

      while (t < 1. && j < k) {
	 bl1 = (1. - t);
	 bl2 = t * t;	/* t^2 */
	 bl4 = t * bl2;	/* t^3 */
	 bl3 = bl4 - bl2;

	 bl1 = bl1 * bl1 * bl1;
	 bl2 = 3. * (bl3 - bl2) + 4.;
	 bl3 = 3. * (  t - bl3) + 1.;

	 sxy[j++] = (bl1 * xi_m1 + bl2 * x[i] + bl3 * x[i+1] + bl4 * xi_p2) / 6.; /* x-coordinate */
	 sxy[j++] = (bl1 * yi_m1 + bl2 * y[i] + bl3 * y[i+1] + bl4 * yi_p2) / 6.; /* y-coordinate */

	 t += interval;
      }
   }
   sxy[m]   = x[n];
   sxy[m+1] = y[n];
   g2_free(x);
}

/**
 *
 * Plot a uniform cubic B-spline curve with \a o interpolated points per data point.
 * So the larger \a o, the more fluent the curve.
 * For most averaging purposes, this is the right spline.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 * \param o number of interpolated points per data point, negative for a cyclic spline
 *
 * With \a o < 0, the spline ends are calculated in such a way that they share
 * the same \e y coordinate. This suits cyclic data, like per hour (day cycle),
 * per day (week cycle), or per month (year cycle). See the smooth transition
 * from December to January in sample \c bargraph.py.
 *
 * \ingroup splines
 */
void g2_b_spline(int dev, int n, double *points, int o)
{
   g2_p_spline(dev, n, points, o, g2_c_b_spline);
}

/**
 *
 * Plot a filled uniform cubic B-spline curve with \a o interpolated points per data point.
 * So the larger \a o, the more fluent the curve.
 * For most averaging purposes, this is the right spline.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 * \param o number of interpolated points per data point, negative for a cyclic spline
 *
 * \ingroup splines
 */
void g2_filled_b_spline(int dev, int n, double *points, int o)
{
   g2_p_filled_spline(dev, n, points, o, g2_c_b_spline);
}

/*
 *	FUNCTION g2_c_hermite
 *
 *	FUNCTIONAL DESCRIPTION:
 *
 *	This function draws a piecewise cubic polynomial through
 *	the specified data points. The (n-1) cubic polynomials are
 *	basically parametric cubic Hermite polynomials through the
 *	n specified data points with tangent values at the data
 *	points determined by a weighted average of the slopes of
 *	the secant lines. A tension parameter "tn" is provided to
 *	adjust the length of the tangent vector at the data points.
 *	This allows the "roundness" of the curve to be adjusted.
 *	For further information and references on this technique see:
 *
 *	D. Kochanek and R. Bartels, Interpolating Splines With Local
 *	Tension, Continuity and Bias Control, Computer Graphics,
 *	18(1984)3.
 *
 *	AUTHORS:
 *
 *	Dennis Mikkelson	distributed in GPLOT	Jan 7, 1988	F77
 *	Tijs Michels		t.michels@vimec.nl	Jun 7, 1999	C
 *
 *	FORMAL ARGUMENTS:
 *
 *	n	number of data points, n > 2
 *	points	double array holding the x and y-coords of the data points
 *	tn	double parameter in [0.0, 2.0]. When tn = 0.0,
 *		the curve through the data points is very rounded.
 *		As tn increases the curve is gradually pulled tighter.
 *		When tn = 2.0, the curve is essentially a polyline
 *		through the given data points.
 *	nb	number of straight connecting lines of which each polynomial
 *		consists. So between one data point and the next, (nb-1) points
 *		are placed.
 *	sxy	double array holding the coords of the spline curve
 *
 *	IMPLICIT INPUTS:	NONE
 *	IMPLICIT OUTPUTS:	NONE
 *	SIDE EFFECTS:		NONE
 */

static void g2_c_hermite(int n, const double *points, double tn, int nb, double *sxy)
{
   int i, j;
   double bias, tnFactor, tangentL1, tangentL2;
   double D1x, D1y, D2x, D2y, t1x, t1y, t2x, t2y;

   /* Values of the Hermite basis functions */
   /* at nb+1 evenly spaced points in [0,1] */
   double * const h1 = (double *) g2_malloc(nb*4*sizeof(double));
   double * const h2 = h1 + nb;
   double * const h3 = h2 + nb;
   double * const h4 = h3 + nb;

   double * const x = (double *) g2_malloc(n*2*sizeof(double));
   double * const y = x + n;
   g2_split(n, points, x, y);

/*
 * First, store the values of the Hermite basis functions in a table h[ ]
 * so no time is wasted recalculating them
 */
   for (i = 0; i < nb; i++) {
      double t, tt, ttt;
      t = (double) i / nb;
      tt  = t * t;
      ttt = t * tt;
      h1[i] =  2. * ttt - 3. * tt + 1.;
      h2[i] = -2. * ttt + 3. * tt;
      h3[i] =       ttt - 2. * tt + t;
      h4[i] =       ttt -      tt;
   }

/*
 * Set local tnFactor based on input parameter tn
 */
   if (tn <= 0.) {
      tnFactor = 2.;
      fputs("g2_c_hermite: Using Tension Factor 0.0: very rounded", stderr);
   }
   else if (tn >= 2.) {
      tnFactor = 0.;
      fputs("g2_c_hermite: Using Tension Factor 2.0: not rounded at all", stderr);
   }
   else			tnFactor = 2. - tn;

   D1x = D1y = 0.; /* first point has no preceding point */
   for (j = 0; j < n - 2; j++) {
      t1x = x[j+1] - x[j];
      t1y = y[j+1] - y[j];
      t2x = x[j+2] - x[j+1];
      t2y = y[j+2] - y[j+1];
      tangentL1 = t1x * t1x + t1y * t1y;
      tangentL2 = t2x * t2x + t2y * t2y;
      if (tangentL1 + tangentL2 == 0) bias = .5;
      else bias = tangentL2 / (tangentL1 + tangentL2);
      D2x = tnFactor * (bias  * t1x + (1 - bias) * t2x);
      D2y = tnFactor * (bias  * t1y + (1 - bias) * t2y);
      for (i = 0; i < nb; i++) {
	sxy[2 * nb * j + i + i] =
	   h1[i] * x[j] + h2[i] * x[j+1] + h3[i] * D1x + h4[i] * D2x;
	sxy[2 * nb * j + i + i + 1] =
	   h1[i] * y[j] + h2[i] * y[j+1] + h3[i] * D1y + h4[i] * D2y;
      }
      D1x = D2x; /* store as preceding point in */
      D1y = D2y; /* the next pass */
   }

/*
 * Do the last subinterval as a special case since no point follows the
 * last point
 */
   for (i = 0; i < nb; i++) {
      sxy[2 * nb * (n-2) + i + i] =
	h1[i] * x[n-2] + h2[i] * x[n-1] + h3[i] * D1x;
      sxy[2 * nb * (n-2) + i + i + 1] =
	h1[i] * y[n-2] + h2[i] * y[n-1] + h3[i] * D1y;
   }
   i = 2 * nb * (n-1);
   sxy[i]=x[n-1];
   sxy[i+1]=y[n-1];
   g2_free(x);
   g2_free(h1);
}

static void g2_p_cyclic_hermite(int id, int n, const double *points, double tn, int o, int filled)
{
   const int m = (n+5)*o+1;
   double * const cxy = (double *) g2_malloc((n+6)*2*sizeof(double));
   double * const sxy = (double *) g2_malloc(m*2*sizeof(double));
   double * const slice = sxy + 5*o;
   surround_points(n+n, points, cxy);

   g2_c_hermite(n+6, cxy, tn, o, sxy);
   g2_free(cxy);
   g2_print_spline_statistics(m-5*o, o, sxy+5*o);

   if (filled) {
      extend_to_base(n+n, o, slice);
      g2_filled_polygon(id, n*o+3, slice - 2);
   } else {
      g2_poly_line(id, n*o+1, slice);
   }
   g2_free(sxy);
}

/**
 *
 * Plot a piecewise cubic polynomial with adjustable roundness
 * through the given data points.
 * Each Hermite polynomial between two data points is made up of 40 lines.
 * Tension factor \a tn must be between 0.0 (very rounded)
 * and 2.0 (not rounded at all, i.e. essentially a \ref g2_poly_line "polyline").
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 * \param tn tension factor in the range [0.0, 2.0]
 * \param o number of interpolated points per data point, negative for a cyclic spline
 *
 * \ingroup splines
 */
void g2_hermite(int dev, int n, double *points, double tn, int o)
{
   if (not_continuously_ascending(n, points)) return;
   if (o < 0) { /* cyclic graph: the last value should lead to the first */
      if (o % 2) o -= 1; /* make sure o is even */
      g2_p_cyclic_hermite(dev, n, points, tn, -o, 0);
   } else {
      const int m = (n-1)*o+1;
      double * const sxy = (double *) g2_malloc(m*2*sizeof(double)); /* coords of the entire spline curve */

      g2_c_hermite(n, points, tn, o, sxy);
      g2_print_spline_statistics(m, o, sxy);
      g2_poly_line(dev, m, sxy);

      g2_free(sxy);
   }
}

/**
 *
 * Plot a filled piecewise cubic polynomial with adjustable roundness
 * through the given data points.
 * Each Hermite polynomial between two data points is made up of 40 lines.
 * Tension factor \a tn must be between 0.0 (very rounded)
 * and 2.0 (not rounded at all, i.e. essentially a \ref g2_poly_line "polyline").
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 * \param tn tension factor in the range [0.0, 2.0]
 * \param o number of interpolated points per data point, negative for a cyclic spline
 *
 * \ingroup splines
 */
void g2_filled_hermite(int dev, int n, double *points, double tn, int o)
{
   if (not_continuously_ascending(n, points)) return;
   if (o < 0) { /* cyclic graph: the last value should lead to the first */
      if (o % 2) o -= 1; /* make sure o is even */
      g2_p_cyclic_hermite(dev, n, points, tn, -o, 1);
   } else {
      const int m = (n-1)*o+3;
      const int mm = m+m;
      double * const sxy = (double *) g2_malloc(mm*sizeof(double)); /* coords of the entire spline curve */
      double base;
      int i;

      g2_c_hermite(n, points, tn, o, sxy + 2); /* first and last point are written below */
      g2_print_spline_statistics(m-2, o, sxy+2);
      for (i=5, base = sxy[3]; i < mm-2; i+=2) if (sxy[i] < base) base = sxy[i];
      sxy[0] = sxy[2];
      sxy[1] = base;
      sxy[mm-2] = sxy[mm-4];
      sxy[mm-1] = base;
      g2_filled_polygon(dev, m, sxy);
      g2_free(sxy);
   }
}

/* Both functions below are for backward compatibility only */

/**
 *
 * For backward compatibility, as \ref g2_hermite, but without argument \c o.
 * The number of interpolated points per data point is fixed at 40.
 *
 * \ingroup splines
 */

void g2_raspln(int dev, int n, double *points, double tn)
{
   g2_hermite(dev, n, points, tn, 40);
}

/**
 *
 * For backward compatibility, as \ref g2_filled_hermite, but without argument \c o.
 * The number of interpolated points per data point is fixed at 40.
 *
 * \ingroup splines
 */

void g2_filled_raspln(int dev, int n, double *points, double tn)
{
   g2_filled_hermite(dev, n, points, tn, 40);
}

/* ---- And now for a rather different approach ---- */

/*
 *	FUNCTION g2_c_newton
 *
 *	FUNCTIONAL DESCRIPTION:
 *
 *	Use Newton's Divided Differences to calculate an interpolation
 *	polynomial through the specified data points.
 *	This function is called by
 *		g2_c_para_3 and
 *		g2_c_para_5.
 *
 *	Dennis Mikkelson	distributed in GPLOT	Jan  5, 1988	F77
 *	Tijs Michels		t.michels@vimec.nl	Jun 16, 1999	C
 *
 *	FORMAL ARGUMENTS:
 *
 *	n	number of entries in c1 and c2, 4 <= n <= MaxPts
 *		for para_3	(degree 3)	n = 4
 *		for para_5	(degree 5)	n = 6
 *		for para_i	(degree i)	n = (i + 1)
 *	c1	double array holding at most MaxPts values giving the
 *		first  coords of the points to be interpolated
 *	c2	double array holding at most MaxPts values giving the
 *		second coords of the points to be interpolated
 *	o	number of points at which the interpolation
 *		polynomial is to be evaluated
 *	xv	double array holding o points at which to
 *		evaluate the interpolation polynomial
 *	yv	double array holding upon return the values of the
 *		interpolation polynomial at the corresponding points in xv
 *
 *		yv is the OUTPUT
 *
 *	IMPLICIT INPUTS:	NONE
 *	IMPLICIT OUTPUTS:	NONE
 *	SIDE EFFECTS:		NONE
 */

#define MaxPts 21
#define xstr(s) __str(s)
#define __str(s) #s

/*
 * Maximum number of data points allowed
 * 21 would correspond to a polynomial of degree 20
 */

static void g2_c_newton(int n, const double *c1, const double *c2,
			int o, const double *xv, double *yv)
{
   int i, j;
   double p, s;
   double ddt[MaxPts][MaxPts];		/* Divided Difference Table */

   if (n < 4) {
      fputs("g2_c_newton: Error! Less than 4 points passed "
	    "to function g2_c_newton\n", stderr);
      return;
   }

   if (n > MaxPts) {
      fputs("g2_c_newton: Error! More than " xstr(MaxPts) " points passed "
	    "to function g2_c_newton\n", stderr);
      return;
   }

/* First, build the divided difference table */

   for (i = 0; i < n; i++)	ddt[i][0] = c2[i];
   for (j = 1; j < n; j++) {
      for (i = 0; i < n - j; i++)
	ddt[i][j] = (ddt[i+1][j-1] - ddt[i][j-1]) / (c1[i+j] - c1[i]);
   }

/* Next, evaluate the polynomial at the specified points */

   for (i = 0; i < o; i++) {
      for (p = 1., s = ddt[0][0], j = 1; j < n; j++) {
	 p *= xv[i] - c1[j-1];
	 s += p * ddt[0][j];
      }
      yv[i] = s;
   }
}

/*
 *	FUNCTION: g2_c_para_3
 *
 *	FUNCTIONAL DESCRIPTION:
 *
 *	This function draws a piecewise parametric interpolation
 *	polynomial of degree 3 through the specified data points.
 *	The effect is similar to that obtained using DISSPLA to
 *	draw a curve after a call to the DISSPLA routine PARA3.
 *	The curve is parameterized using an approximation to the
 *	curve's arc length. The basic interpolation is done
 *	using function g2_c_newton.
 *
 *	Dennis Mikkelson	distributed in GPLOT	Jan  7, 1988	F77
 *	Tijs Michels		t.michels@vimec.nl	Jun 17, 1999	C
 *
 *	FORMAL ARGUMENTS:
 *
 *	n	number of data points through which to draw the curve
 *	points	double array containing the x and y-coords of the data points
 *
 *	IMPLICIT INPUTS:	NONE
 *	IMPLICIT OUTPUTS:	NONE
 *	SIDE EFFECTS:		NONE
 */

#define nb 40
/*
 * Number of straight connecting lines of which each polynomial consists.
 * So between one data point and the next, (nb-1) points are placed.
 */

static void g2_c_para_3(int n, const double *points, int m, double *sxy)
{
#define dgr	(3+1)
#define nb2	(nb*2)
   int i, j;
   double x1t, y1t;
   double o, step;
   double X[nb2];		/* x-coords of the current curve piece */
   double Y[nb2];		/* y-coords of the current curve piece */
   double t[dgr];		/* data point parameter values */
   double Xpts[dgr];		/* x-coords data point subsection */
   double Ypts[dgr];		/* y-coords data point subsection */
   double s[nb2];		/* parameter values at which to interpolate */
   m = m;			/* dummy argument; stop compiler complaints */

   /* Do first TWO subintervals first */

   g2_split(dgr, points, Xpts, Ypts);

   t[0] = 0.;
   for (i = 1; i < dgr; i++) {
      x1t = Xpts[i] - Xpts[i-1];
      y1t = Ypts[i] - Ypts[i-1];
      t[i] = t[i-1] + sqrt(x1t * x1t + y1t * y1t);
   }

   step = t[2] / nb2;
   for (i = 0; i < nb2; i++)	s[i] = i * step;

   g2_c_newton(dgr, t, Xpts, nb2, s, X);
   g2_c_newton(dgr, t, Ypts, nb2, s, Y);
   for (i = 0; i < nb2; i++) {
      sxy[i+i]   = X[i];
      sxy[i+i+1] = Y[i];
   }

   /* Next, do later central subintervals */

   for (j = 1; j < n - dgr + 1; j++) {
      g2_split(dgr, points + j + j, Xpts, Ypts);

      for (i = 1; i < dgr; i++) {
	 x1t = Xpts[i] - Xpts[i-1];
	 y1t = Ypts[i] - Ypts[i-1];
	 t[i] = t[i-1] + sqrt(x1t * x1t + y1t * y1t);
      }

      o = t[1]; /* look up once */
      step = (t[2] - o) / nb;
      for (i = 0; i < nb; i++)	s[i] = i * step + o;

      g2_c_newton(dgr, t, Xpts, nb, s, X);
      g2_c_newton(dgr, t, Ypts, nb, s, Y);

      for (i = 0; i < nb; i++) {
	 sxy[(j + 1) * nb2 + i + i]     = X[i];
	 sxy[(j + 1) * nb2 + i + i + 1] = Y[i];
      }
   }

   /* Now do last subinterval */

   o = t[2];
   step = (t[3] - o) / nb;
   for (i = 0; i < nb; i++)	s[i] = i * step + o;

   g2_c_newton(dgr, t, Xpts, nb, s, X);
   g2_c_newton(dgr, t, Ypts, nb, s, Y);

   for (i = 0; i < nb; i++) {
      sxy[(n - dgr + 2) * nb2 + i + i]     = X[i];
      sxy[(n - dgr + 2) * nb2 + i + i + 1] = Y[i];
   }
   sxy[(n - 1) * nb2]     = points[n+n-2];
   sxy[(n - 1) * nb2 + 1] = points[n+n-1];
}

/**
 *
 * Using Newton's Divided Differences method, plot a piecewise
 * parametric interpolation polynomial of degree 3
 * through the given data points.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 *
 * \ingroup splines
 */
void g2_para_3(int dev, int n, double *points)
{
   g2_p_spline(dev, n, points, nb, g2_c_para_3);
}

/**
 *
 * Using Newton's Divided Differences method, plot a filled piecewise
 * parametric interpolation polynomial of degree 3
 * through the given data points.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 *
 * \ingroup splines
 */
void g2_filled_para_3(int dev, int n, double *points)
{
   g2_p_filled_spline(dev, n, points, nb, g2_c_para_3);
}

/*
 *	FUNCTION: g2_c_para_5
 *
 *	As g2_c_para_3, but now plot a polynomial of degree 5
 */

/*
 * Number of straight connecting lines of which each polynomial consists.
 * So between one data point and the next, (nb-1) points are placed.
 */

static void g2_c_para_5(int n, const double *points, int m, double *sxy)
{
#undef	dgr
#define dgr	(5+1)
#define nb3	(nb*3)
   int i, j;
   double x1t, y1t;
   double o, step;
   double X[nb3];		/* x-coords of the current curve piece */
   double Y[nb3];		/* y-coords of the current curve piece */
   double t[dgr];		/* data point parameter values */
   double Xpts[dgr];		/* x-coords data point subsection */
   double Ypts[dgr];		/* y-coords data point subsection */
   double s[nb3];		/* parameter values at which to interpolate */
   m = m;			/* dummy argument; stop compiler complaints */

   /* Do first THREE subintervals first */

   g2_split(dgr, points, Xpts, Ypts);

   t[0] = 0.;
   for (i = 1; i < dgr; i++) {
      x1t = Xpts[i] - Xpts[i-1];
      y1t = Ypts[i] - Ypts[i-1];
      t[i] = t[i-1] + sqrt(x1t * x1t + y1t * y1t);
   }

   step = t[3] / nb3;
   for (i = 0; i < nb3; i++)	s[i] = i * step;

   g2_c_newton(dgr, t, Xpts, nb3, s, X);
   g2_c_newton(dgr, t, Ypts, nb3, s, Y);
   for (i = 0; i < nb3; i++) {
      sxy[i+i]   = X[i];
      sxy[i+i+1] = Y[i];
   }

   /* Next, do later central subintervals */

   for (j = 1; j < n - dgr + 1; j++) {
      g2_split(dgr, points + j + j, Xpts, Ypts);

      for (i = 1; i < dgr; i++) {
	 x1t = Xpts[i] - Xpts[i-1];
	 y1t = Ypts[i] - Ypts[i-1];
	 t[i] = t[i-1] + sqrt(x1t * x1t + y1t * y1t);
      }

      o = t[2]; /* look up once */
      step = (t[3] - o) / nb;
      for (i = 0; i < nb; i++)	s[i] = i * step + o;

      g2_c_newton(dgr, t, Xpts, nb, s, X);
      g2_c_newton(dgr, t, Ypts, nb, s, Y);

      for (i = 0; i < nb; i++) {
	 sxy[(j + 2) * nb2 + i + i]     = X[i];
	 sxy[(j + 2) * nb2 + i + i + 1] = Y[i];
      }
   }

   /* Now do last TWO subinterval */

   o = t[3];
   step = (t[5] - o) / nb2;
   for (i = 0; i < nb2; i++)	s[i] = i * step + o;

   g2_c_newton(dgr, t, Xpts, nb2, s, X);
   g2_c_newton(dgr, t, Ypts, nb2, s, Y);

   for (i = 0; i < nb2; i++) {
      sxy[(n - dgr + 3) * nb2 + i + i]     = X[i];
      sxy[(n - dgr + 3) * nb2 + i + i + 1] = Y[i];
   }
   sxy[(n - 1) * nb2]     = points[n+n-2];
   sxy[(n - 1) * nb2 + 1] = points[n+n-1];
}

/**
 *
 * Using Newton's Divided Differences method, plot a piecewise
 * parametric interpolation polynomial of degree 5
 * through the given data points.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 *
 * \ingroup splines
 */
void g2_para_5(int dev, int n, double *points)
{
   g2_p_spline(dev, n, points, nb, g2_c_para_5);
}

/**
 *
 * Using Newton's Divided Differences method, plot a filled piecewise
 * parametric interpolation polynomial of degree 5
 * through the given data points.
 *
 * \param dev device id
 * \param n number of data points (not the size of buffer \a points)
 * \param points buffer of \a n data points x1, y1, ... x\a n, y\a n
 *
 * \ingroup splines
 */
void g2_filled_para_5(int dev, int n, double *points)
{
   g2_p_filled_spline(dev, n, points, nb, g2_c_para_5);
}
