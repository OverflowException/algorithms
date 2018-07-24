#ifndef _MATR_H
#define _MATR_H

#include "geo_utility.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <array>

namespace imgalg
{
  
  template<typename _T>
    class Matr
    {
    public:
      typedef _T value_type;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
      typedef value_type& reference;
      typedef const value_type& const_reference;
      
      //ctors
      Matr()
	: _row(0), _col(0), _row_step(0),
	_data_ptr(static_cast<value_type*>(NULL)),
	_row_ptrs(static_cast<pointer*>(NULL)){}
      
      Matr(int row, int col);
      
      Matr(const Size<int>& sz)
	: Matr(sz.height, sz.width){}
	
      Matr(const Matr& mat)
	: _row(mat._row), _col(mat._col), _row_step(mat._row_step),
	_data_ptr(mat._data_ptr),
	_row_ptrs(mat._row_ptrs){ std::cout << "Copy constructor called!" << std::endl; }
      
      //dtor
      ~Matr() = default;

      inline int row() const { return _row; }
      inline int col() const { return _col; }
      inline Size<int> size() const { return Size<int>(_col, _row); }
      
      Matr& operator=(const Matr& mat);
      //Set ROI
      Matr operator()(const Rect<int>& roi) const;
      
      //Read only element access
      inline const_reference at(int row, int col) const { return _row_ptrs.get()[row][col]; }
      //Read/write element access
      inline reference at(int row, int col) { return _row_ptrs.get()[row][col]; }


      //No need to return const, since this function returns pointer value, not reference
      inline pointer ptr(int row) const { return _row_ptrs.get()[row]; }
      
      friend std::ostream& operator<<(std::ostream& os, const Matr& mat)
      {
	int r_idx, c_idx;
	pointer row_ptr;
	os << "[\n";
	for(r_idx = 0; r_idx < mat._row; ++r_idx)
	  {
	    row_ptr = mat._row_ptrs.get()[r_idx];
	    for(c_idx = 0; c_idx < mat._col; ++c_idx)
	      os << row_ptr[c_idx] << ", ";
	    os << "\n";
	  }
	os << "]";
      }
      
      void copyTo(Matr& mat) const;      
      
    private:
      int _row;      //Total rows and columns of this matrix
      int _col;

      int _row_step;
      
      std::shared_ptr<value_type> _data_ptr; //Pointer to data
      std::shared_ptr<pointer> _row_ptrs; //Pointer to each row
    };

  template<typename _T>
    Matr<_T>::Matr(int row, int col)
    : _row(row), _col(col), _row_step(col),
    _data_ptr(new value_type[_row * _col], std::default_delete<value_type[]>())
    {
      pointer* temp_ptrs = new pointer[row];
      int r_idx = 0;
      pointer ptr = _data_ptr.get();
      for(; r_idx < row; ++r_idx, ptr += col)
	temp_ptrs[r_idx] = ptr;

      _row_ptrs.reset(temp_ptrs, std::default_delete<pointer[]>());
    }
  
  template<typename _T>
    Matr<_T>& Matr<_T>::operator=(const Matr<_T>& mat)
    {
      std::cout << "Operator= called!" <<std::endl;

      _row = mat._row;
      _col = mat._col;
      _row_step = mat._row_step;

      _data_ptr = mat._data_ptr;
      _row_ptrs = mat._row_ptrs;
      
      return *this;
    }
  
  template<typename _T>
    Matr<_T> Matr<_T>::operator()(const Rect<int>& roi) const
    {      
      Matr<_T> mat;

      mat._row = roi.height;
      mat._col = roi.width;
      mat._row_step = _row_step;

      mat._data_ptr = _data_ptr;
      pointer* temp_ptrs = new pointer[roi.height];
      for(int r_idx = 0; r_idx < roi.height; ++r_idx)
	temp_ptrs[r_idx] = _row_ptrs.get()[r_idx + roi.y] + roi.x;
      mat._row_ptrs.reset(temp_ptrs, std::default_delete<pointer[]>());
      
      return mat;
    }
  
  template<typename _T>
    void Matr<_T>::copyTo(Matr<_T>& dst) const
    {
      pointer src_row_ptr = _row_ptrs.get()[0];
      pointer dst_row_ptr = NULL;
      
      //dst and src matrices' _data_ptr's object are not the same size
      //dst matrix's _data_ptr's object is shared
      //assign new object to dst matrix's _data_ptr
      if(dst._row * dst._col != _row * _col || dst._data_ptr.use_count() > 1)
	{
	  std::cout << "_data_ptr reassigned! "
		    << dst._row << "x" << dst._col << " -> " << _row << "x" << _col
		    << std::endl;
	  dst._data_ptr.reset(new value_type[_row * _col], std::default_delete<value_type[]>());
	}
      dst_row_ptr = dst._data_ptr.get();
      
      //dst and src matrices' _row_ptrs' object are not the same size
      //dst matrix's _row_ptrs' object is shared
      //assign new object to dst matrix's _row_ptrs
      if(dst._row != _row || dst._row_ptrs.use_count() > 1)
	{
	  std::cout << "_row_ptrs reassigned! " << dst._row << " -> " << _row << std::endl;
	  dst._row_ptrs.reset(new pointer[_row], std::default_delete<pointer[]>());
	}
      
      int r_idx = 0;
      do
	{
	  //Copy _data_ptr
	  std::copy(src_row_ptr, src_row_ptr + _col, dst_row_ptr);
	  //Assign dst._row_ptrs
	  dst._row_ptrs.get()[r_idx] = dst_row_ptr;
	  
	  src_row_ptr += _row_step;
	  dst_row_ptr += _col;
	}while(++r_idx < _row);

      dst._row = _row;
      dst._col = _col;
      dst._row_step = dst._col;
      
      return;
    }
}

#endif
