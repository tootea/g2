##############################################################################
##  Copyright (C) 2007  Dr. Tijs Michels
##  This file is part of the g2 library

##  Simple script to draw my default palette in either a window or a file

from g2 import *
import sys

def loadPalette():
    import graphsettings
    colors = graphsettings.Colors()
    graph.g2_clear_palette()
    for c in colors:
        graph.g2_ink(*c)

def drawPalette():
    graph.g2_set_font_size(12)
    c = 0
    for y in xrange(14):
        dh = y*24
        for x in xrange(18):
            dw = x*26
            graph.g2_pen(c)
            graph.g2_filled_rectangle(10+dw, 324-dh, 36+dw, 348-dh)
            graph.g2_pen(0) # alternatively, draw the strings in a separate loop, to switch to a black pen just once, instead of 252 times
            graph.g2_string(14+dw, 340-dh, str(c))
            c += 1

output = 'w' # by default, output to window only
graph = None
progName = sys.argv.pop(0)
while sys.argv:
    arg = sys.argv.pop(0)
    if arg == '-f': # output to file (landscape PostScript)
        output = 'f'
        graph = g2_open_PS("palette.ps", g2_A4, g2_PS_land)
        graph.g2_set_coordinate_system(0, 0, 1.725, 1.65)
    else:
        if arg != '-h':
            print "\n Argument '%s' is invalid." % arg
        print '\n %s <-f> <-h>\n\n' \
              '   -f : output to file (landscape PostScript)\n' \
              '   -h : show this help\n\n' \
              ' If no (valid) output device is specified, the screen is chosen.\n\n' % progName
        sys.exit(0)

if graph is None: # no device was specified on the command line, or the device specified could not be opened
    if hasattr(globals(), 'g2_open_win32'):
        graph = g2_open_win32(976, 720, 'palette', g2_win32)
    else:
        graph = g2_open_X11(976, 720)
    if graph is None:
        print '\n Could not open any device.\n'
        sys.exit(0)
    graph.g2_set_coordinate_system(0, 0, 2, 2)

graph.g2_set_auto_flush(False)
loadPalette()
drawPalette()
graph.g2_flush()

if output != 'f':
    print '\n Done.' \
          '\n Hit any key to continue.\n'
    sys.stdin.read(1)
