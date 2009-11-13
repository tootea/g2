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
tilburg97.max_interpol_val = 14.6469

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
nl95.max_interpol_val = 15.5329

nl96 = PerMonth(
    2900,  3367,  4580,
    5492, 11722, 11681,
    7745, 10288, 10928,
    6843,  4660,  4934 )
# CBS / Maandstatistiek bevolking 45(1997)9, 19.
nl96.max_interpol_val = 14.9933

nl97 = PerMonth(
    3075,  3428,  3974,
    6130, 11380, 11042,
    8560, 10010, 11025,
    7243,  4094,  5125 )
# CBS / Maandstatistiek bevolking 46(1998)9, 65.
nl97.max_interpol_val = 14.0910

nl98 = PerMonth(
    2688,  3456,  4497,
    6473, 11339, 11047,
    8932, 10141, 11740,
    7248,  4289,  5106 )
# CBS / Maandstatistiek bevolking 47(1999)9, 56.
nl98.max_interpol_val = 13.6747

# 1964-1968
# CBS / Statistiek van de loop der bevolking van Nederland 1946-1967
nl64 = PerMonth(
    5343,  5126,  5529,
    8732, 10074,  8104,
   11204,  8513,  9508,
    9825,  9641, 11314 )
nl64.max_interpol_val = 11.2173

nl65 = PerMonth(
    4978,  6503,  6171,
    9042,  9884,  9220,
   10509,  8904,  9837,
    9644, 10324, 13501 )
nl65.max_interpol_val = 12.7150

nl66 = PerMonth(
    4510,  5812,  6500,
    8704, 10105,  9581,
    9888,  9245, 10314,
    9407, 10656, 17190 )
nl66.max_interpol_val = 15.5732

nl67 = PerMonth(
    4129,  5155,  7906,
    8051,  9925, 11376,
    7996,  9647, 10527,
    9406, 11077, 19920 )
nl67.max_interpol_val = 17.5016

nl68 = PerMonth(
    3403,  5053,  6821,
    7709, 11027,  9189,
    8883, 10080,  9659,
   10109, 12579, 23022 )
nl68.max_interpol_val = 19.8675
