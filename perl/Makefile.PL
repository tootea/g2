use ExtUtils::MakeMaker;
WriteMakefile(
	      'NAME' => 'g2',
	      'LIBS' => ["-L.. -lg2 -lX11 -lgd -lpng -lz -ljpeg -lXpm" ],
	      'OBJECT' => 'g2_wrap.o',
	      'DEFINE' => '-DDO_X11 -DDO_PS -DDO_GD',
	      'INC'  => '-I../src/X11 -I../src/PS -I../src/GD -I../src'
	      );
