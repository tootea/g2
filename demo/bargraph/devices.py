##############################################################################
##  Copyright (C) 2007  Dr. Tijs Michels
##  This file is part of the g2 library

import g2
from g2 import *
import graphsettings

class PhysicalDevices(dict):
    def __init__(self):
        colors = graphsettings.Colors()
        print
        print '',
        if hasattr(g2, 'g2_open_PS'):
            print '..PS ..EPSF ..EPSF_CLIP',
            self['ps']   = g2_open_PS('graph.ps', g2_A4, g2_PS_land)
            self['eps']  = g2_open_EPSF('graph.eps')
            self['epsc'] = g2_open_EPSF_CLIP('graph_clip.eps', 200, 200)
        if hasattr(g2, 'g2_open_FIG'):
            print '..FIG',
            self['fig']  = g2_open_FIG('graph.fig')
        if hasattr(g2, 'g2_open_X11') and not hasattr(g2, 'g2_open_win32'):
            print '..X11',
            self['X']    = g2_open_X11(775, 575)
        if hasattr(g2, 'g2_open_gd'):
            print '..GD(png) ..GD(jpeg)',
            self['png']  = g2_open_gd('graph.png', 775, 575, g2_gd_png)
            self['jpeg'] = g2_open_gd('graph.jpg', 775, 575, g2_gd_jpeg)
        if hasattr(g2, 'g2_open_win32'):
            print '..WIN32 ..WMF32'
            self['msw']  = g2_open_win32(775, 575, 'graph',     g2_win32)
            self['wmf']  = g2_open_win32(775, 575, 'graph.emf', g2_wmf32)
        print

        # delete devices that could not be opened (returned NULL), if any
        for d in [k for k, v in self.iteritems() if v is None]:
            del self[d]

        # give each physical device my very own palette
        for d in self.values():
            d.g2_clear_palette()
            for r, g, b in colors:
                d.g2_ink(r, g, b)

class AllAtOnce(G2):
    def __init__(self):
        self.physicalDevices = PhysicalDevices()
        for d in self.physicalDevices.values():
            self.g2_attach(d)
