# Generated automatically from Makefile.in by configure.
#
#
# Makefile for g2 library
#
#

G2_VERSION = 0.41

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
LDFLAGS      =   -L/usr/X11R6/lib -L/usr/local/lib -lm -lX11 -lgd


BASE_DIR = ./src
BASE_SRC = $(BASE_DIR)/g2_device.c         $(BASE_DIR)/g2_ui_control.c \
           $(BASE_DIR)/g2_util.c           $(BASE_DIR)/g2_fif.c \
           $(BASE_DIR)/g2_virtual_device.c $(BASE_DIR)/g2_physical_device.c \
           $(BASE_DIR)/g2_graphic_pd.c     $(BASE_DIR)/g2_control_pd.c \
           $(BASE_DIR)/g2_ui_graphic.c     $(BASE_DIR)/g2_ui_virtual_device.c \
           $(BASE_DIR)/g2_ui_device.c      $(BASE_DIR)/g2_splines.c
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


#GD_DIR = ./src/GD
#GD_SRC = $(GD_DIR)/g2_gd.c
#GD_INS = $(GD_DIR)/g2_gd.h


SRC = $(BASE_SRC) $(PS_SRC) $(X11_SRC) $(GIF_SRC) $(GD_SRC)
OBJ = $(SRC:.c=.o)

INS =  $(BASE_INS) $(PS_INS) $(X11_INS) $(GIF_INS) $(GD_INS)

.c.o:  
	$(CC) $(CFLAGS) -c $< -o $@


all: libg2.a
	test -d ./include || mkdir ./include
	cp $(INS) ./include/

shared: libg2.so.0.$(G2_VERSION)
	@echo


libg2.a: $(OBJ)
	$(AR) $(ARFLAGS) libg2.a $(OBJ)
	test ! -n "$(RANLIB)" || $(RANLIB) $@
	test ! -f ./libg2.$(G2_VERSION).a || rm ./libg2.$(G2_VERSION).a
	ln -s libg2.a libg2.$(G2_VERSION).a

libg2.so.0.$(G2_VERSION): $(OBJ)
	ld -shared -soname libg2.so.0 -o $@ $(OBJ) 

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
	-rm -f ./libg2.so.0.$(G2_VERSION)
	-rm -f libg2.$(G2_VERSION).a

demo:	libg2.a
	(cd ./demo ; make)

depend:
	$(MAKEDEPEND) -- $(CFLAGS) -- $(SRC)
	@echo
	@echo "Run 'make' to build g2 library."
	@echo


# DO NOT DELETE THIS LINE -- make  depend  depends  on it.

./src/g2_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_device.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_device.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_device.o: ./src/g2.h ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_device.o: ./src/g2_funix.h ./src/g2_virtual_device.h ./src/g2_util.h
./src/g2_device.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_device.o: /usr/include/time.h /usr/include/endian.h
./src/g2_device.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_device.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_device.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_ui_control.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_control.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_ui_control.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_ui_control.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_ui_control.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_ui_control.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_ui_control.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_ui_control.o: /usr/include/time.h /usr/include/endian.h
./src/g2_ui_control.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_ui_control.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_ui_control.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_ui_control.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_ui_control.o: /usr/include/bits/mathdef.h
./src/g2_ui_control.o: /usr/include/bits/mathcalls.h
./src/g2_ui_control.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/g2_ui_control.o: ./src/g2.h ./src/g2_device.h
./src/g2_ui_control.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/g2_ui_control.o: ./src/g2_virtual_device.h ./src/g2_control_pd.h
./src/g2_util.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_util.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_util.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_util.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_util.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_util.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_util.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_util.o: /usr/include/time.h /usr/include/endian.h
./src/g2_util.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_util.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_util.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_util.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_util.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/g2_util.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/g2_util.o: ./src/g2_util.h ./src/g2_physical_device.h ./src/g2.h
./src/g2_util.o: ./src/g2_funix.h
./src/g2_fif.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_fif.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_fif.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_fif.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_fif.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_fif.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_fif.o: /usr/include/string.h ./src/g2.h ./src/g2_util.h
./src/g2_fif.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_fif.o: /usr/include/time.h /usr/include/endian.h
./src/g2_fif.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_fif.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_fif.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_fif.o: ./src/g2_physical_device.h ./src/g2_funix.h ./src/PS/g2_PS.h
./src/g2_fif.o: ./src/X11/g2_X11.h ./src/GIF/g2_GIF.h
./src/g2_virtual_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_virtual_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_virtual_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_virtual_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_virtual_device.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_virtual_device.o: /usr/include/_G_config.h
./src/g2_virtual_device.o: /usr/include/bits/stdio_lim.h
./src/g2_virtual_device.o: ./src/g2_virtual_device.h ./src/g2_device.h
./src/g2_virtual_device.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_virtual_device.o: ./src/g2_funix.h ./src/g2_util.h
./src/g2_virtual_device.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_virtual_device.o: /usr/include/time.h /usr/include/endian.h
./src/g2_virtual_device.o: /usr/include/bits/endian.h
./src/g2_virtual_device.o: /usr/include/sys/select.h
./src/g2_virtual_device.o: /usr/include/bits/select.h
./src/g2_virtual_device.o: /usr/include/bits/sigset.h
./src/g2_virtual_device.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_physical_device.o: /usr/include/stdlib.h /usr/include/features.h
./src/g2_physical_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_physical_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_physical_device.o: /usr/include/sys/types.h
./src/g2_physical_device.o: /usr/include/bits/types.h /usr/include/time.h
./src/g2_physical_device.o: /usr/include/endian.h /usr/include/bits/endian.h
./src/g2_physical_device.o: /usr/include/sys/select.h
./src/g2_physical_device.o: /usr/include/bits/select.h
./src/g2_physical_device.o: /usr/include/bits/sigset.h
./src/g2_physical_device.o: /usr/include/sys/sysmacros.h
./src/g2_physical_device.o: /usr/include/alloca.h /usr/include/stdio.h
./src/g2_physical_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_physical_device.o: /usr/include/libio.h /usr/include/_G_config.h
./src/g2_physical_device.o: /usr/include/bits/stdio_lim.h
./src/g2_physical_device.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_physical_device.o: ./src/g2_funix.h ./src/g2_util.h
./src/g2_graphic_pd.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_graphic_pd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_graphic_pd.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_graphic_pd.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_graphic_pd.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_graphic_pd.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_graphic_pd.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_graphic_pd.o: /usr/include/time.h /usr/include/endian.h
./src/g2_graphic_pd.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_graphic_pd.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_graphic_pd.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_graphic_pd.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_graphic_pd.o: /usr/include/bits/mathdef.h
./src/g2_graphic_pd.o: /usr/include/bits/mathcalls.h
./src/g2_graphic_pd.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/g2_graphic_pd.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_graphic_pd.o: ./src/g2_graphic_pd.h ./src/g2_physical_device.h
./src/g2_graphic_pd.o: ./src/g2.h ./src/g2_control_pd.h ./src/g2_util.h
./src/g2_control_pd.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_control_pd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_control_pd.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_control_pd.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_control_pd.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_control_pd.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_control_pd.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_control_pd.o: /usr/include/time.h /usr/include/endian.h
./src/g2_control_pd.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_control_pd.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_control_pd.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_control_pd.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_control_pd.o: /usr/include/bits/mathdef.h
./src/g2_control_pd.o: /usr/include/bits/mathcalls.h
./src/g2_control_pd.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/g2_control_pd.o: ./src/g2.h ./src/g2_device.h
./src/g2_control_pd.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/g2_control_pd.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/g2_ui_graphic.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_graphic.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_ui_graphic.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_ui_graphic.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_ui_graphic.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_ui_graphic.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_ui_graphic.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_ui_graphic.o: ./src/g2.h ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_ui_graphic.o: ./src/g2_graphic_pd.h ./src/g2_util.h
./src/g2_ui_graphic.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_ui_graphic.o: /usr/include/time.h /usr/include/endian.h
./src/g2_ui_graphic.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_ui_graphic.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_ui_graphic.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_ui_virtual_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_virtual_device.o: /usr/include/sys/cdefs.h
./src/g2_ui_virtual_device.o: /usr/include/gnu/stubs.h
./src/g2_ui_virtual_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_ui_virtual_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_ui_virtual_device.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_ui_virtual_device.o: /usr/include/_G_config.h
./src/g2_ui_virtual_device.o: /usr/include/bits/stdio_lim.h ./src/g2.h
./src/g2_ui_virtual_device.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_ui_virtual_device.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_ui_virtual_device.o: ./src/g2_util.h /usr/include/stdlib.h
./src/g2_ui_virtual_device.o: /usr/include/sys/types.h /usr/include/time.h
./src/g2_ui_virtual_device.o: /usr/include/endian.h
./src/g2_ui_virtual_device.o: /usr/include/bits/endian.h
./src/g2_ui_virtual_device.o: /usr/include/sys/select.h
./src/g2_ui_virtual_device.o: /usr/include/bits/select.h
./src/g2_ui_virtual_device.o: /usr/include/bits/sigset.h
./src/g2_ui_virtual_device.o: /usr/include/sys/sysmacros.h
./src/g2_ui_virtual_device.o: /usr/include/alloca.h
./src/g2_ui_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_ui_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_ui_device.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_ui_device.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_ui_device.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_ui_device.o: ./src/g2.h ./src/g2_funix.h ./src/g2_device.h
./src/g2_ui_device.o: ./src/g2_physical_device.h ./src/g2_virtual_device.h
./src/g2_splines.o: /usr/include/math.h /usr/include/features.h
./src/g2_splines.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_splines.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
./src/g2_splines.o: /usr/include/bits/mathcalls.h
./src/g2_splines.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/g2_splines.o: /usr/include/stdio.h
./src/g2_splines.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/g2_splines.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/g2_splines.o: /usr/include/bits/types.h /usr/include/libio.h
./src/g2_splines.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/g2_splines.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/g2_splines.o: /usr/include/time.h /usr/include/endian.h
./src/g2_splines.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/g2_splines.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/g2_splines.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/g2_splines.o: ./src/g2.h ./src/g2_util.h ./src/g2_physical_device.h
./src/g2_splines.o: ./src/g2_funix.h
./src/PS/g2_PS.o: /usr/include/stdio.h /usr/include/features.h
./src/PS/g2_PS.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/PS/g2_PS.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/PS/g2_PS.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/PS/g2_PS.o: /usr/include/bits/types.h /usr/include/libio.h
./src/PS/g2_PS.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/PS/g2_PS.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/PS/g2_PS.o: /usr/include/time.h /usr/include/endian.h
./src/PS/g2_PS.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/PS/g2_PS.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/PS/g2_PS.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/PS/g2_PS.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
./src/PS/g2_PS.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
./src/PS/g2_PS.o: /usr/include/bits/posix2_lim.h /usr/include/math.h
./src/PS/g2_PS.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
./src/PS/g2_PS.o: /usr/include/bits/mathcalls.h
./src/PS/g2_PS.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/PS/g2_PS.o: /usr/include/string.h ./src/g2.h ./src/g2_device.h
./src/PS/g2_PS.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/PS/g2_PS.o: ./src/g2_virtual_device.h ./src/g2_util.h ./src/g2_config.h
./src/PS/g2_PS.o: ./src/PS/g2_PS.h ./src/PS/g2_PS_P.h ./src/PS/g2_PS_funix.h
./src/PS/g2_PS.o: ./src/PS/g2_PS_definitions.h
./src/X11/g2_X11.o: /usr/include/stdio.h /usr/include/features.h
./src/X11/g2_X11.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/X11/g2_X11.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/X11/g2_X11.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/X11/g2_X11.o: /usr/include/bits/types.h /usr/include/libio.h
./src/X11/g2_X11.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/X11/g2_X11.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/X11/g2_X11.o: /usr/include/time.h /usr/include/endian.h
./src/X11/g2_X11.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/X11/g2_X11.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/X11/g2_X11.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/X11/g2_X11.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
./src/X11/g2_X11.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
./src/X11/g2_X11.o: /usr/include/bits/posix2_lim.h /usr/include/math.h
./src/X11/g2_X11.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
./src/X11/g2_X11.o: /usr/include/bits/mathcalls.h
./src/X11/g2_X11.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/X11/g2_X11.o: /usr/include/string.h /usr/X11R6/include/X11/Xlib.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/X.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xfuncproto.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xosdefs.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xutil.h ./src/g2_device.h
./src/X11/g2_X11.o: ./src/g2_physical_device.h ./src/g2.h ./src/g2_funix.h
./src/X11/g2_X11.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/X11/g2_X11.o: ./src/X11/g2_X11_P.h ./src/X11/g2_X11.h
./src/X11/g2_X11.o: ./src/X11/g2_X11_funix.h ./src/g2_config.h
./src/GIF/g2_GIF.o: /usr/include/stdio.h /usr/include/features.h
./src/GIF/g2_GIF.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/GIF/g2_GIF.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stddef.h
./src/GIF/g2_GIF.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/stdarg.h
./src/GIF/g2_GIF.o: /usr/include/bits/types.h /usr/include/libio.h
./src/GIF/g2_GIF.o: /usr/include/_G_config.h /usr/include/bits/stdio_lim.h
./src/GIF/g2_GIF.o: /usr/include/stdlib.h /usr/include/sys/types.h
./src/GIF/g2_GIF.o: /usr/include/time.h /usr/include/endian.h
./src/GIF/g2_GIF.o: /usr/include/bits/endian.h /usr/include/sys/select.h
./src/GIF/g2_GIF.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
./src/GIF/g2_GIF.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
./src/GIF/g2_GIF.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/GIF/g2_GIF.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/GIF/g2_GIF.o: /usr/lib/gcc-lib/i386-redhat-linux/egcs-2.91.66/include/float.h
./src/GIF/g2_GIF.o: ./src/g2.h ./src/g2_device.h ./src/g2_physical_device.h
./src/GIF/g2_GIF.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/GIF/g2_GIF.o: ./src/g2_util.h ./src/g2_config.h ./src/GIF/g2_GIF_P.h
./src/GIF/g2_GIF.o: /usr/include/gd.h /usr/include/gdfontt.h
./src/GIF/g2_GIF.o: /usr/include/gdfonts.h /usr/include/gdfontmb.h
./src/GIF/g2_GIF.o: /usr/include/gdfontl.h /usr/include/gdfontg.h
./src/GIF/g2_GIF.o: ./src/GIF/g2_GIF.h ./src/GIF/g2_GIF_funix.h
