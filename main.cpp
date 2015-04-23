/* -*- mode: c++; c-basic-offset: 2; -*- vim: set sw=2 tw=70 et sta ai: */
#include <iostream>

class AD
{
  // Use  real  type for  numbers  below, as  if  it  were a  template
  // parameter:
  typedef double real;

  // C++11 initialization  here, supply -std=c++11  to get rid  of the
  // warning:
  real v[2] = {0.0, 0.0};

  // User is  not supposed to  construct arbitrary AD  instances, keep
  // the  constructor private.  Use  AD::var() and  AD::fix() instead.
  // One argument constructor for  lifting literal constants is public
  // though (see comments below).
  AD (real v0, real v1): v{v0, v1} {}

  // No bounds checking, so it should better be private:
  real
  operator[] (int i) const
  {
    return this->v[i];
  }

 public:

  // FIXME:  we do  not specialize  operations  for (AD  + number)  or
  // (number - AD).  For the moment we rely on the argument conversion
  // to lift literal numbers to full blown AD constant:
  AD (real x): v{x, 0.0} {}

  // Independent variable with unit slope:
  static AD
  var (real x)
  {
    return AD (x, 1.0);
  }

  // Constant   with  zero   slope.  FIXME:   Duplicates  one-argument
  // constructor.
  static AD
  fix (real x)
  {
    return AD (x, 0.0);
  }

  // Public  accessors   for  the  value  and   the  first  derivative
  // follow. If you make them static, you will have to qualify them as
  // in  AD::fst(x).   Rely   on  argument-dependent  lookup  instead.
  // FIXME: how to avoid qualifying AD::var() and AD::fix(U)?
  friend real
  val (const AD &x)
  {
    return x[0];
  }

  friend real
  fst (const AD &x)
  {
    return x[1];
  }

  friend AD
  operator+ (const AD &x, const AD &y)
  {
    return AD (x[0] + y[0], x[1] + y[1]);
  }

  friend AD
  operator- (const AD &x, const AD &y)
  {
    return AD (x[0] - y[0], x[1] - y[1]);
  }

  // For debug printing only:
  friend std::ostream
  &operator<< (std::ostream &stream, const AD &x)
  {
    return stream << "{" << x[0] << ", " << x[1] << "}";
  }
};

template<class T>
T func (const T &x)
{
  return x;
}

int main ()
{
  using std::cout;
  using std::endl;

  AD x = AD::var (2);
  AD y = AD::fix (10);
  cout << x << " + " << y << " = " << x + y << endl;
  cout << x << " - " << y << " = " << x - y << endl;
  cout << 1 << " - " << y << " = " << 1 - y << endl;
  cout << x << " + " << 100 << " = " << x + 100 << endl;
}
