/* -*- mode: c++; c-basic-offset: 2; -*- vim: set sw=2 tw=70 et sta ai: */
#ifndef LIBAD_H
#define LIBAD_H

#include <iostream>
#include <cmath>
#include <cassert>

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

  // There will  be no bounds  checking "in production", so  it should
  // better be private:
  real
  operator[] (int i) const
  {
    assert (i == 0 or i == 1);
    return this->v[i];
  }

 public:

  // FIXME: we do not specialize operations for (AD + real) or (real -
  // AD).  For the  moment we rely on the  argument conversion to lift
  // literal numbers to full blown AD constant. Add "explicit" here to
  // get an idea of missing specializations:
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
    return AD (x[0] + y[0],
               x[1] + y[1]);
  }

  friend AD
  operator- (const AD &x, const AD &y)
  {
    return AD (x[0] - y[0],
               x[1] - y[1]);
  }

  friend AD
  operator* (const AD &x, const AD &y)
  {
    return AD (x[0] * y[0],
               x[0] * y[1] + x[1] * y[0]);
  }

  // Should it be private?
  friend AD
  recip (const AD &x)
  {
    return AD (1 / x[0],
               - x[1] / (x[0] * x[0]));
  }

  friend AD
  operator/ (const AD &x, const AD &y)
  {
    return x * recip (y);
  }

  friend AD
  sin (const AD &x)
  {
    return AD (sin (x[0]),
               cos (x[0]) * x[1]);
  }

  friend AD
  cos (const AD &x)
  {
    return AD (cos (x[0]),
               - sin (x[0]) * x[1]);
  }

  friend AD
  tan (const AD &x)
  {
    const real t = tan (x[0]);
    return AD (t,
               x[1] * (1 + t * t));
  }

  friend AD
  atan (const AD &x)
  {
    return AD (atan (x[0]),
               x[1] / (1 + x[0] * x[0]));
  }

  friend AD
  exp (const AD &x)
  {
    const real e = exp (x[0]);
    return AD (e,
               e * x[1]);
  }

  friend AD
  log (const AD &x)
  {
    return AD (log (x[0]),
               x[1] / x[0]);
  }

  friend AD
  sqrt (const AD &x)
  {
    const real y = sqrt (x[0]);
    return AD (y,
               x[1] / (2 * y));
  }

  // Specializaton  for pow  (AD, real)  is probably  most  used, more
  // general version pow (AD, AD) below:
  friend AD
  pow (const AD &x, real y)
  {
    const real z = pow (x[0], y);
    return AD (z,
               (y / x[0]) * x[1] * z);
  }

  friend AD
  pow (const AD &x, const AD &y)
  {
    const real z = pow (x[0], y[0]);
    return AD (z,
               (y[1] * log (x[0]) + (y[0] / x[0]) * x[1]) * z);
  }

  // For debug printing only:
  friend std::ostream
  &operator<< (std::ostream &stream, const AD &x)
  {
    return stream << "{" << x[0] << ", " << x[1] << "}";
  }
};

#endif  // ifndef LIBAD_H
