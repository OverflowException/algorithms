#ifndef _GEO_UTILITY_H
#define _GEO_UTILITY_H

#include <ostream>

namespace imgalg
{
  template<typename _T>
    class Point
    {
    public:
      typedef _T value_type;
      //ctors
      Point() = default;
      Point(const _T& x, const _T& y) : x(x), y(y){}
      template<typename _Tp>
	Point(const Point<_Tp>& p) : x(_T(p.x)), y(_T(p.y)){}

      //Default operator=
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
      typedef _T value_type;
      //ctors
      Size() = default;
      Size(const _T& w, const _T& h) : width(w), height(h){}
      template<typename _Tp>
	Size(const Size<_Tp>& sz) : width(_T(sz.width)), height(_T(sz.height)){}
      Size(const Point<_T>& p1, const Point<_T>& p2)
	{
	  _T x_diff = p1.x - p2.x;
	  _T y_diff = p1.y - p2.y;
	  width = x_diff < 0 ? 0 - x_diff : x_diff;
	  height = y_diff < 0 ? 0 - y_diff : y_diff;
	}

      //Default operator=
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
      typedef _T value_type;
      //ctors
      Rect() = default;
      Rect(_T x, _T y, _T w, _T h) : x(x), y(y), width(w), height(h){}
      Rect(const Point<_T> p1, const Point<_T> p2);
      template<typename _Tp>
	Rect(const Rect<_Tp>& r) : x(_T(r.x)), y(_T(r.y)), width(_T(r.width)), height(_T(r.height)){}

      
      //Default operator=
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
