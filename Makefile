# Generated automatically from Makefile.in by configure.
#
#
# Makefile for g2 library
#
#

G2_VERSION = 0.52a

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
CFLAGS       = -I./src -g -O2  -I/usr/X11R6/include -I/usr/local/include  -DLINUX=1 -DDO_PS=1 -DDO_FIG=1 -DDO_X11=1 -DDO_GD=1 -DSTDC_HEADERS=1 -DHAVE_LIMITS_H=1 
INSTALL      = /usr//bin/install -c
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

FIG_DIR = ./src/FIG
FIG_SRC = $(FIG_DIR)/g2_FIG.c
FIG_INS = $(FIG_DIR)/g2_FIG.h

X11_DIR = ./src/X11
X11_SRC = $(X11_DIR)/g2_X11.c
X11_INS = $(X11_DIR)/g2_X11.h

#WIN32_DIR = ./src/WIN32
#WIN32_SRC = $(WIN32_DIR)/g2_win32.c $(WIN32_DIR)/g2_win32_thread.c 
#WIN32_INS = $(WIN32_DIR)/g2_win32.h

GD_DIR = ./src/GD
GD_SRC = $(GD_DIR)/g2_gd.c
GD_INS = $(GD_DIR)/g2_gd.h


SRC = $(BASE_SRC) $(PS_SRC) $(FIG_SRC) $(X11_SRC) $(WIN32_SRC) $(GD_SRC)
OBJ = $(SRC:.c=.o)

INS =  $(BASE_INS) $(PS_INS) $(FIG_INS) $(X11_INS) $(WIN32_INS) $(GD_INS)

#
# define some phony targets
#
.PHONY: all shared clean doc release demo

#
# major rule
#
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

release: clean doc
	cp ./doc/latex/refman.ps  ./doc/g2_refman.ps
	cp ./doc/latex/refman.pdf ./doc/g2_refman.pdf
	rm -r ./doc/latex

doc:
	(cd ./doc ; doxygen Doxyfile)
	(cd ./doc/latex ; make ps ; make pdf)


clean:
	-(cd ./demo ; make clean)
	-rm -f $(OBJ)
	-rm -f libg2.a config.cache config.log Makefile.bak config.status
	-rm -f ./include/*.h
	-$(FIND) . -name "*~" -exec rm -f {} \;
	-(cd ./g2_perl ; make clean)
	-rm -f ./g2_perl/test.ps
	-rm -f ./g2_perl/test.png
	-rm -f ./g2_perl/Makefile.old
	-rm -f ./libg2.so.0.$(G2_VERSION)
	-rm -f libg2.$(G2_VERSION).a
	-rm -f a.out
	-rm -fr doc/html/ doc/latex/ doc/g2_refman.ps doc/g2_refman.pdf

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
./src/g2_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_device.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_device.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_device.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_device.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_device.o: /usr/include/bits/stdio_lim.h
./src/g2_device.o: /usr/include/bits/sys_errlist.h ./src/g2.h
./src/g2_device.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_device.o: ./src/g2_funix.h ./src/g2_virtual_device.h ./src/g2_util.h
./src/g2_device.o: /usr/include/stdlib.h
./src/g2_ui_control.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_control.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_ui_control.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_ui_control.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_ui_control.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_ui_control.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_ui_control.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_ui_control.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_ui_control.o: /usr/include/bits/stdio_lim.h
./src/g2_ui_control.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/g2_ui_control.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_ui_control.o: /usr/include/bits/mathdef.h
./src/g2_ui_control.o: /usr/include/bits/mathcalls.h ./src/g2.h
./src/g2_ui_control.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_ui_control.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_ui_control.o: ./src/g2_control_pd.h
./src/g2_util.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_util.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_util.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_util.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_util.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_util.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_util.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_util.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_util.o: /usr/include/bits/stdio_lim.h
./src/g2_util.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/g2_util.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_util.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/g2_util.o: ./src/g2_util.h ./src/g2_physical_device.h ./src/g2.h
./src/g2_util.o: ./src/g2_funix.h ./src/g2_config.h
./src/g2_fif.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_fif.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_fif.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_fif.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_fif.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_fif.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_fif.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_fif.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_fif.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
./src/g2_fif.o: /usr/include/string.h ./src/g2.h ./src/g2_util.h
./src/g2_fif.o: /usr/include/stdlib.h ./src/g2_physical_device.h
./src/g2_fif.o: ./src/g2_funix.h ./src/PS/g2_PS.h ./src/X11/g2_X11.h
./src/g2_fif.o: ./src/GD/g2_gd.h
./src/g2_virtual_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_virtual_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_virtual_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_virtual_device.o: /usr/include/bits/types.h
./src/g2_virtual_device.o: /usr/include/bits/wordsize.h
./src/g2_virtual_device.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_virtual_device.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_virtual_device.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_virtual_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_virtual_device.o: /usr/include/bits/stdio_lim.h
./src/g2_virtual_device.o: /usr/include/bits/sys_errlist.h
./src/g2_virtual_device.o: ./src/g2_virtual_device.h ./src/g2_device.h
./src/g2_virtual_device.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_virtual_device.o: ./src/g2_funix.h ./src/g2_util.h
./src/g2_virtual_device.o: /usr/include/stdlib.h
./src/g2_physical_device.o: /usr/include/stdlib.h /usr/include/features.h
./src/g2_physical_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_physical_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_physical_device.o: /usr/include/stdio.h /usr/include/bits/types.h
./src/g2_physical_device.o: /usr/include/bits/wordsize.h
./src/g2_physical_device.o: /usr/include/bits/typesizes.h
./src/g2_physical_device.o: /usr/include/libio.h /usr/include/_G_config.h
./src/g2_physical_device.o: /usr/include/wchar.h /usr/include/bits/wchar.h
./src/g2_physical_device.o: /usr/include/gconv.h
./src/g2_physical_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_physical_device.o: /usr/include/bits/stdio_lim.h
./src/g2_physical_device.o: /usr/include/bits/sys_errlist.h
./src/g2_physical_device.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_physical_device.o: ./src/g2_funix.h ./src/g2_util.h
./src/g2_graphic_pd.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_graphic_pd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_graphic_pd.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_graphic_pd.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_graphic_pd.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_graphic_pd.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_graphic_pd.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_graphic_pd.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_graphic_pd.o: /usr/include/bits/stdio_lim.h
./src/g2_graphic_pd.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/g2_graphic_pd.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_graphic_pd.o: /usr/include/bits/mathdef.h
./src/g2_graphic_pd.o: /usr/include/bits/mathcalls.h ./src/g2_funix.h
./src/g2_graphic_pd.o: ./src/g2_virtual_device.h ./src/g2_graphic_pd.h
./src/g2_graphic_pd.o: ./src/g2_physical_device.h ./src/g2.h
./src/g2_graphic_pd.o: ./src/g2_control_pd.h ./src/g2_util.h
./src/g2_control_pd.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_control_pd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_control_pd.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_control_pd.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_control_pd.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_control_pd.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_control_pd.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_control_pd.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_control_pd.o: /usr/include/bits/stdio_lim.h
./src/g2_control_pd.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/g2_control_pd.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/g2_control_pd.o: /usr/include/bits/mathdef.h
./src/g2_control_pd.o: /usr/include/bits/mathcalls.h ./src/g2.h
./src/g2_control_pd.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_control_pd.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_control_pd.o: ./src/g2_util.h
./src/g2_ui_graphic.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_graphic.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_ui_graphic.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_ui_graphic.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_ui_graphic.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_ui_graphic.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_ui_graphic.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_ui_graphic.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_ui_graphic.o: /usr/include/bits/stdio_lim.h
./src/g2_ui_graphic.o: /usr/include/bits/sys_errlist.h ./src/g2_device.h
./src/g2_ui_graphic.o: ./src/g2_physical_device.h ./src/g2.h ./src/g2_funix.h
./src/g2_ui_graphic.o: ./src/g2_virtual_device.h ./src/g2_graphic_pd.h
./src/g2_ui_graphic.o: ./src/g2_util.h /usr/include/stdlib.h
./src/g2_ui_virtual_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_virtual_device.o: /usr/include/sys/cdefs.h
./src/g2_ui_virtual_device.o: /usr/include/gnu/stubs.h
./src/g2_ui_virtual_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_ui_virtual_device.o: /usr/include/bits/types.h
./src/g2_ui_virtual_device.o: /usr/include/bits/wordsize.h
./src/g2_ui_virtual_device.o: /usr/include/bits/typesizes.h
./src/g2_ui_virtual_device.o: /usr/include/libio.h /usr/include/_G_config.h
./src/g2_ui_virtual_device.o: /usr/include/wchar.h /usr/include/bits/wchar.h
./src/g2_ui_virtual_device.o: /usr/include/gconv.h
./src/g2_ui_virtual_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_ui_virtual_device.o: /usr/include/bits/stdio_lim.h
./src/g2_ui_virtual_device.o: /usr/include/bits/sys_errlist.h ./src/g2.h
./src/g2_ui_virtual_device.o: ./src/g2_device.h ./src/g2_physical_device.h
./src/g2_ui_virtual_device.o: ./src/g2_funix.h ./src/g2_virtual_device.h
./src/g2_ui_virtual_device.o: ./src/g2_util.h /usr/include/stdlib.h
./src/g2_ui_device.o: /usr/include/stdio.h /usr/include/features.h
./src/g2_ui_device.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_ui_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_ui_device.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_ui_device.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_ui_device.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_ui_device.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_ui_device.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_ui_device.o: /usr/include/bits/stdio_lim.h
./src/g2_ui_device.o: /usr/include/bits/sys_errlist.h ./src/g2.h
./src/g2_ui_device.o: ./src/g2_funix.h ./src/g2_device.h
./src/g2_ui_device.o: ./src/g2_physical_device.h ./src/g2_virtual_device.h
./src/g2_ui_device.o: ./src/g2_util.h /usr/include/stdlib.h
./src/g2_splines.o: /usr/include/math.h /usr/include/features.h
./src/g2_splines.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/g2_splines.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
./src/g2_splines.o: /usr/include/bits/mathcalls.h /usr/include/stdio.h
./src/g2_splines.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/g2_splines.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/g2_splines.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/g2_splines.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/g2_splines.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/g2_splines.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/g2_splines.o: /usr/include/bits/stdio_lim.h
./src/g2_splines.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/g2_splines.o: ./src/g2.h ./src/g2_util.h ./src/g2_physical_device.h
./src/g2_splines.o: ./src/g2_funix.h
./src/PS/g2_PS.o: /usr/include/stdio.h /usr/include/features.h
./src/PS/g2_PS.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/PS/g2_PS.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/PS/g2_PS.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/PS/g2_PS.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/PS/g2_PS.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/PS/g2_PS.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/PS/g2_PS.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/PS/g2_PS.o: /usr/include/bits/stdio_lim.h
./src/PS/g2_PS.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/PS/g2_PS.o: /usr/include/limits.h
./src/PS/g2_PS.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/limits.h
./src/PS/g2_PS.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/PS/g2_PS.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/PS/g2_PS.o: /usr/include/string.h ./src/g2.h ./src/g2_device.h
./src/PS/g2_PS.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/PS/g2_PS.o: ./src/g2_virtual_device.h ./src/g2_util.h ./src/g2_config.h
./src/PS/g2_PS.o: ./src/PS/g2_PS.h ./src/PS/g2_PS_P.h ./src/PS/g2_PS_funix.h
./src/PS/g2_PS.o: ./src/PS/g2_PS_definitions.h
./src/FIG/g2_FIG.o: /usr/include/stdio.h /usr/include/features.h
./src/FIG/g2_FIG.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/FIG/g2_FIG.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/FIG/g2_FIG.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/FIG/g2_FIG.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/FIG/g2_FIG.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/FIG/g2_FIG.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/FIG/g2_FIG.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/FIG/g2_FIG.o: /usr/include/bits/stdio_lim.h
./src/FIG/g2_FIG.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/FIG/g2_FIG.o: /usr/include/limits.h
./src/FIG/g2_FIG.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/limits.h
./src/FIG/g2_FIG.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/FIG/g2_FIG.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/FIG/g2_FIG.o: /usr/include/string.h ./src/g2.h ./src/g2_device.h
./src/FIG/g2_FIG.o: ./src/g2_physical_device.h ./src/g2_funix.h
./src/FIG/g2_FIG.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/FIG/g2_FIG.o: ./src/g2_config.h ./src/FIG/g2_FIG.h ./src/FIG/g2_FIG_P.h
./src/FIG/g2_FIG.o: ./src/FIG/g2_FIG_funix.h
./src/X11/g2_X11.o: /usr/include/stdio.h /usr/include/features.h
./src/X11/g2_X11.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/X11/g2_X11.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/X11/g2_X11.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/X11/g2_X11.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/X11/g2_X11.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/X11/g2_X11.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/X11/g2_X11.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/X11/g2_X11.o: /usr/include/bits/stdio_lim.h
./src/X11/g2_X11.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/X11/g2_X11.o: /usr/include/limits.h
./src/X11/g2_X11.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/limits.h
./src/X11/g2_X11.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/X11/g2_X11.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/X11/g2_X11.o: /usr/include/string.h /usr/X11R6/include/X11/Xlib.h
./src/X11/g2_X11.o: /usr/include/sys/types.h /usr/include/time.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/X.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xfuncproto.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xosdefs.h
./src/X11/g2_X11.o: /usr/X11R6/include/X11/Xutil.h ./src/g2_device.h
./src/X11/g2_X11.o: ./src/g2_physical_device.h ./src/g2.h ./src/g2_funix.h
./src/X11/g2_X11.o: ./src/g2_virtual_device.h ./src/g2_util.h
./src/X11/g2_X11.o: ./src/X11/g2_X11_P.h ./src/X11/g2_X11.h
./src/X11/g2_X11.o: ./src/X11/g2_X11_funix.h ./src/g2_config.h
./src/GD/g2_gd.o: /usr/include/stdio.h /usr/include/features.h
./src/GD/g2_gd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
./src/GD/g2_gd.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stddef.h
./src/GD/g2_gd.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
./src/GD/g2_gd.o: /usr/include/bits/typesizes.h /usr/include/libio.h
./src/GD/g2_gd.o: /usr/include/_G_config.h /usr/include/wchar.h
./src/GD/g2_gd.o: /usr/include/bits/wchar.h /usr/include/gconv.h
./src/GD/g2_gd.o: /usr/lib/gcc-lib/i586-mandrake-linux-gnu/3.2.2/include/stdarg.h
./src/GD/g2_gd.o: /usr/include/bits/stdio_lim.h
./src/GD/g2_gd.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
./src/GD/g2_gd.o: /usr/include/math.h /usr/include/bits/huge_val.h
./src/GD/g2_gd.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
./src/GD/g2_gd.o: ./src/g2.h ./src/g2_device.h ./src/g2_physical_device.h
./src/GD/g2_gd.o: ./src/g2_funix.h ./src/g2_virtual_device.h ./src/g2_util.h
./src/GD/g2_gd.o: ./src/g2_config.h ./src/GD/g2_gd_P.h
./src/GD/g2_gd.o: /usr/local/include/gd.h /usr/local/include/gd_io.h
./src/GD/g2_gd.o: /usr/local/include/gdfx.h /usr/local/include/gdfontt.h
./src/GD/g2_gd.o: /usr/local/include/gdfonts.h /usr/local/include/gdfontmb.h
./src/GD/g2_gd.o: /usr/local/include/gdfontl.h /usr/local/include/gdfontg.h
./src/GD/g2_gd.o: ./src/GD/g2_gd.h ./src/GD/g2_gd_funix.h
