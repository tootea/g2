##############################################################################
##  Copyright (C) 2007  Dr. Tijs Michels
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
 'kl' : [2.25, 9.0],
 'sl' : [7.5, 12.5],
 'ds' : [6.25, 4.5] }

class Colors(list):
    def __init__(self):
        a_ = 0.0000
        b_ = 0.4528
        c_ = 0.6201
        d_ = 0.7634
        e_ = 0.8887
        f_ = 1.0000

        p_ = 0.1338
        q_ = 0.3574
        r_ = 0.5400

        u_ = 0.9459
        v_ = 0.8280
        w_ = 1.0000

        c1 = (a_, b_, c_, d_, e_, f_)
        c2 = (p_, q_, r_)
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
