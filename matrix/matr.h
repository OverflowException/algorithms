#ifndef _MATR_H
#define _MATR_H

namespace imgalg
{  
  template<typename _T>
    class Matr
    {
    public:
      typedef _T value_type;
      Matr(int row = 0, int col = 0) : _row(row), _col(col)
      {
	
      }


      ~Mat();

      //element access
      inline value_type& at(int row, int col)
      { return *(_row_head + _ele_step * sizeof(value_type)); }
      
      
    private:
      int _row;      //Total rows and columns of this matrix
      int _col;

      value_type* _data_head; //
      value_type** _row_head;

      value_type* _data_ptr;
      value_type** _row_ptr;
      
      int _line_step;
      int _ele_step;
    }
}


#endif
