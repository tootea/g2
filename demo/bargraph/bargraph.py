##############################################################################
##  Copyright (C) 2007-2009  Dr. Tijs Michels
##  This file is part of the g2 library

##  Based on graph 2.17 (4.2) on page 29 (139) of my dissertation (ISBN 90-9018145-8)

from g2 import *
import os
import sys
import graphdata
import graphsettings
from dimensions import *

def bars():
    graph.g2_set_line_width(0) # add no width, depth or height to the bars
    for i, month in enumerate(months):
        graph.g2_pen(4+step_c*i)
        graph.g2_filled_rectangle(xStep(i), min_gr_y, xStep(i+1), yStep(month))

def interp():
    mndl = []

    for i, month in enumerate(months):
        mndl.append(xStep(i+.5))
        mndl.append(yStep(month))

    graph.g2_set_line_width(graphsettings.bold_line)

    if g2legend is None:
        graph.g2_spline(mndl, -44) # negative, for a cyclic spline
        return

    ty = yStep(legendTopLine - 1)
    legend_line = lambda: graph.g2_line(xOff(2), ty, xOff(5), ty)

    graph.g2_pen(162) # 168
    graph.g2_b_spline(mndl, -44) # negative, for a cyclic spline
    legend_line()

    ty += step_y
    graph.g2_pen(186)
    graph.g2_spline(mndl, -44) # negative, for a cyclic spline
    legend_line()

    ty -= step_y * 2
    graph.g2_pen(72)
    graph.g2_set_dash(graphsettings.LineDashes['ds'])
    legend_line()
    # as this is a fairly dark line, make it a little less bold,
    # so it won't stand out too much (not visible on all devices)
    graph.g2_set_line_width(graphsettings.firm_line)
    graph.g2_hermite(mndl, .7, -44) # negative, for a cyclic spline
    graph.g2_set_solid()

def scales():
    graph.g2_set_font_size(x_font_size)
    for i, mname in enumerate(('jan', 'feb', 'mar', 'apr', 'may', 'jun',
                               'jul', 'aug', 'sep', 'oct', 'nov', 'dec')):
        graph.g2_string(xStep(i), min_y, mname)
        graph.g2_line(xStep(i), min_gr_y-x_scale_marker_length,
                      xStep(i), min_gr_y)
    end_x = max_x-graphsettings.thin_line * .5;
    graph.g2_line(end_x, min_gr_y-x_scale_marker_length, end_x, min_gr_y)
    graph.g2_line(min_gr_x, min_gr_y, max_x, min_gr_y)
    graph.g2_line(min_gr_x, min_gr_y, min_gr_x, max_y)

    graph.g2_set_font_size(y_font_size)
    for i in xrange(2, int(months.max_interpol_val)+1, 2):
        graph.g2_string(min_x, yStep(i)-(y_font_size/4.), '1%d%%' % (i % 10))
        graph.g2_line(min_gr_x-scale_marker_length, yStep(i),
                                          min_gr_x, yStep(i))
    graph.g2_pen(graphsettings.white_)
    graph.g2_filled_rectangle(min_x, yStep(2)-(y_font_size/3.),
                           12+min_x, yStep(9)-(y_font_size/2.))
    graph.g2_pen(0)
    graph.g2_set_dash(graphsettings.LineDashes['kl'])
    for i in xrange(1, int(months.max_interpol_val)+1):
        graph.g2_line(min_gr_x, yStep(i),
                         max_x, yStep(i))
    graph.g2_set_solid()

def legend():
    yfs = y_font_size * .7
    ty = yStep(legendTopLine)-(yfs/4.)

    graph.g2_pen(86)
    graph.g2_set_font_size(.75*yfs)
    if g2legend:
        graph.g2_string(xOff(6), ty-3*step_y, 'tijs@users.sourceforge.net')
    else:
        graph.g2_string(xStep(10.225), yStep(0.225), '(c) Tijs Michels')
        if g2legend is None: return

    graph.g2_pen(0)
    graph.g2_set_font_size(yfs)
    if g2legend:
        graph.g2_set_line_width(graphsettings.LineThickness['lxix'])
        graph.g2_string(xOff(6), ty, 'g2')
        graph.g2_line(xOff(9.4), ty,
                     xOff(10.4), ty)
        graph.g2_string(xOff(10.6), ty, 'spline')
    elif dataset == 'nl':
        graph.g2_string(xOff(6), ty+0.175*step_y, 'successive')
        graph.g2_string(xOff(10.35), ty-0.225*step_y, 'over-relaxation')
    else:
        graph.g2_string(xOff(6), ty, 'successive over-relaxation')
    ty -= step_y
    if g2legend:
        graph.g2_string(xOff(6), ty, 'g2')
        graph.g2_line(xOff(9.4), ty,
                     xOff(10.4), ty)
        graph.g2_string(xOff(10.5), ty, 'b')
        graph.g2_line(xOff(12.3), ty,
                      xOff(13.3), ty)
        graph.g2_string(xOff(13.5), ty, 'spline')
    else:
        graph.g2_string(xOff(6), ty, 'cubic B-spline')
    ty -= step_y
    if g2legend:
        graph.g2_string(xOff(6), ty, 'g2')
        graph.g2_line(xOff(9.4), ty,
                     xOff(10.4), ty)
        graph.g2_string(xOff(10.6), ty, 'hermite')
    else:
        graph.g2_string(xOff(6), ty, 'cubic Hermite')

def draw():
    global months, step_y
    months = graphdata.__dict__[dataset + str(year)]
    step_y = max_gr_h / months.max_interpol_val
    os.putenv("G2_SPLINES_VERBOSE", "%g %g" % (min_gr_y, step_y)) # comment this out to have no statistics printed to stdout
    bars()
    graph.g2_pen(0)
    graph.g2_set_line_width(graphsettings.thin_line)
    graph.g2_rectangle(*frame)
    scales()
    interp()
    legend()

xOff = lambda factor: min_gr_x + factor * scale_marker_length
xStep = lambda factor: min_gr_x + factor * step_x
yStep = lambda factor: min_gr_y + factor * step_y

g2legend = True
dataset = 'nl' # use option -d to plot a different data set
year = 97 # use option -y to plot a different year
sys.argv.pop(0)
while sys.argv:
    arg = sys.argv.pop(0)
    if   arg == '-f': # output to EPS file
        output = 'f'
        graph = g2_open_EPSF('bargraph.eps')
    elif arg == '-a': # output to all available devices
        output = 'a'
        import devices
        graph = devices.AllAtOnce()
    elif arg == '-d': # followed by a data set ('nl' or 'tilburg')
        try:
            dataset = sys.argv.pop(0)
        except IndexError:
            print '\n Error : no data set specified\n'
            sys.exit(0)
    elif arg == '-y': # followed by a year
        try:
            year = int(sys.argv.pop(0))
        except IndexError:
            print '\n Error : no year specified\n'
        except ValueError:
            print '\n Error : year must be an integer\n'
        else:
            if 64 <= year <= 68 or 94 <= year <= 98:
                continue # perfect
            print '\n Error : year must be between 64 and 68 or 94 and 98.\n'
        sys.exit(0)
    elif arg == '-m': # math legend
        g2legend = False
    elif arg == '-s': # single spline, therefore no legend needed
        g2legend = None
    else:
        if arg != '-h':
            print "\n Argument '%s' is invalid." % arg
        print '\n bargraph.py <[-f | -a]> <-d nl|tilburg> <-y xx> <-m> <-s> <-h>\n\n' \
              '   -f : output to EPS file\n' \
              '   -a : output to all available devices\n' \
              '   -d : select a data set: nl (default) or tilburg\n' \
              '   -y : plot the year xx (default is 97)\n' \
              '   -m : print alternative math legend\n' \
              '   -s : single spline mode: no legend, as none is needed\n' \
              '   -h : show this help\n\n' \
              ' If no output device is specified, the screen is chosen.\n' \
              ' If no year is specified, 1997 is plotted.\n\n'
        sys.exit(0)

if not locals().has_key('graph'): # no device was specified on the command line, or the device specified could not be opened
    if locals().has_key('g2_open_X11'):
        graph = g2_open_X11(x_width, x_height)
    else:
        graph = g2_open_win32(x_width, x_height, 'g2_test', g2_win32)
    if graph is None:
        print '\n Could not open any device.\n'
        sys.exit(0)
    graph.g2_set_coordinate_system(0, 0, x11_scale_factor, x11_scale_factor)
    x_font_size *= x11_scale_factor
    y_font_size *= x11_scale_factor
    output = 'w'

if g2legend or dataset == 'nl':
    legendTopLine = 13.5
else:
    legendTopLine = 14.375

if output != 'a':
    graph.g2_clear_palette()
    for c in graphsettings.Colors():
        graph.g2_ink(*c)
    graph.g2_set_background(graphsettings.white_)

graph.g2_set_auto_flush(False)
draw()
graph.g2_flush()

print '\n Total for 19%d : %d.' % (year, months.total)

if output != 'f':
    print '\n Done.' \
          '\n Hit [Enter] to continue.\n'
    sys.stdin.read(1)
