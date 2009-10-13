##############################################################################
##  Copyright (C) 2004-2007  Dr. Tijs Michels
##  This file is part of the g2 library

##  Originally published on page 29 (the Netherlands) and page 139 (Tilburg)
##  of my dissertation (ISBN 90-9018145-8)

class PerMonth(tuple):
    def __new__(cls, *months):
        fract = sum(months) / 100.00
        return tuple.__new__(cls, (m / fract for m in months))
    def __init__(self, *months):
        self.total = sum(months)

tilburg97 = PerMonth( # total for 1997 : 954
     38,  43,  38, 62,
    132, 129, 101, 96,
    118,  86,  54, 57 )
tilburg97.max_interpol_val = 14.6472

nl94 = PerMonth(
    3076,  3296,  4983,
    6718, 10465, 11497,
    7880,  7973, 12284,
    6136,  4142,  4532 )
# CBS / Maandstatistiek bevolking 43(1995)10, 39.
nl94.max_interpol_val = 14.8309

nl95 = PerMonth(
    2947, 3121,  4514,
    5708, 9794, 12427,
    6825, 8630, 12108,
    6411, 4045,  4939 )
# CBS / Maandstatistiek bevolking 44(1996)11, 23.
nl95.max_interpol_val = 15.5327

nl96 = PerMonth(
    2900,  3367,  4580,
    5492, 11722, 11681,
    7745, 10288, 10928,
    6843,  4660,  4934 )
# CBS / Maandstatistiek bevolking 45(1997)9, 19.
nl96.max_interpol_val = 14.9934

nl97 = PerMonth(
    3075,  3428,  3974,
    6130, 11380, 11042,
    8560, 10010, 11025,
    7243,  4094,  5125 )
# CBS / Maandstatistiek bevolking 46(1998)9, 65.
nl97.max_interpol_val = 14.0957

nl98 = PerMonth(
    2688,  3456,  4497,
    6473, 11339, 11047,
    8932, 10141, 11740,
    7248,  4289,  5106 )
# CBS / Maandstatistiek bevolking 47(1999)9, 56.
nl98.max_interpol_val = 13.6750
