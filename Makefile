# Generated automatically from Makefile.in by configure.
#
#
# Makefile for g2 library
#
#

G2_VERSION = 0.40

#
# g2 installation directories
#
LIBDIR = /usr/local/lib
INCDIR = /usr/local/include

#LIBDIR = $(HOME)/local/lib
#INCDIR = $(HOME)/local/include

#
#------------------------ do not edit ------------------------
#
SHELL = /bin/sh

CC           = gcc
CFLAGS       = -I./src -g -O2  -I/usr/X11R6/include -I/usr/local/include  -DLINUX=1 -DDO_PS=1 -DDO_X11=1 -DDO_GIF=1 -DSTDC_HEADERS=1 -DHAVE_LIMITS_H=1 
INSTALL      = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
FIND         = find
MAKEDEPEND   = makedepend
AR           = ar
ARFLAGS      = -cr
RANLIB       = ranlib
LD           = ld
LDFLAGS      = 


BASE_DIR = ./src
BASE_SRC = $(BASE_DIR)/g2_device.c         $(BASE_DIR)/g2_ui_control.c \
           $(BASE_DIR)/g2_util.c           $(BASE_DIR)/g2_fif.c \
           $(BASE_DIR)/g2_virtual_device.c $(BASE_DIR)/g2_physical_device.c \
           $(BASE_DIR)/g2_graphic_pd.c     $(BASE_DIR)/g2_control_pd.c \
           $(BASE_DIR)/g2_ui_graphic.c     $(BASE_DIR)/g2_ui_virtual_device.c \
           $(BASE_DIR)/g2_ui_device.c
BASE_INS = $(BASE_DIR)/g2.h


PS_DIR = ./src/PS
PS_SRC = $(PS_DIR)/g2_PS.c
PS_INS = $(PS_DIR)/g2_PS.h


X11_DIR = ./src/X11
X11_SRC = $(X11_DIR)/g2_X11.c
X11_INS = $(X11_DIR)/g2_X11.h


GIF_DIR = ./src/GIF
GIF_SRC = $(GIF_DIR)/g2_GIF.c
GIF_INS = $(GIF_DIR)/g2_GIF.h


SRC = $(BASE_SRC) $(PS_SRC) $(X11_SRC) $(GIF_SRC)
OBJ = $(SRC:.c=.o)

INS =  $(BASE_INS) $(PS_INS) $(X11_INS) $(GIF_INS)

.c.o:  
	$(CC) $(CFLAGS) -c $< -o $@


all: libg2.a
	test -d ./include || mkdir ./include
	cp $(INS) ./include/

shared: libg2.so.0.$(G2_VERSION)
	@echo

libg2.a: $(OBJ)
	$(AR) $(ARFLAGS) libg2.a $(OBJ)
	test -n "$(RANLIB)" && $(RANLIB) $@
	ln -s libg2.a libg2.$(G2_VERSION).a

libg2.so.0.$(G2_VERSION): $(OBJ)
	$(LD) $(LDFLAGS) -soname libg2.so.0 -o $@ $(OBJ) -L/usr/X11/lib -lX11 -lgd -lm -lc

install: libg2.a
	test -d $(LIBDIR) || mkdir -p $(LIBDIR)
	test -d $(INCDIR) || mkdir -p $(INCDIR)
	$(INSTALL_DATA) libg2.a $(LIBDIR)
	for IFILE in $(INS); do \
		$(INSTALL_DATA) $$IFILE  $(INCDIR); \
	done

clean:
	-(cd ./demo ; make clean)
	-rm -f $(OBJ)
	-rm -f libg2.a config.cache config.log Makefile.bak config.status
	-rm -f ./include/*.h
	-$(FIND) . -name "*~" -exec rm -f {} \;
	-(cd ./g2_perl ; make clean)
	-rm -f ./g2_perl/test.ps ./g2_perl/test.gif
	-rm -f ./libg2.$(G2_VERSION).a

demo:	libg2.a
	(cd ./demo ; make)

depend:
	$(MAKEDEPEND) -- $(CFLAGS) -- $(SRC)
	@echo
	@echo "Run 'make' to build g2 library."
	@echo


# DO NOT DELETE THIS LINE -- make  depend  depends  on it.

./src/g2_device.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_device.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_device.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_device.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_device.o: ./src/g2.h ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_device.o: ./src/g2_funix.h ./src/g2_virtual_device.h ./src/g2_util.h
./src/g2_device.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_device.o: /usr/include/time.h /usr/include/endian.h
./src/g2_device.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_device.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_ui_control.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_ui_control.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_ui_control.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_ui_control.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_ui_control.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_ui_control.o: /usr/include/time.h /usr/include/endian.h
./src/g2_ui_control.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_ui_control.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_ui_control.o: /usr/include/math.h /usr/include/huge_val.h
./src/g2_ui_control.o: /usr/include/mathcalls.h ./src/g2.h ./src/g2_device.h
./src/g2_ui_control.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/g2_ui_control.o: ./src/g2_virtual_device.h ./src/g2_control_pd.h
./src/g2_util.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_util.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_util.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_util.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_util.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_util.o: /usr/include/time.h /usr/include/endian.h
./src/g2_util.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_util.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_util.o: /usr/include/math.h /usr/include/huge_val.h
./src/g2_util.o: /usr/include/mathcalls.h ./src/g2_util.h
./src/g2_util.o: ./src/g2_physical_device.h ./src/g2.h ./src/g2_funix.h
./src/g2_fif.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_fif.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_fif.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_fif.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_fif.o: /usr/include/string.h ./src/g2.h ./src/g2_util.h
./src/g2_fif.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_fif.o: /usr/include/time.h /usr/include/endian.h
./src/g2_fif.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_fif.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_fif.o: ./src/g2_physical_device.h ./src/g2_funix.h ./src/PS/g2_PS.h
./src/g2_fif.o: ./src/X11/g2_X11.h ./src/GIF/g2_GIF.h
./src/g2_virtual_device.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_virtual_device.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_virtual_device.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_virtual_device.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_virtual_device.o: ./src/g2_virtual_device.h ./src/g2_device.h
./src/g2_virtual_device.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_virtual_device.o: ./src/g2_funix.h ./src/g2_util.h
./src/g2_virtual_device.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_virtual_device.o: /usr/include/time.h /usr/include/endian.h
./src/g2_virtual_device.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_virtual_device.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_physical_device.o: /usr/include/stdlib.h /usr/include/features.h
./src/g2_physical_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_physical_device.o: /usr/include/sys/types.h /usr/include/gnu/types.h
./src/g2_physical_device.o: /usr/include/time.h /usr/include/endian.h
./src/g2_physical_device.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_physical_device.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_physical_device.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_physical_device.o: /usr/include/_G_config.h /usr/include/stdio_lim.h
./src/g2_physical_device.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_physical_device.o: ./src/g2_funix.h ./src/g2_util.h
./src/g2_graphic_pd.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_graphic_pd.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_graphic_pd.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_graphic_pd.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_graphic_pd.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_graphic_pd.o: /usr/include/time.h /usr/include/endian.h
./src/g2_graphic_pd.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_graphic_pd.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_graphic_pd.o: /usr/include/math.h /usr/include/huge_val.h
./src/g2_graphic_pd.o: /usr/include/mathcalls.h ./src/g2_funix.h
./src/g2_graphic_pd.o: ./src/g2_virtual_device.h ./src/g2_graphic_pd.h
./src/g2_graphic_pd.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_graphic_pd.o: ./src/g2_control_pd.h ./src/g2_util.h
./src/g2_control_pd.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_control_pd.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_control_pd.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_control_pd.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_control_pd.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_control_pd.o: /usr/include/time.h /usr/include/endian.h
./src/g2_control_pd.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_control_pd.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_control_pd.o: /usr/include/math.h /usr/include/huge_val.h
./src/g2_control_pd.o: /usr/include/mathcalls.h ./src/g2.h ./src/g2_device.h
./src/g2_control_pd.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/g2_control_pd.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/g2_ui_graphic.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_ui_graphic.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_ui_graphic.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_ui_graphic.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_ui_graphic.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_ui_graphic.o: ./src/g2.h ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_ui_graphic.o: ./src/g2_graphic_pd.h ./src/g2_util.h
./src/g2_ui_graphic.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_ui_graphic.o: /usr/include/time.h /usr/include/endian.h
./src/g2_ui_graphic.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/g2_ui_graphic.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_ui_virtual_device.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_ui_virtual_device.o: /usr/include/features.h
./src/g2_ui_virtual_device.o: /usr/include/sys/cdefs.h
./src/g2_ui_virtual_device.o: /usr/include/gnu/stubs.h
./src/g2_ui_virtual_device.o: /usr/include/_G_config.h
./src/g2_ui_virtual_device.o: /usr/include/gnu/types.h
./src/g2_ui_virtual_device.o: /usr/include/stdio_lim.h ./src/g2.h
./src/g2_ui_virtual_device.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_ui_virtual_device.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_ui_virtual_device.o: ./src/g2_util.h /usr/include/stdlib.h
./src/g2_ui_virtual_device.o: /usr/include/sys/types.h /usr/include/time.h
./src/g2_ui_virtual_device.o: /usr/include/endian.h /usr/include/bytesex.h
./src/g2_ui_virtual_device.o: /usr/include/sys/select.h
./src/g2_ui_virtual_device.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/g2_ui_device.o: /usr/include/stdio.h /usr/include/libio.h
./src/g2_ui_device.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/g2_ui_device.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/g2_ui_device.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/g2_ui_device.o: ./src/g2.h ./src/g2_funix.h ./src/g2_device.h
./src/g2_ui_device.o: ./src/g2_physical_device.h ./src/g2_virtual_device.h
./src/PS/g2_PS.o: /usr/include/stdio.h /usr/include/libio.h
./src/PS/g2_PS.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/PS/g2_PS.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/PS/g2_PS.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/PS/g2_PS.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/PS/g2_PS.o: /usr/include/time.h /usr/include/endian.h
./src/PS/g2_PS.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/PS/g2_PS.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/PS/g2_PS.o: /usr/include/limits.h /usr/include/posix1_lim.h
./src/PS/g2_PS.o: /usr/include/local_lim.h /usr/include/linux/limits.h
./src/PS/g2_PS.o: /usr/include/posix2_lim.h ./src/g2.h ./src/g2_device.h
./src/PS/g2_PS.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/PS/g2_PS.o: ./src/g2_virtual_device.h ./src/g2_util.h ./src/g2_config.h
./src/PS/g2_PS.o: ./src/PS/g2_PS.h ./src/PS/g2_PS_P.h ./src/PS/g2_PS_funix.h
./src/PS/g2_PS.o: ./src/PS/g2_PS_definitions.h
./src/X11/g2_X11.o: /usr/include/stdio.h /usr/include/libio.h
./src/X11/g2_X11.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/X11/g2_X11.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/X11/g2_X11.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/X11/g2_X11.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/X11/g2_X11.o: /usr/include/time.h /usr/include/endian.h
./src/X11/g2_X11.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/X11/g2_X11.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/X11/g2_X11.o: /usr/include/limits.h /usr/include/posix1_lim.h
./src/X11/g2_X11.o: /usr/include/local_lim.h /usr/include/linux/limits.h
./src/X11/g2_X11.o: /usr/include/posix2_lim.h /usr/include/math.h
./src/X11/g2_X11.o: /usr/include/huge_val.h /usr/include/mathcalls.h
./src/X11/g2_X11.o: /usr/include/string.h /usr/X11R6/include/X11/Xlib.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/X.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xfuncproto.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xosdefs.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xutil.h ./src/g2_device.h
./src/X11/g2_X11.o: ./src/g2_physical_device.h ./src/g2.h ./src/g2_funix.h
./src/X11/g2_X11.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/X11/g2_X11.o: ./src/X11/g2_X11_P.h ./src/X11/g2_X11.h
./src/X11/g2_X11.o: ./src/X11/g2_X11_funix.h ./src/g2_config.h
./src/GIF/g2_GIF.o: /usr/include/stdio.h /usr/include/libio.h
./src/GIF/g2_GIF.o: /usr/include/features.h /usr/include/sys/cdefs.h
./src/GIF/g2_GIF.o: /usr/include/gnu/stubs.h /usr/include/_G_config.h
./src/GIF/g2_GIF.o: /usr/include/gnu/types.h /usr/include/stdio_lim.h
./src/GIF/g2_GIF.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/GIF/g2_GIF.o: /usr/include/time.h /usr/include/endian.h
./src/GIF/g2_GIF.o: /usr/include/bytesex.h /usr/include/sys/select.h
./src/GIF/g2_GIF.o: /usr/include/selectbits.h /usr/include/alloca.h
./src/GIF/g2_GIF.o: /usr/include/math.h /usr/include/huge_val.h
./src/GIF/g2_GIF.o: /usr/include/mathcalls.h ./src/g2.h ./src/g2_device.h
./src/GIF/g2_GIF.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/GIF/g2_GIF.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/GIF/g2_GIF.o: ./src/g2_config.h ./src/GIF/g2_GIF_P.h /usr/include/gd.h
./src/GIF/g2_GIF.o: /usr/include/gdfontt.h /usr/include/gdfonts.h
./src/GIF/g2_GIF.o: /usr/include/gdfontmb.h /usr/include/gdfontl.h
./src/GIF/g2_GIF.o: /usr/include/gdfontg.h ./src/GIF/g2_GIF.h
./src/GIF/g2_GIF.o: ./src/GIF/g2_GIF_funix.h
