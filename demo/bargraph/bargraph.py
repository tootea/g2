##############################################################################
##  Copyright (C) 2007  Dr. Tijs Michels
##  This file is part of the g2 library

from g2 import *
import sys
import graphdata
import graphsettings
from dimensions import *

def bars():
    for i, month in enumerate(months):
        graph.g2_pen(4+step_c*i)
        graph.g2_filled_rectangle(min_gr_x+step_x*i, min_gr_y,
                           step_x+min_gr_x+step_x*i, min_gr_y+month*step_y)
    graph.g2_pen(0)

def interp():
    mndl = []

    for i, month in enumerate(months):
        mndl.append(min_gr_x+st_h_x+step_x*i)
        mndl.append(min_gr_y+step_y*month)

    graph.g2_set_line_width(graphsettings.bold_line)

    graph.g2_pen(162) # 168
    graph.g2_b_spline(mndl, -40) # negative, for a cyclic spline
    graph.g2_line(min_gr_x+2*scale_marker_length, min_gr_y+step_y*13.5,
                  min_gr_x+5*scale_marker_length, min_gr_y+step_y*13.5)

    graph.g2_pen(186)
    graph.g2_spline(mndl, -40) # negative, for a cyclic spline
    graph.g2_line(min_gr_x+2*scale_marker_length, min_gr_y+step_y*12.5,
                  min_gr_x+5*scale_marker_length, min_gr_y+step_y*12.5)

    graph.g2_pen(72)
    graph.g2_set_dash(graphsettings.LineDashes['ds'])
    graph.g2_line(min_gr_x+2*scale_marker_length, min_gr_y+step_y*11.5,
                  min_gr_x+5*scale_marker_length, min_gr_y+step_y*11.5)
    # as this is a fairly dark line, make it a little less bold,
    # so it won't stand out too much (not visible on all devices)
    graph.g2_set_line_width(graphsettings.firm_line)
    graph.g2_hermite(mndl, .7, -20) # negative, for a cyclic spline
    graph.g2_pen(0)
    graph.g2_set_solid()
    graph.g2_set_line_width(graphsettings.thin_line)

def x_scale():
    mnames = (
        'jan', 'feb', 'mar', 'apr',
        'may', 'jun', 'jul', 'aug',
        'sep', 'oct', 'nov', 'dec')
    if output == 'w':
        graph.g2_set_font_size(x_font_size*x11_scale_factor)
    else:
        graph.g2_set_font_size(x_font_size)
    for i, mname in enumerate(mnames):
        graph.g2_string(min_gr_x+step_x*i, min_y, mname)
        graph.g2_line(min_gr_x+step_x*i, min_gr_y-scale_marker_length*fr_pr,
                      min_gr_x+step_x*i, min_gr_y)
    graph.g2_line(max_x, min_gr_y-scale_marker_length*fr_pr, max_x, min_gr_y)
    graph.g2_line(min_gr_x, min_gr_y, max_x, min_gr_y)

def y_scale():
    for i in range(2, 10, 2):
        graph.g2_string(min_x, min_gr_y-(y_font_size/4.)+step_y*i, '1%d%%' % i)
        graph.g2_line(min_gr_x-scale_marker_length, min_gr_y+step_y*i,
                                          min_gr_x, min_gr_y+step_y*i)
    graph.g2_pen(graphsettings.white_)
    graph.g2_filled_rectangle(min_x, min_gr_y-(y_font_size/3.)+step_y*2,
                          min_x+12, min_gr_y-(y_font_size/1.5)+step_y*9)
    graph.g2_pen(0)
    for i in range(10, int(months.max_interpol_val)+1, 2):
        graph.g2_string(min_x, min_gr_y-(y_font_size/4.)+step_y*i, '%d%%' % i)
        graph.g2_line(min_gr_x-scale_marker_length, min_gr_y+step_y*i,
                                          min_gr_x, min_gr_y+step_y*i)
    graph.g2_line(min_gr_x, min_gr_y, min_gr_x, max_y)
    graph.g2_set_dash(graphsettings.LineDashes['kl'])
    for i in range(1, int(months.max_interpol_val)+1):
        graph.g2_line(min_gr_x, min_gr_y+step_y*i,
                         max_x, min_gr_y+step_y*i)

def legend():
    yfs = y_font_size * .7
    graph.g2_set_line_width(.7*graphsettings.thin_line)
    if output == 'w': yfs *= x11_scale_factor
    ty = min_gr_y-(yfs/4.)+step_y*13.5
    graph.g2_set_solid()
    graph.g2_set_font_size(yfs)
    graph.g2_string(min_gr_x+6*scale_marker_length, ty, 'g2')
    graph.g2_line(min_gr_x+9.4*scale_marker_length, ty,
                 min_gr_x+10.4*scale_marker_length, ty)
    graph.g2_string(min_gr_x+10.5*scale_marker_length, ty, 'b')
    graph.g2_line(min_gr_x+12.3*scale_marker_length, ty,
                  min_gr_x+13.3*scale_marker_length, ty)
    graph.g2_string(min_gr_x+13.5*scale_marker_length, ty, 'spline')
    ty -= step_y
    graph.g2_string(min_gr_x+6*scale_marker_length, ty, 'g2')
    graph.g2_line(min_gr_x+9.4*scale_marker_length, ty,
                 min_gr_x+10.4*scale_marker_length, ty)
    graph.g2_string(min_gr_x+10.6*scale_marker_length, ty, 'spline')
    ty -= step_y
    graph.g2_string(min_gr_x+6*scale_marker_length, ty, 'g2')
    graph.g2_line(min_gr_x+9.4*scale_marker_length, ty,
                 min_gr_x+10.4*scale_marker_length, ty)
    graph.g2_string(min_gr_x+10.6*scale_marker_length, ty, 'hermite')
    ty -= step_y
    graph.g2_set_font_size(.75*yfs)
    graph.g2_pen(86)
    graph.g2_string(min_gr_x+6*scale_marker_length, ty, 'tijs@users.sourceforge.net')

def draw():
    graph.g2_set_line_width(graphsettings.thin_line)
    graph.g2_rectangle(fr_margin, fr_margin, fr_right, fr_top)
    global months, step_y
    months = graphdata.data[year]
    step_y = max_gr_h / months.max_interpol_val
    bars()
    interp()
    x_scale()
    y_scale()
    legend()

output = 'w' # by default, output to window only
graph = None
year = 97 # use option -y to plot a different year
sys.argv.pop(0)
while sys.argv:
    arg = sys.argv.pop(0)
    if   arg == '-f': # output to file
        output = 'f'
        graph = g2_open_EPSF('bargraph.eps')
    elif arg == '-a': # output to all available devices
        output = 'a'
        import devices
        graph = devices.AllAtOnce()
    elif arg == '-y': # a year has been specified
        try:
            year = int(sys.argv.pop(0))
        except IndexError:
            print '\n Error : no year specified\n'
        except ValueError:
            print '\n Error : year must be an integer\n'
        else:
            if 94 <= year <= 98:
                continue # perfect
            print '\n Error : year must be between 94 and 98.\n'
        sys.exit(0)
    else:
        if arg != '-h':
            print "\n Argument '%s' is invalid." % arg
        print '\n bargraph.py <[-f | -a]> <-y 9x> <-h>\n\n' \
              '   -f : output to file\n' \
              '   -a : output to all available devices\n' \
              '   -y : show the year 9x (default is 97)\n' \
              '   -h : show this help\n\n' \
              ' If no (valid) output device is specified, the screen is chosen.\n' \
              ' If no (valid) year is specified, 1997 is shown.\n\n'
        sys.exit(0)

if graph is None: # no device was specified on the command line, or the device specified could not be opened
    if hasattr(globals(), 'g2_open_win32'):
        graph = g2_open_win32(x_width, x_height, 'g2_test', g2_win32)
    else:
        graph = g2_open_X11(x_width, x_height)
    if graph is None:
        print '\n Could not open any device.\n'
        sys.exit(0)
    graph.g2_set_coordinate_system(0, 0, x11_scale_factor, x11_scale_factor)

if output != 'a':
    colors = graphsettings.Colors()
    graph.g2_clear_palette()
    for r, g, b in colors:
        graph.g2_ink(r, g, b)
    graph.g2_set_background(graphsettings.white_)

print '\n Plotting year 19%d' % year

graph.g2_set_auto_flush(False)
draw()
graph.g2_flush()

if output != 'f':
    print '\n Done.' \
          '\n Hit any key to continue.\n'
    sys.stdin.read(1)
