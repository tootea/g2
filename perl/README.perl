Howto build perl library

perl Makefile.PL
swig -perl5 -o g2_wrap.c -I../src -DDO_PS ../src/g2.h
nmake
nmake install
