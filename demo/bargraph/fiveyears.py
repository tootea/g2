##############################################################################
##  Copyright (C) 2009  Dr. Tijs Michels
##  This file is part of the g2 library

##  Graphs 2.14 and 2.15 on page 29 of my dissertation (ISBN 90-9018145-8)

from g2 import *
import graphdata
import graphsettings
from dimensions import *

baseyear = 64 # 94

graph = g2_open_EPSF('permonth_%d-%d.eps' % (baseyear, baseyear + 4))
graph.g2_set_auto_flush(False)

graph.g2_clear_palette()
for c in graphsettings.Colors():
    graph.g2_ink(*c)

months = [];
max_y = 0.;
for year in range(baseyear, baseyear + 5):
    yeardata = graphdata.__dict__["nl%d" % year]
    max_y = max(max_y, yeardata.max_interpol_val)
    months.extend(yeardata)

step_x /= 5
step_y = max_gr_h / max_y
xStep = lambda factor: min_gr_x + factor * step_x
yStep = lambda factor: min_gr_y + factor * step_y

mndl = []
graph.g2_set_line_width(0) # add no width, depth or height to the bars
for i, month in enumerate(months):
    graph.g2_pen(1+3*i)
    graph.g2_filled_rectangle(xStep(i), min_gr_y, xStep(i+1), yStep(month))

    mndl.append(xStep(i+.5))
    mndl.append(yStep(month))

graph.g2_pen(0)
graph.g2_set_line_width(graphsettings.thin_line)
graph.g2_rectangle(*frame)

graph.g2_set_font_size(x_font_size)

points_per_cycle = 12
step_x *= points_per_cycle
for i in range(5):
    graph.g2_string(xStep(i+.5)+0.5-(x_font_size/2.), min_y, str(baseyear+i))
    graph.g2_line(xStep(i), min_gr_y-x_scale_marker_length,
                  xStep(i), min_gr_y)
end_x = max_x-graphsettings.thin_line*.5;
graph.g2_line(end_x, min_gr_y-x_scale_marker_length, end_x, min_gr_y)
graph.g2_poly_line((min_gr_x, yStep(max_y), min_gr_x, min_gr_y, max_x, min_gr_y))

y_scale_step = 2 + (baseyear == 64)
for i in xrange(y_scale_step, int(max_y)+1, y_scale_step):
    graph.g2_string(min_x, yStep(i)-(y_font_size/4.), '1%d%%' % (i % 10))
    graph.g2_line(min_gr_x-scale_marker_length, yStep(i),
                                      min_gr_x, yStep(i))
graph.g2_pen(graphsettings.white_)
graph.g2_filled_rectangle(min_x, yStep(1.6),
                       12+min_x, yStep(9.6))
graph.g2_pen(0)
graph.g2_set_dash(graphsettings.LineDashes['kl'])
graph.g2_set_line_width(graphsettings.LineThickness['lix'])
for i in xrange(1, int(max_y)+1):
    graph.g2_line(min_gr_x, yStep(i),
                     max_x, yStep(i))
graph.g2_set_solid()
graph.g2_set_line_width(graphsettings.firm_line)
g2_splines_set_points_per_cycle(points_per_cycle)
graph.g2_spline(mndl, -20) # negative, for a cyclic spline
graph.g2_pen(86)
graph.g2_set_font_size(y_font_size*.525)
graph.g2_string(xStep(4.26), yStep(0.225), '(c) Tijs Michels')

graph.g2_flush()
