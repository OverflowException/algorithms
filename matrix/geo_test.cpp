#include "geo_utility.h"
#include <iostream>

using namespace imgalg;

int main(int argc, char** argv)
{
  std::cout << "Point test" << std::endl;
  Point<double> p1(1, 3);
  Point<double> p2(6.3, 7.32);
  Point<double> p3, p4, p5;
  p3 = p1 + p2 + p2;
  p4 = p1 - p2;
  
  std::cout << p1 << std::endl;
  std::cout << p2 << std::endl;
  std::cout << p3 << std::endl;
  std::cout << p4 << std::endl;

  std::cout << "Size test" << std::endl;
  Size<int> s1(6, 2);
  Size<double> s2(3.32, 3.5);
  Size<int> s3 = s1 + s2;
  Size<double> s4;

  std::cout << s1 << std::endl;
  std::cout << s2 << std::endl;
  std::cout << s3 << std::endl;
  std::cout << s4 << std::endl;

  std::cout << "Rect test" << std::endl;
  Rect<double> r1(Point<double>(1, 12), Point<double>(3.2, 5.67));

  std::cout << r1 << std::endl;
  
  return 0;
}
