#include <iostream>
#include "matr.h"

using namespace imgalg;
using namespace std;  

int main(int argc, char** argv)
{
  Matr<float> m1(Size<int>(7, 5));
  for(int row = 0; row < m1.row(); ++row)
    for(int col = 0; col < m1.col(); ++col)
      m1.at(row, col) = row * col;
  
  Matr<float> m2, m3;
  m2 = m1(Rect<int>(0, 0, 5, 2));
  m1(Rect<int>(0, 0, 5, 2)).copyTo(m3);
  
  cout << "rows:" << endl;
  cout << m1.ptr(0) << "\n"
       << m2.ptr(0) << "\n"
       << m3.ptr(0) << endl;

  m2.at(0, 0) = -100;
  m2.ptr(0)[1] = -90;
  
  cout << m1 << endl;
  cout << m2 << endl;
  cout << m3 << endl;

  
  
  return 0;
}
