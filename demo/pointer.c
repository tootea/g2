#include <stdio.h>
#include <g2.h>
#include <g2_X11.h>

int main()
{
    int d;
    double x, y;
    unsigned int button;
    
    d=g2_open_X11(100, 50);

    g2_set_coordinate_system(d, 50, 25, 50., 25.);

    g2_line(d, -1, 0, 1, 0);
    g2_line(d, 0, -1, 0, 1);

    printf("Press <Enter> to start\n");
    getchar();

    for(;;) {
	g2_query_pointer(d, &x, &y, &button);
	printf("%f %f  0x%04x\n", x, y, button);
    }
	
    return 0;
}

