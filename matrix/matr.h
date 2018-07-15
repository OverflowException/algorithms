#ifndef _MATR_H
#define _MATR_H

#include "geo_utility.h"
#include <algorithm>
#include <iostream>

namespace imgalg
{  
  template<typename _T>
    class Matr
    {
    public:
      typedef _T value_type;
      //ctors
      Matr() : _row(0), _col(0), _row_step(0), _data_ptr(NULL), _row_ptrs(NULL){};
      Matr(int row, int col);
      Matr(const Size<int>& sz);
      Matr(const Matr& mat);
      //dtor
      ~Matr();

      inline int row() const { return _row; }
      inline int col() const { return _col; }
      inline Size<int> size() const { return Size<int>(_col, _row); }
      
      Matr& operator=(const Matr& mat);
      //Set ROI
      Matr operator()(const Rect<int>& roi) const;
      
      //Read only element access
      inline const _T& at(int row, int col) const { return _row_ptrs[row][col]; }
      //Read/write element access
      inline _T& at(int row, int col) { return _row_ptrs[row][col]; }
      
      inline const _T* ptr(int row) const { return _row_ptrs[row]; }
      inline _T* ptr(int row) { return _row_ptrs[row]; }
      
      //////////////////////
      inline _T** debug_row_ptrs() { return _row_ptrs; }
      //////////////////////

      
      friend std::ostream& operator<<(std::ostream& os, const Matr& mat)
      {
	int r_idx, c_idx;
	os << "[\n";
	for(r_idx = 0; r_idx < mat._row; ++r_idx)
	  {
	    for(c_idx = 0; c_idx < mat._col; ++c_idx)
	      os << mat._row_ptrs[r_idx][c_idx] << ", ";
	    os << "\n";
	  }
	os << "]";
      }
      
      void copyTo(Matr& mat) const;
      
      
    private:
      void _allocate_all(int row, int col);
      void _deallocate_all();
      
      int _row;      //Total rows and columns of this matrix
      int _col;

      int _row_step;
      
      _T* _data_ptr; //Pointer to data, NULL means this Matr is not the one that allocates memory in the first place
      _T** _row_ptrs; //Pointer to each row
    };

  template<typename _T>
    Matr<_T>::Matr(int row, int col) : _row(row), _col(col), _row_step(col)
    {
      _allocate_all(row, col);	
    }

  template<typename _T>
    Matr<_T>::Matr(const Size<int>& sz)
    {
      _allocate_all(sz.height, sz.width);
    }

  
  template<typename _T>
    Matr<_T>::Matr(const Matr& mat)
    {
      //////////
      std::cout << "Copy constructor called!" << std::endl;
      _data_ptr = NULL;
      _row_ptrs = new _T*[mat._row];
      std::copy(mat._row_ptrs, mat._row_ptrs + mat._row, _row_ptrs);
      
      _row = mat._row;
      _col = mat._col;
      _row_step = mat._row_step;
    }

  template<typename _T>
    Matr<_T>::~Matr()
    {
      _deallocate_all();
    }

  template<typename _T>
    Matr<_T>& Matr<_T>::operator=(const Matr<_T>& mat)
    {
      std::cout << "operator= called!" << std::endl;
      delete[] _data_ptr;
      _data_ptr = NULL;

      if(_row < mat._row)
	{
	  delete[] _row_ptrs;
	  _row_ptrs = new _T*[mat._row];
	}	
      std::copy(mat._row_ptrs, mat._row_ptrs + mat._row, _row_ptrs);

      _row = mat._row;
      _col = mat._col;
      _row_step = mat._row_step;

      return *this;
    }
  
  template<typename _T>
    Matr<_T> Matr<_T>::operator()(const Rect<int>& roi) const
    {      
      Matr<_T> mat;
      mat._row = roi.height;
      mat._col = roi.width;
      mat._row_step = _row_step;

      mat._row_ptrs = new _T*[roi.height];
      for(int r_idx = 0; r_idx < roi.height; ++r_idx)
	mat._row_ptrs[r_idx] = _row_ptrs[r_idx + roi.y] + roi.x;

      return mat;
    }
  
  template<typename _T>
    void Matr<_T>::copyTo(Matr<_T>& dst) const
    {
      //mat is a fully allocated matrix, and happens to have the same size as *this
      if(dst._row == _row && dst._col == _col && dst._data_ptr != NULL);
      else
	{
	  dst._deallocate_all();
	  dst._allocate_all(_row, _col);
	}
      
      int r_idx = 0;
      _T* src_row_ptr = _row_ptrs[0];
      _T* dst_row_ptr = dst._data_ptr;
      do
	{
	  //Copy _data_ptr
	  std::copy(src_row_ptr, src_row_ptr + _col, dst_row_ptr);
	  //Assign dst._row_ptrs
	  dst._row_ptrs[r_idx] = dst_row_ptr;
	  
	  src_row_ptr += _row_step;
	  dst_row_ptr += dst._row_step;
	}while(++r_idx < _row);
            
      return;
    }

  template<typename _T>
    void Matr<_T>::_deallocate_all()
    {
      _row = 0;
      _col = 0;
      _row_step = 0;
      
      delete[] _row_ptrs;
      _row_ptrs = NULL;
      delete[] _data_ptr;
      _data_ptr = NULL;
    }

  template<typename _T>
    void Matr<_T>::_allocate_all(int row, int col)
    {
      _data_ptr = new _T[row * col];
      _row_ptrs = new _T*[row];

      int r_idx;
      _T* ptr = NULL;
      for(r_idx = 0, ptr = _data_ptr; r_idx < row; ++r_idx, ptr += col)
	_row_ptrs[r_idx] = ptr;

      _row = row;
      _col = col;
      _row_step = col;

    }
}

#endif
