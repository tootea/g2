##############################################################################
##  Copyright (C) 2007  Dr. Tijs Michels
##  This file is part of the g2 library

import g2
from g2 import *
import graphsettings
import dimensions

width = int(dimensions.total_width)
height = int(dimensions.total_height)

class PhysicalDevices(dict):
    def __init__(self):
        print
        print '',
        if hasattr(g2, 'g2_open_PS'):
            print '..PS ..EPSF ..EPSF_CLIP',
            self['ps']   = g2_open_PS('graph.ps', g2_A4, g2_PS_land)
            self['eps']  = g2_open_EPSF('graph.eps')
            self['epsc'] = g2_open_EPSF_CLIP('graph_clip.eps', width, height)
        if hasattr(g2, 'g2_open_FIG'):
            print '..FIG',
            self['fig']  = g2_open_FIG('graph.fig')
        if hasattr(g2, 'g2_open_X11') and not hasattr(g2, 'g2_open_win32'):
            print '..X11',
            self['X']    = g2_open_X11(width, height)
        if hasattr(g2, 'g2_open_gd'):
            print '..GD(png) ..GD(jpeg)',
            self['png']  = g2_open_gd('graph.png', width, height, g2_gd_png)
            self['jpeg'] = g2_open_gd('graph.jpg', width, height, g2_gd_jpeg)
        if hasattr(g2, 'g2_open_win32'):
            print '..WIN32 ..WMF32'
            self['msw']  = g2_open_win32(width, height, 'graph', g2_win32)
            self['wmf']  = g2_open_win32(width, height, 'graph.emf', g2_wmf32)
        print

        # delete devices that could not be opened (returned NULL), if any
        for d in (k for k, v in self.iteritems() if v is None):
            del self[d]

        # give each physical device my very own palette
        colors = graphsettings.Colors()
        for d in self.values():
            d.g2_clear_palette()
            for c in colors:
                d.g2_ink(*c)
            d.g2_set_background(graphsettings.white_)

class AllAtOnce(G2):
    def __init__(self):
        self.physicalDevices = PhysicalDevices()
        for d in self.physicalDevices.values():
            self.g2_attach(d)

        # g2_set_background doesn't work with GD,
        # so simply draw a white rectangle over the entire background
        d.g2_pen(graphsettings.white_)
        for k, d in self.physicalDevices.iteritems():
            if k in ('png', 'jpeg'):
                d.g2_filled_rectangle(0, 0, width, height)
            elif k is 'ps':
                d.g2_set_coordinate_system((842 - width ) / 2,
                                           (595 - height) / 2, 1, 1)
