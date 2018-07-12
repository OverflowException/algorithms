#include <iostream>
#include <cassert>

//Solve Ax = b with doolittle LU decomposition
//L matrix has 1 as diagonal elememts
//May need to check eigenvalue first, see if A is singular
//Could perform vector dot product in an individual function

template<class _T>
bool luDecomp(_T** A, size_t order)
{
  //Row, column and temporary index
  size_t row, col, temp;
  //In-place LU
  for(row = 0; row < order; ++row)
    {
      //Generating elements in L matrix
      for(col = 0; col < row; ++col)
	{
	  //Perform vector dot operation
	  for(temp = 0; temp < col; ++temp)
	    A[row][col] -= A[row][temp] * A[temp][row - 1];
	  A[row][col] /= A[col][col];
	}      

      //Generating elements in U matrix
      for(col = row; col < order; ++col)
	//Perform vector dot operation
	for(temp = 0; temp < row; ++temp)
	  A[row][col] -= A[row][temp] * A[temp][col];
    }
  
  return true;
}

template<class _T>
bool luSolve(_T** A, _T* x, _T* b, size_t order)
{
  
}


template<class _T>
void displayMat(_T** mat, size_t order)
{
  for(size_t row = 0; row < order; ++row)
    {
      for(size_t col = 0; col < order; ++col)
	std::cout << mat[row][col] << "\t";
      std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
  //Order of matrix
  size_t order = 3;
  //Allocate matrix
  float** mat = (float**)malloc(order * sizeof(float*));
  for(size_t row = 0; row < order; ++row)
    mat[row] = (float*)malloc(order * sizeof(float));
  //Assign elements
  mat[0][0] = 2;
  mat[0][1] = -1;
  mat[0][2] = -2;

  mat[1][0] = -4;
  mat[1][1] = 6;
  mat[1][2] = 3;

  mat[2][0] = -4;
  mat[2][1] = -2;
  mat[2][2] = 8;

  std::cout << "A = " << std::endl;
  displayMat(mat, order);
  luDecomp(mat, order);

  std::cout << "Combined LU = " << std::endl;
  displayMat(mat, order);  

  return 0;
}

