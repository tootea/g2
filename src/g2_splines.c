/*
 * g2_splines.c
 * 06/01/99
 */

#include <math.h>
#include <stdlib.h>

#include "g2.h"

#define eps 1.0e-12


void g2_c_spline(int n, double *x, double *y, int m, double *sxy);
void g2_c_b_spline(int n, double *x, double *y, int m, double *sxy);



void g2_c_spline(int n, double *x, double *y,
		 int m, double *sxy)

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
 *	x, y			data points (x[i],y[i])
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
 *	Tijs Michels	06/01/99	<M.H.M.Michels@kub.nl>
 */

{
    int i, j;
    double *g;
    double p, w, k, u, delta_g;

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

	for (i = 1; i < (n-1); i++)
	    {
	    p = .5 * (x[i] - x[(i-1)]) / (x[(i+1)] - x[(i-1)]);
	    delta_g = w * (-*(g+i) - (p * *(g+i-1)) -
			      ((.5 - p) * *(g+i+1)) + *(g+n+i));
	    *(g+i) = *(g+i) + delta_g;

	    if (fabs(delta_g) > u)	u = fabs(delta_g);
	    }	/* On loop termination u holds the largest delta_g. */

	if (k == 0)
	    k = (u * eps);	/* Only executed once, at the end of pass one.
				 * So k preserves the largest delta_g of pass
				 * one multiplied by eps.
				 */
	}
    while (u > k);

    for (j = 0; j < m; j++)
	{
	i = 1;

	while (x[i] < sxy[(j+j)])
	    i++;

	i--;

	if (i >= n)
	    i = (n-1);

	sxy[((j+j)+1)] = (y[i] +
		((sxy[(j+j)] - x[i]) * (y[(i+1)] - y[i]) / (x[(i+1)] - x[i])) +
		((sxy[(j+j)] - x[i]) * (sxy[(j+j)] - x[(i+1)]) *
		 ((2. * *(g+i)) + *(g+i+1) +
		  ((sxy[(j+j)] - x[i]) * (*(g+i+1) - *(g+i)) /
		   (x[(i+1)] - x[i])))
		 / 6.));
	}

    free (g);
}

void g2_spline(int id, int n, double *x, double *y, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	x, y			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
    int m = (((n-1)*o)+1);
    double sxy[(m+m)];

    g2_c_spline(n, x, y, m, sxy);
    g2_poly_line(id, m, sxy);
}

void g2_filled_spline(int id, int n, double *x, double *y, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	x, y			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
    int m = (((n-1)*o)+1);
    double sxy[(m+m+2)];

    g2_c_spline(n, x, y, m, sxy);
    sxy[(m+m)] = x[(n-1)];
    sxy[(m+m+1)] = y[0];
    g2_filled_polygon(id, (m+1), sxy);
}

void g2_c_b_spline(int n, double *x, double *y,
		   int m, double *sxy)

/*
 * g2_c_b_spline takes n input points. It uses parameter t
 * to compute sx(t) and sy(t) respectively
 */

{
    int i, j;
    double t, bl1, bl2, bl3, bl4;
    double interval, xi_3, yi_3, xi, yi;

    interval = (double)(n-1) / (double)(m-1);

    for (i = 2, j = 0; i <= n; i++)
	{
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

	while (t < 1.0 && j < (m-1))
	    {
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
}

void g2_b_spline(int id, int n, double *x, double *y, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	x, y			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
    int m = (((n-1)*o)+1);
    double sxy[(m+m)];

    g2_c_b_spline(n, x, y, m, sxy);
    g2_poly_line(id, m, sxy);
}

void g2_filled_b_spline(int id, int n, double *x, double *y, int o)

/*
 *	FORMAL ARGUMENTS:
 *
 *	id			device id
 *	n			number of data points
 *	x, y			data points (x[i],y[i])
 *	o			number of interpolated points per data point
 */

{
    int m = (((n-1)*o)+1);
    double sxy[(m+m+2)];

    g2_c_b_spline(n, x, y, m, sxy);
    sxy[(m+m)] = x[(n-1)];
    sxy[(m+m+1)] = y[0];
    g2_filled_polygon(id, (m+1), sxy);
}
