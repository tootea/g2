#include <g2.h>
#include <g2_gd.h>

int main()
{
    int d;

    d=g2_open_gd("simple.png", 100, 100, g2_gd_png);
    g2_line(d, 10, 10, 90, 90);
    g2_close(d);
    return 0;
}

