#include <stdio.h>
#include <iostream>
#include <g2_X11.h>
#include <g2.h>

/* A very simple example to demonstrate g2 in a C++ environment */


class Circle
{
public:
  Circle(int d, double x, double y, double r)
    : _d(d), _x(x), _y(y), _r(r)
  {
    g2_circle(d, x, y, r);
    g2_flush(d);
  }

  void Fill()
  {
    g2_filled_circle(_d, _x, _y, _r);
    g2_flush(_d);
  }
private:
  int _d;
  double _x, _y, _r;
};


int main(int argc, char *argv[])
{
    int d;
    d=g2_open_X11(100, 100);
    Circle c(d, 50, 50, 25);
    std::cout << "Press [Enter]" << std::endl;
    getchar();
    c.Fill();
    std::cout << "Press [Enter]" << std::endl;
    getchar();
    return 0;
}
