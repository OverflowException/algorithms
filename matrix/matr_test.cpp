#include <iostream>
#include "matr.h"

using namespace imgalg;
using namespace std;  

int main(int argc, char** argv)
{
  Matr<float> m1(5, 5);
  for(int row = 0; row < m1.row(); ++row)
    for(int col = 0; col < m1.col(); ++col)
      m1.at(row, col) = row * col;
  Matr<float> m2 = m1(Rect<int>(1, 1, 3, 4));
  Matr<float> m3(m2.size());
  m2.copyTo(m3);  

  cout << "rows:" << endl;
  cout << m1.ptr(1) << "\n"
       << m2.ptr(1) << "\n"
       << m3.ptr(1) << endl;

  cout << "row pointers:" << endl;
  cout << m1.debug_row_ptrs() << "\n"
       << m2.debug_row_ptrs() << "\n"
       << m3.debug_row_ptrs() << endl;

  m2.at(0, 0) = -100;

  
  cout << m1 << endl;
  cout << m2 << endl;
  cout << m3 << endl;
  
  return 0;
}
