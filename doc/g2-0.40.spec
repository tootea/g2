Summary: g2 graphical library
Name: g2
Version: 0.40
Release: 1
Group: Development/Libraries
Source: ftp://sunsite.unc.edu/pub/Linux/libs/graphics/g2-0.40.tar.gz
Copyright: GPL
Requires: gd XFree86-libs
Buildroot: /tmp/g2_buildroot

%description
g2 is a easy to use graphics library for 2D graphical applications
written in Ansi-C. g2 library provides a comprehensive set of
functions for simultaneous generation of graphical output on different
types of devices. Following devices are currently supported by g2:
PostScript, X11, GIF (using gd) and Win32 (xfig is in development). g2
has C, Perl and Fortran interface.

%prep
%setup


%build
./configure --prefix=$RPM_BUILD_ROOT
make depend
make


%install
make install


%files
%doc  README CHANGES COPYING doc/* demo/*
/usr/lib/libg2.a
/usr/include/g2.h
/usr/include/g2_PS.h
/usr/include/g2_X11.h
/usr/include/g2_GIF.h
