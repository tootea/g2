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
    def __new__(cls):
        import math
        return tuple.__new__(cls, (math.log(a) for a in frange(1,math.e,13)))

class Colors(list):
    def __init__(self):
        steps = ColorSteps()

        c1 = (0.,) + steps[4:12:2] + (1.,)
        c2 = steps[1:7:2]

        u_, v_, w_, = steps[11], steps[9], 1.

        c3 = (((u_, v_, v_), (u_, v_, w_), (u_, w_, w_)),
              ((v_, u_, v_), (v_, u_, w_), (w_, u_, w_)),
              ((v_, v_, u_), (v_, w_, u_), (w_, w_, u_)))

        for r in c1:
            for g in c1:
                for b in c1:
                    self.append((r, g, b))

        for r, l in zip(c2, c3):
            for g in c2:
                for b in c2:
                    self.append((r, g, b))
            for a in l:
                self.append(a)

black_   = 0
blue_    = 5
green_   = 30
cyan_    = 35
red_     = 180
yellow_  = 185
magenta_ = 210
white_   = 215
