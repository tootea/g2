/*****************************************************************************
**  Copyright (C) 1998-2001  Ljubomir Milanovic & Horst Wagner
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
 * tijs@vimec.nl
 * 06/16/99
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <g2.h>
#include <g2_util.h>

#define eps 1.0e-12

void g2_split(int n, int o, double *points, double *x, double *y);
void g2_c_spline(int n, double *points, int m, double *sxy);
void g2_c_b_spline(int n, double *points, int m, double *sxy);
void g2_c_raspln(int n, double *points, double tn, double *sxy);
void g2_c_newton(int n, double *c1, double *c2, int o, double *xv, double *yv);
void g2_c_para_3(int n, double *points, double *sxy);
void g2_c_para_5(int n, double *points, double *sxy);

void g2_split(int n, int o, double *points, double *x, double *y)
{
   int i;
   for (i = 0; i < n; i++) {
      x[i] = points[(o+o+i+i)];
      y[i] = points[(o+o+i+i+1)];
   }
}

void g2_c_spline(int n, double *points, int m, double *sxy)

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
 *	m			number of interpolated points
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
 *	Tijs Michels	06/16/99	<M.H.M.Michels@kub.nl>
 */

{
   int i, j;
   double *x;
   double *y;
   double *g;
   double p, w, k, u, delta_g;

   x = (double *) calloc (sizeof(double), n);
   y = (double *) calloc (sizeof(double), n);
   g2_split(n, 0, points, x, y);

   u = (x[(n-1)] - x[0]) / (m-1);
   for (j = 0; j < m; j++)	sxy[(j+j)] = ((j * u) + x[0]);

   g = (double *) calloc (sizeof(double), (n+n));

   for (i = 1; i < (n-1); i++) {
      *(g+i) = 2. * (((y[(i+1)] - y[i]) / (x[(i+1)] - x[i])) -
		     ((y[i] - y[(i-1)]) / (x[i] - x[(i-1)])))
		  / (x[(i+1)] - x[(i-1)]);
      *(g+n+i) = 1.5 * *(g+i);
   }

   w = 8. - (4. * sqrt(3.));
   k = 0;

   do
      {
	u = 0;

	for (i = 1; i < (n-1); i++) {
	   p = .5 * (x[i] - x[(i-1)]) / (x[(i+1)] - x[(i-1)]);
	   delta_g = w * (-*(g+i) - (p * *(g+i-1)) -
			     ((.5 - p) * *(g+i+1)) + *(g+n+i));
	   *(g+i) = *(g+i) + delta_g;

	   if (fabs(delta_g) > u)	u = fabs(delta_g);
	}	/* On loop termination u holds the largest delta_g. */

	if (k == 0)	k = (u * eps);
		/* Only executed once, at the end of pass one. So k preserves
		 * the largest delta_g of pass one multiplied by eps.
		 */
      }
   while (u > k);

   for (j = 0; j < m; j++) {
      i = 1;

      while (x[i] < sxy[(j+j)])
	   i++;

      i--;

      if (i >= n)	i = (n-1);

      sxy[((j+j)+1)] = (y[i] +
		((sxy[(j+j)] - x[i]) * (y[(i+1)] - y[i]) / (x[(i+1)] - x[i])) +
		((sxy[(j+j)] - x[i]) * (sxy[(j+j)] - x[(i+1)]) *
		 ((2. * *(g+i)) + *(g+i+1) +
		  ((sxy[(j+j)] - x[i]) * (*(g+i+1) - *(g+i)) /
		   (x[(i+1)] - x[i])))
		 / 6.));
   }
   free (x);
   free (y);
   free (g);
}

void g2_spline(int id, int n, double *points, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 *
 *	Given an array of n data points {x1, y1, ..., xn, yn} a spline curve
 *	is plotted on device id with o interpolated points per data point.
 *	So the larger o, the more fluent the curve.
 */

{
   int m;
   double *sxy;

   m=(((n-1)*o)+1);
   sxy=(double*)g2_malloc((m+m)*sizeof(double));
   
   g2_c_spline(n, points, m, sxy);
   g2_poly_line(id, m, sxy);

   g2_free(sxy);
}

void g2_filled_spline(int id, int n, double *points, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
   int m;
   double *sxy;

   m=(((n-1)*o)+1);
   sxy=(double*)g2_malloc((m+m+2)*sizeof(double));
   
   g2_c_spline(n, points, m, sxy);
   sxy[(m+m)] = points[(n+n-2)];
   sxy[(m+m+1)] = points[1];
   g2_filled_polygon(id, (m+1), sxy);
   g2_free(sxy);
}

void g2_c_b_spline(int n, double *points, int m, double *sxy)

/*
 * g2_c_b_spline takes n input points. It uses parameter t
 * to compute sx(t) and sy(t) respectively
 */

{
   int i, j;
   double *x;
   double *y;
   double t, bl1, bl2, bl3, bl4;
   double interval, xi_3, yi_3, xi, yi;

   interval = (double)(n-1) / (double)(m-1);

   x = (double *) calloc (sizeof(double), n);
   y = (double *) calloc (sizeof(double), n);
   g2_split(n, 0, points, x, y);

   for (i = 2, j = 0; i <= n; i++) {
      if (i == 2) {
	xi_3 = x[0] - (x[1] - x[0]);
	yi_3 = ((y[1] * (xi_3 - x[0])) -
		(y[0] * (xi_3 - x[1]))) /
	       (x[1] - x[0]);
      }
      else {
	xi_3 = x[(i-3)];
	yi_3 = y[(i-3)];
      }
      if (i == n) {
	xi = x[(n-1)] + (x[(n-1)] - x[(n-2)]);
	yi = ((y[(n-1)] * (xi - x[(n-2)])) -
	      (y[(n-2)] * (xi - x[(n-1)]))) /
	     (x[(n-1)] - x[(n-2)]);
      }
      else {
	xi = x[i];
	yi = y[i];
      }

      t = fmod((j * interval), 1.0);

      while (t < 1.0 && j < (m-1)) {
	bl1 = ((1.0 - t) * (1.0 - t) * (1.0 - t)) / 6.0;
	bl2 = (( 3.0 * t * t * t) - (6.0 * t * t) + 4.0) / 6.0;
	bl3 = ((-3.0 * t * t * t) + (3.0 * t * t) + (3.0 * t) + 1.0) / 6.0;
	bl4 = t * t * t / 6.0;

	sxy[ (j+j)]    = (bl1 * xi_3) +
			 (bl2 * x[(i-2)]) +
			 (bl3 * x[(i-1)]) +
			 (bl4 * xi);
	sxy[((j+j)+1)] = (bl1 * yi_3) +
			 (bl2 * y[(i-2)]) +
			 (bl3 * y[(i-1)]) +
			 (bl4 * yi);

	t += interval;
	j++;
      }
   }
   sxy[(m+m-2)] = x[(n-1)];
   sxy[(m+m-1)] = y[(n-1)];
   free(x);
   free(y);
}

void g2_b_spline(int id, int n, double *points, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
   int m;
   double *sxy;

   m=(((n-1)*o)+1);
   sxy=(double*)g2_malloc((m+m)*sizeof(double));
   
   g2_c_b_spline(n, points, m, sxy);
   g2_poly_line(id, m, sxy);

   g2_free(sxy);
}

void g2_filled_b_spline(int id, int n, double *points, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
   int m;
   double *sxy;

   m = (((n-1)*o)+1);
   sxy=(double*)g2_malloc((m+m+2)*sizeof(double));
   
   g2_c_b_spline(n, points, m, sxy);
   sxy[(m+m)] = points[(n+n-2)];
   sxy[(m+m+1)] = points[1];
   g2_filled_polygon(id, (m+1), sxy);

   g2_free(sxy);
}

/*
 *	FUNCTION g2_c_raspln
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
 *	Tension, Continuitiy and Bias Control, Computer Graphics,
 *	18(1984)3.
 *
 *	AUTHORS:
 *
 *	Dennis Mikkelson	distributed in GPLOT	Jan 7, 1988	F77
 *	Tijs Michels		M.H.M.Michels@kub.nl	Jun 7, 1999	C
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
 *	sxy	double array holding the coords of the spline curve
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

void g2_c_raspln(int n, double *points, double tn, double *sxy)
{
   int i, j;
   double *x;
   double *y;
   double t, bias, tnFactor, tangentL1, tangentL2;
   double D1x, D1y, D2x, D2y;
   double h1[(nb+1)];	/*	Values of the Hermite basis functions */
   double h2[(nb+1)];	/*	at nb+1 evenly spaced points in [0,1] */
   double h3[(nb+1)];
   double h4[(nb+1)];

   x = (double *) calloc (sizeof(double), n);
   y = (double *) calloc (sizeof(double), n);
   g2_split(n, 0, points, x, y);

/*
 * First, store the values of the Hermite basis functions in a table h[ ]
 * so no time is wasted recalculating them
 */
   for (i = 0; i < (nb+1); i++) {
      t = (double) i / nb;
      h1[i] = ( 2.0 * t * t * t) - (3.0 * t * t) + 1.0;
      h2[i] = (-2.0 * t * t * t) + (3.0 * t * t);
      h3[i] = (       t * t * t) - (2.0 * t * t) + t;
      h4[i] = (       t * t * t) - (      t * t);
   }

/*
 * Set local tnFactor based on input parameter tn
 */
   if (tn <= 0.0) {
      tnFactor = 2.0;
      fprintf(stderr, "g2_c_raspln: Using Tension Factor 0.0: very rounded");
   }
   else if (tn >= 2.0) {
      tnFactor = 0.0;
      fprintf(stderr,
	      "g2_c_raspln: Using Tension Factor 2.0: not rounded at all");
   }
   else			tnFactor = 2.0 - tn;

/*
 * Do the first subinterval as a special case since no point precedes the
 * first point
 */
   tangentL1 =	((x[1] - x[0]) * (x[1] - x[0])) +
		((y[1] - y[0]) * (y[1] - y[0]));
   tangentL2 =	((x[2] - x[1]) * (x[2] - x[1])) +
		((y[2] - y[1]) * (y[2] - y[1]));
   if ((tangentL1 + tangentL2) == 0) bias = 0.5;
   else bias = tangentL2 / (tangentL1 + tangentL2);
   D1x = 0.0;
   D1y = 0.0;
   D2x = tnFactor * ((     bias  * (x[1] - x[0])) +
		     ((1 - bias) * (x[2] - x[1])));
   D2y = tnFactor * ((     bias  * (y[1] - y[0])) +
		     ((1 - bias) * (y[2] - y[1])));
   for (i = 0; i < nb; i++) {
      sxy[(i+i)]   = (h1[i] * x[0]) + (h2[i] * x[1]) +
		     (h3[i] * D1x) + (h4[i] * D2x);
      sxy[(i+i+1)] = (h1[i] * y[0]) + (h2[i] * y[1]) +
		     (h3[i] * D1y) + (h4[i] * D2y);
   free(x);
   free(y);
   }

/*
 * Do all general subintervals with preceding and following subintervals
 */
   for (j = 1; j < (n-2); j++) {
      tangentL1 = ((x[(j+1)] - x[j]) * (x[(j+1)] - x[j])) +
		  ((y[(j+1)] - y[j]) * (y[(j+1)] - y[j]));
      tangentL2 = ((x[(j+2)] - x[(j+1)]) * (x[(j+2)] - x[(j+1)])) +
		  ((y[(j+2)] - y[(j+1)]) * (y[(j+2)] - y[(j+1)]));
      if ((tangentL1 + tangentL2) == 0) bias = 0.5;
      else bias = tangentL2 / (tangentL1 + tangentL2);
      D1x = D2x;
      D1y = D2y;
      D2x = tnFactor * ((     bias  * (x[(j+1)] - x[j])) +
			((1 - bias) * (x[(j+2)] - x[(j+1)])));
      D2y = tnFactor * ((     bias  * (y[(j+1)] - y[j])) +
			((1 - bias) * (y[(j+2)] - y[(j+1)])));
      for (i = 0; i < nb; i++) {
	sxy[((j * 2 * nb) + i + i)] =
	   (h1[i] * x[j]) + (h2[i] * x[j+1]) +
	   (h3[i] * D1x) + (h4[i] * D2x);
	sxy[((j * 2 * nb) + i + i + 1)] =
	   (h1[i] * y[j]) + (h2[i] * y[j+1]) +
	   (h3[i] * D1y) + (h4[i] * D2y);
      }
   }

/*
 * Do the last subinterval as a special case since no point follows the
 * last point
 */
   D1x = D2x;
   D1y = D2y;
   D2x = 0.0;
   D2y = 0.0;
   for (i = 0; i < (nb+1); i++) {
      sxy[(((n-2) * 2 * nb) + i + i)] =
	(h1[i] * x[(n-2)]) + (h2[i] * x[(n-1)]) +
	(h3[i] * D1x) + (h4[i] * D2x);
      sxy[(((n-2) * 2 * nb) + i + i + 1)] =
	(h1[i] * y[(n-2)]) + (h2[i] * y[(n-1)]) +
	(h3[i] * D1y) + (h4[i] * D2y);
   }
}

void g2_raspln(int id, int n, double *points, double tn)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	tn			tension factor [0.0, 2.0]
 *				0.0  very rounded
 *				2.0  not rounded at all
 */

{
   double *sxy;		/*	coords of the entire spline curve */
   sxy = (double *) calloc (sizeof(double), (((n+n-2) * nb) + 2));

   g2_c_raspln(n, points, tn, sxy);
   g2_poly_line(id, (((n-1) * nb) + 1), sxy);

   free(sxy);
}

void g2_filled_raspln(int id, int n, double *points, double tn)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 *	tn			tension factor [0.0, 2.0]
 *				0.0  very rounded
 *				2.0  not rounded at all
 */

{
   double *sxy;		/*	coords of the entire spline curve */
   sxy = (double *) calloc (sizeof(double), (((n+n-2) * nb) + 4));

   g2_c_raspln(n, points, tn, sxy);
   sxy[(((n+n-2) * nb) + 2)] = points[(n+n-2)];
   sxy[(((n+n-2) * nb) + 3)] = points[1];
   g2_filled_polygon(id, (((n-1) * nb) + 2), sxy);

   free(sxy);
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
 *	Tijs Michels		M.H.M.Michels@kub.nl	Jun 16, 1999	C
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
/*
 * Maximum number of data points allowed
 * 21 would correspond to a polynomial of degree 20
 */

void g2_c_newton(int n, double *c1, double *c2, int o, double *xv, double *yv)
{
   int i, j;
   double p, s;
   double ddt[MaxPts][MaxPts];		/* Divided Difference Table */

   if (n < 4) {
      fprintf(stderr,
	      "g2_c_newton: Error! Less then 4 points passed"
	      "to function g2_c_newton\n");
      return;
   }

   if (n > MaxPts) {
      fprintf(stderr,
	      "g2_c_newton: Error! More then %d points passed"
	      "to function g2_c_newton\n",
	     MaxPts);
      return;
   }

/* First, build the divided difference table */

   for (i = 0; i < n; i++)	ddt[i][0] = c2[i];
   for (j = 1; j < n; j++) {
      for (i = 0; i < (n-j); i++)
	ddt[i][j] = (ddt[(i+1)][(j-1)] - ddt[i][(j-1)]) /
		    (c1[(i+j)] - c1[i]);
   }

/* Next, evaluate the polynomial at the specified points */

   for (i = 0; i < o; i++) {
      p = 1.0;
      s = ddt[0][0];
      for (j = 1; j < n; j++) {
	p = p * (xv[i] - c1[(j-1)]);
	s = s + (p * ddt[0][j]);
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
 *	Tijs Michels		M.H.M.Michels@kub.nl	Jun 17, 1999	C
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

/*
 * #undef  nb
 * #define nb 40
 * Number of straight connecting lines of which each polynomial consists.
 * So between one data point and the next, (nb-1) points are placed.
 */

void g2_c_para_3(int n, double *points, double *sxy)
{
#define dgr	(3+1)

   int i, j;
   double d2, step;
   double X[(nb + nb)];		/* x-coords of the current curve piece */
   double Y[(nb + nb)];		/* y-coords of the current curve piece */
   double t[dgr];		/* data point parameter values */
   double Xpts[dgr];		/* x-coords data point subsection */
   double Ypts[dgr];		/* y-coords data point subsection */
   double s[(nb + nb)];		/* parameter values at which to interpolate */

   /* Do first TWO subintervals first */

   g2_split(dgr, 0, points, Xpts, Ypts);

   t[0] = 0.0;
   for (i = 1; i < dgr; i++) {
      d2 = ((Xpts[i] - Xpts[(i-1)]) * (Xpts[i] - Xpts[(i-1)])) +
	   ((Ypts[i] - Ypts[(i-1)]) * (Ypts[i] - Ypts[(i-1)]));
      t[i] = t[(i-1)] + sqrt(d2);
   }

   step = t[2] / (nb + nb);
   for (i = 0; i < (nb + nb); i++)	s[i] = i * step;

   g2_c_newton(dgr, t, Xpts, (nb + nb), s, X);
   g2_c_newton(dgr, t, Ypts, (nb + nb), s, Y);
   for (i = 0; i < (nb + nb); i++) {
      sxy[(i+i)]   = X[i];
      sxy[(i+i+1)] = Y[i];
   }

   /* Next, do later central subintervals */

   for (j = 1; j < (n - dgr + 1); j++) {
      g2_split(dgr, j, points, Xpts, Ypts);

      for (i = 1; i < dgr; i++) {
	d2 = ((Xpts[i] - Xpts[(i-1)]) * (Xpts[i] - Xpts[(i-1)])) +
	     ((Ypts[i] - Ypts[(i-1)]) * (Ypts[i] - Ypts[(i-1)]));
	t[i] = t[(i-1)] + sqrt(d2);
      }

      step = (t[2] - t[1]) / nb;
      for (i = 0; i < nb; i++)	s[i] = (i * step) + t[1];

      g2_c_newton(dgr, t, Xpts, nb, s, X);
      g2_c_newton(dgr, t, Ypts, nb, s, Y);

      for (i = 0; i < nb; i++) {
	sxy[(((j + 1) * (nb + nb)) + i + i)]     = X[i];
	sxy[(((j + 1) * (nb + nb)) + i + i + 1)] = Y[i];
      }
   }

   /* Now do last subinterval */

   step = (t[3] - t[2]) / nb;
   for (i = 0; i < nb; i++)	s[i] = (i * step) + t[2];

   g2_c_newton(dgr, t, Xpts, nb, s, X);
   g2_c_newton(dgr, t, Ypts, nb, s, Y);

   for (i = 0; i < nb; i++) {
      sxy[(((n - dgr + 2) * (nb + nb)) + i + i)]     = X[i];
      sxy[(((n - dgr + 2) * (nb + nb)) + i + i + 1)] = Y[i];
   }
   sxy[(((n - 1) * (nb + nb)))]     = points[(n+n-2)];
   sxy[(((n - 1) * (nb + nb)) + 1)] = points[(n+n-1)];
}

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 */

void g2_para_3(int id, int n, double *points)
{
   double *sxy;		/*	coords of the entire spline curve */
   sxy = (double *) calloc (sizeof(double), (((n - 1) * (nb + nb)) + 2));

   g2_c_para_3(n, points, sxy);
   g2_poly_line(id, (((n - 1) * nb) + 1), sxy);

   free(sxy);
}

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 */

void g2_filled_para_3(int id, int n, double *points)
{
   double *sxy;		/*	coords of the entire spline curve */
   sxy = (double *) calloc (sizeof(double), (((n - 1) * (nb + nb)) + 4));

   g2_c_para_3(n, points, sxy);
   sxy[(((n - 1) * (nb + nb)) + 2)] = points[(n+n-2)];
   sxy[(((n - 1) * (nb + nb)) + 3)] = points[1];
   g2_filled_polygon(id, (((n - 1) * nb) + 2), sxy);

   free(sxy);
}

/*
 *	FUNCTION: g2_c_para_5
 *
 *	As g2_c_para_3, but now plot a polynomial of degree 5
 */

/*
 * #undef  nb
 * #define nb 40
 * Number of straight connecting lines of which each polynomial consists.
 * So between one data point and the next, (nb-1) points are placed.
 */

void g2_c_para_5(int n, double *points, double *sxy)
{
#undef	dgr
#define dgr	(5+1)

   int i, j;
   double d2, step;
   double X[(nb + nb + nb)];	/* x-coords of the current curve piece */
   double Y[(nb + nb + nb)];	/* y-coords of the current curve piece */
   double t[dgr];		/* data point parameter values */
   double Xpts[dgr];		/* x-coords data point subsection */
   double Ypts[dgr];		/* y-coords data point subsection */
   double s[(nb + nb + nb)];	/* parameter values at which to interpolate */

   /* Do first THREE subintervals first */

   g2_split(dgr, 0, points, Xpts, Ypts);

   t[0] = 0.0;
   for (i = 1; i < dgr; i++) {
      d2 = ((Xpts[i] - Xpts[(i-1)]) * (Xpts[i] - Xpts[(i-1)])) +
	   ((Ypts[i] - Ypts[(i-1)]) * (Ypts[i] - Ypts[(i-1)]));
      t[i] = t[(i-1)] + sqrt(d2);
   }

   step = t[3] / (nb + nb + nb);
   for (i = 0; i < (nb + nb + nb); i++)	s[i] = i * step;

   g2_c_newton(dgr, t, Xpts, (nb + nb + nb), s, X);
   g2_c_newton(dgr, t, Ypts, (nb + nb + nb), s, Y);
   for (i = 0; i < (nb + nb + nb); i++) {
      sxy[(i+i)]   = X[i];
      sxy[(i+i+1)] = Y[i];
   }

   /* Next, do later central subintervals */

   for (j = 1; j < (n - dgr + 1); j++) {
      g2_split(dgr, j, points, Xpts, Ypts);

      for (i = 1; i < dgr; i++) {
	d2 = ((Xpts[i] - Xpts[(i-1)]) * (Xpts[i] - Xpts[(i-1)])) +
	     ((Ypts[i] - Ypts[(i-1)]) * (Ypts[i] - Ypts[(i-1)]));
	t[i] = t[(i-1)] + sqrt(d2);
      }

      step = (t[3] - t[2]) / nb;
      for (i = 0; i < nb; i++)	s[i] = (i * step) + t[2];

      g2_c_newton(dgr, t, Xpts, nb, s, X);
      g2_c_newton(dgr, t, Ypts, nb, s, Y);

      for (i = 0; i < nb; i++) {
	sxy[(((j + 2) * (nb + nb)) + i + i)]     = X[i];
	sxy[(((j + 2) * (nb + nb)) + i + i + 1)] = Y[i];
      }
   }

   /* Now do last TWO subinterval */

   step = (t[5] - t[3]) / (nb + nb);
   for (i = 0; i < (nb + nb); i++)	s[i] = (i * step) + t[3];

   g2_c_newton(dgr, t, Xpts, (nb + nb), s, X);
   g2_c_newton(dgr, t, Ypts, (nb + nb), s, Y);

   for (i = 0; i < (nb + nb); i++) {
      sxy[(((n - dgr + 3) * (nb + nb)) + i + i)]     = X[i];
      sxy[(((n - dgr + 3) * (nb + nb)) + i + i + 1)] = Y[i];
   }
   sxy[(((n - 1) * (nb + nb)))]     = points[(n+n-2)];
   sxy[(((n - 1) * (nb + nb)) + 1)] = points[(n+n-1)];
}

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 */

void g2_para_5(int id, int n, double *points)
{
   double *sxy;		/*	coords of the entire spline curve */
   sxy = (double *) calloc (sizeof(double), (((n - 1) * (nb + nb)) + 2));

   g2_c_para_5(n, points, sxy);
   g2_poly_line(id, (((n - 1) * nb) + 1), sxy);

   free(sxy);
}

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	points			data points (x[i],y[i])
 */

void g2_filled_para_5(int id, int n, double *points)
{
   double *sxy;		/*	coords of the entire spline curve */
   sxy = (double *) calloc (sizeof(double), (((n - 1) * (nb + nb)) + 4));

   g2_c_para_5(n, points, sxy);
   sxy[(((n - 1) * (nb + nb)) + 2)] = points[(n+n-2)];
   sxy[(((n - 1) * (nb + nb)) + 3)] = points[1];
   g2_filled_polygon(id, (((n - 1) * nb) + 2), sxy);

   free(sxy);
}
