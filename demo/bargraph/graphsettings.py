##############################################################################
##  Copyright (C) 2007-2009  Dr. Tijs Michels
##  This file is part of the g2 library

##  Note that these are just my personal preferences

LineThickness = {
 'il'     : 1.38,
 'lix'    : 1.15,
 'lxiv'   : 1.06,
 'lxix'   : 0.98,
 'lxxvii' : 0.88 }

thin_line = LineThickness['il']
firm_line = 2.0 * thin_line
bold_line = 2.5 * thin_line

LineDashes = {
 'ps' : [1.5,  7.5],
 'pl' : [1.5,  9.0],
 'kl' : [2.4, 9.12],
 'sl' : [7.5, 12.5],
 'ds' : [6.12, 4.76] }

def frange(from_, to_, n):
    m = n - 1
    q = 1.0 / m
    return (q * (from_ * (m - i) + to_ * i) for i in range(n)) # generator

class ColorSteps(tuple):
    def __new__(cls, n): # a succession of n intensities (0.0, ..., 1.0)
        import math
        return tuple.__new__(cls, (math.log(a) for a in frange(1, math.e, n)))

class Colors(list):
    def allTriplets(self, values):
        for r in values:
            for g in values:
                for b in values:
                    self.append((r, g, b)) # 27, 64, 125, 216, etc. colors

    def __init__(self, n = 0):
        if n != 0:
            self.allTriplets(ColorSteps(n < 3 and 3 or n))
            return

        # the compact yet fairly complete default palette
        steps = ColorSteps(13)

        self.allTriplets((0.,) + steps[4:13:2]) # 6 * 6 * 6 colors

        c2 = steps[1:7:2]

        u_, v_, w_, = steps[11], steps[9], 1.

        c3 = (((u_, v_, v_), (u_, v_, w_), (u_, w_, w_)),
              ((v_, u_, v_), (v_, u_, w_), (w_, u_, w_)),
              ((v_, v_, u_), (v_, w_, u_), (w_, w_, u_)))

        for r, l in zip(c2, c3):
            for g in c2:
                for b in c2:
                    self.append((r, g, b)) # 3 * 3 * 3 colors
            for a in l:
                self.append(a) # 3 * 3 colors

black_   = 0
blue_    = 5
green_   = 30
cyan_    = 35
red_     = 180
yellow_  = 185
magenta_ = 210
white_   = 215
