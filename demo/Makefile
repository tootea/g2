# Generated automatically from Makefile.in by configure.
#
#
# Makefile for g2_library (demo)
#
#


CC = gcc
##Linux
F77 = g77
CPP = /lib/cpp

##OSF
#F77 = f77
#F77_FLAGS=-i8

##AIX
#F77 = xlf
#CPP = /usr/ccs/lib/cpp

##IRIX
#F77 = f77 -n32
#CPP = /lib/cpp -P -DFORTRAN

CFLAGS = -I../src -I../src/X11 -I../src/PS -I../src/GIF -I../src/GD -g -O2  -I/usr/X11R6/include -I/usr/local/include  -DLINUX=1 -DDO_PS=1 -DDO_X11=1 -DDO_GD=1 -DSTDC_HEADERS=1 -DHAVE_LIMITS_H=1 
LDFLAGS = -L.. -lg2   -L/usr/X11R6/lib -L/usr/local/lib -lm -lX11 -lgd

DEMO_PS = simple_PS
DEMO_X11 = simple_X11 pointer
#DEMO_GIF = simple_GIF
DEMO_GD = simple_gd

DEMO = g2_test g2_splines_demo $(DEMO_PS) $(DEMO_X11) $(DEMO_GIF) $(DEMO_GD)

all:	$(DEMO)

demo:	$(DEMO)


g2_test:  g2_test.c
	$(CC) $(CFLAGS) g2_test.c $(LDFLAGS) -o $@

g2_splines_demo:  g2_splines_demo.c
	$(CC) $(CFLAGS) g2_splines_demo.c $(LDFLAGS) -o $@

simple_PS:  simple_PS.c
	$(CC) $(CFLAGS) simple_PS.c $(LDFLAGS) -o $@

simple_X11:  simple_X11.c
	$(CC) $(CFLAGS) simple_X11.c $(LDFLAGS) -o $@

pointer:  pointer.c
	$(CC) $(CFLAGS) pointer.c $(LDFLAGS) -o $@

simple_GIF:  simple_GIF.c
	$(CC) $(CFLAGS) simple_GIF.c $(LDFLAGS) -o $@

simple_gd:  simple_gd.c
	$(CC) $(CFLAGS) simple_gd.c $(LDFLAGS) -o $@

demo_f: demo_f.f
	$(F77) $(F77_FLAGS) demo_f.f $(LDFLAGS) -o $@

g2testf:
	$(CPP)  -DLINUX=1 -DDO_PS=1 -DDO_X11=1 -DDO_GD=1 -DSTDC_HEADERS=1 -DHAVE_LIMITS_H=1  -E g2_test.F >g2_test.f
	$(F77) g2_test.f $(LDFLAGS) -o g2testf

clean:
	-rm $(DEMO) g2_testf demo_f *~ core *.ps *.gif


