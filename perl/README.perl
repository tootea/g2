Howto build perl library

perl Makefile.PL
swig -perl5 -o g2_wrap.c -I../src -DDO_PS -DDO_GD ../src/g2.h
"c:\Program Files\SWIG-1.3.13\swig" -perl5 -o g2_wrap.c -I../src -DDO_PS -DDO_GD -DDO_WIN32 ../src/g2.h
nmake
nmake install
