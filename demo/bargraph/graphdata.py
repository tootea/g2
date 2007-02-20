##############################################################################
##  Copyright (C) 2004-2007  Dr. Tijs Michels
##  This file is part of the g2 library

##  Originally published on page 29 of my dissertation (ISBN 90-9018145-8)

class PerMonth(tuple):
    def __new__(cls, *months):
        total = 0
        for m in months:
            total += m
        fract = total / 100.00
        return tuple.__new__(cls, [m /fract for m in months])
    def __init__(self, *months):
        self.total = 0
        for m in months:
            self.total += m

ninetyfour = PerMonth(
    3076,  3296,  4983,
    6718, 10465, 11497,
    7880,  7973, 12284,
    6136,  4142,  4532 )
# CBS / Maandstatistiek bevolking 43(1995)10, 39.
ninetyfour.max_interpol_val = 14.8309

ninetyfive = PerMonth(
    2947, 3121,  4514,
    5708, 9794, 12427,
    6825, 8630, 12108,
    6411, 4045,  4939 )
# CBS / Maandstatistiek bevolking 44(1996)11, 23.
ninetyfive.max_interpol_val = 15.5327

ninetysix = PerMonth(
    2900,  3367,  4580,
    5492, 11722, 11681,
    7745, 10288, 10928,
    6843,  4660,  4934 )
# CBS / Maandstatistiek bevolking 45(1997)9, 19.
ninetysix.max_interpol_val = 14.9934

ninetyseven = PerMonth(
    3075,  3428,  3974,
    6130, 11380, 11042,
    8560, 10010, 11025,
    7243,  4094,  5125 )
# CBS / Maandstatistiek bevolking 46(1998)9, 65.
ninetyseven.max_interpol_val = 14.0957

ninetyeight = PerMonth(
    2688,  3456,  4497,
    6473, 11339, 11047,
    8932, 10141, 11740,
    7248,  4289,  5106 )
# CBS / Maandstatistiek bevolking 47(1999)9, 56.
ninetyeight.max_interpol_val = 13.6750

data = {
  94 : ninetyfour,
  95 : ninetyfive,
  96 : ninetysix,
  97 : ninetyseven,
  98 : ninetyeight }
