#ifndef _GEO_UTILITY_H
#define _GEO_UTILITY_H

#include <iostream>

namespace imgalg
{
  template<typename _T>
    class Point
    {
    public:
      //ctors, default copy ctor
      Point() : x(_T(0)), y(_T(0)){};
      Point(const _T& x, const _T& y) : x(x), y(y){}

      Point& operator=(const Point& p);
      Point operator+(const Point& p) const;
      Point operator-(const Point& p) const;
      Point& operator+=(const Point& p);
      Point& operator-=(const Point& p);
      
      friend std::ostream& operator<<(std::ostream& os, const Point& p)
	{
	  os << "(" << p.x <<", " << p.y << ")"; 
	}
      
      _T x;
      _T y;
    };

  template<typename _T>
    class Size
    {
    public:
      //ctors, default copy ctor
      Size() : width(_T(0)), height(_T(0)){}
      Size(const _T& w, const _T& h) : width(w), height(h){}
      Size(const Point<_T>& p1, const Point<_T>& p2)
	{
	  _T x_diff = p1.x - p2.x;
	  _T y_diff = p1.y - p2.y;
	  width = x_diff < 0 ? 0 - x_diff : x_diff;
	  height = y_diff < 0 ? 0 - y_diff : y_diff;
	}
      
      Size& operator=(const Size& s);
      Size operator+(const Size& s) const;
      Size operator-(const Size& s) const;
      Size& operator+=(const Size& s);
      Size& operator-=(const Size& s);

      friend std::ostream& operator<<(std::ostream& os, const Size& s)
      {
	os << "[" << s.width <<", " << s.height << "]";
      }
      
      _T width;
      _T height;
    };
  
  template<typename _T>
    class Rect
    {
    public:
      //ctors, default copy ctors
      Rect() : x(_T(0)), y(_T(y)), width(_T(0)), height(_T(0)){}
      Rect(_T x, _T y, _T w, _T h) : x(x), y(y), width(w), height(h){}
      Rect(const Point<_T> p1, const Point<_T> p2);
      
      Point<_T> tl() const { return Point<_T>(x, y); }
      Point<_T> br() const { return Point<_T>(x + width, y + height); }
      Size<_T> size() const { return Size<_T>(width, height); }
      
      friend std::ostream& operator<<(std::ostream& os, const Rect& r)
      {
	os << "{(" << r.x <<", " << r.y << "), "
	   << "[" << r.width << ", " << r.height << "]}";
      }

      _T x;
      _T y;
      _T width;
      _T height;
    };
  

  //Point member function definitions
  template<typename _T>
    Point<_T>& Point<_T>::operator=(const Point<_T>& p)
    {
      x = p.x; y = p.y;
      return *this;
    }

  template<typename _T>
    Point<_T> Point<_T>::operator+(const Point<_T>& p) const
    {
      Point<_T> res(x, y);
      res.x += p.x; res.y += p.y;
      return res;
    }
  
  template<typename _T>
    Point<_T> Point<_T>::operator-(const Point<_T>& p) const
    {
      Point<_T> res(x, y);
      res.x -= p.x; res.y -= p.y;
      return res;
    }

  template<typename _T>
    Point<_T>& Point<_T>::operator+=(const Point<_T>& p)
    {
      x += p.x; y += p.y;
      return *this;
    }
  
  template<typename _T>
    Point<_T>& Point<_T>::operator-=(const Point<_T>& p)
    {
      x -= p.x; y -= p.y;
      return *this;
    }

  //Size member function definitions
    template<typename _T>
    Size<_T>& Size<_T>::operator=(const Size<_T>& s)
    {
      width = s.width; height = s.height;
      return *this;
    }

  template<typename _T>
    Size<_T> Size<_T>::operator+(const Size<_T>& s) const
    {
      Size<_T> res(width, height);
      res.width += s.width; res.height += s.height;
      return res;
    }
  
  template<typename _T>
    Size<_T> Size<_T>::operator-(const Size<_T>& p) const
    {
      Size<_T> res(width, height);
      res.width -= p.width; res.height -= p.height;
      return res;
    }

  template<typename _T>
    Size<_T>& Size<_T>::operator+=(const Size<_T>& p)
    {
      width += p.width; height += p.height;
      return *this;
    }
  
  template<typename _T>
    Size<_T>& Size<_T>::operator-=(const Size<_T>& p)
    {
      width -= p.width; height -= p.height;
      return *this;
    }


  //Rect member function
  template<typename _T>
    Rect<_T>::Rect(Point<_T> p1, Point<_T> p2)
    {
      x = p1.x < p2.x ? p1.x : p2.x;
      y = p1.y < p2.y ? p1.y : p2.y;
      _T x_diff = p1.x - p2.x;
      _T y_diff = p1.y - p2.y;
      width = x_diff < 0 ? 0 - x_diff : x_diff;
      height = y_diff < 0 ? 0 - y_diff : y_diff;
    }
}

#endif
