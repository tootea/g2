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
LDFLAGS      =   -L/usr/X11R6/lib -L/usr/local/lib -lm -lX11 -lgd


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

demo:	libg2.a
	(cd ./demo ; make)

depend:
	$(MAKEDEPEND) -- $(CFLAGS) -- $(SRC)
	@echo
	@echo "Run 'make' to build g2 library."
	@echo


# DO NOT DELETE THIS LINE -- make  depend  depends  on it.

