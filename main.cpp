/* -*- mode: c++; c-basic-offset: 2; -*- vim: set sw=2 tw=70 et sta ai: */
#include <iostream>
#include "libad.hpp"

//
// This is the example used in libtaylor.
//
// Compute a  directional derivative of  f(x, y) in the  direction (1,
// 2), at point (x, y) =  (3, 4).  This is equivalent to computing the
// taylor expansion of f(3+1*eps, 4+2*eps) in the variable eps.
//
// Reference output for the value and directional derivatives:
//
// {9.88847, 50.2665, -10558.6, -666560, 1.20363e+08, 9.72153e+09}
//
template<class T>
T f2(const T &x, const T &y)
{
  return sin (log (7 * x) + exp (y)) + 9;
}

template<class T>
T f1 (const T &eps)
{
  return f2 (3 + eps, 4 + 2 * eps);
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
  cout << x << " * " << 100 << " = " << x * 100 << endl;
  cout << x << " * " << x << " = " << x * x << endl;
  cout << "pow(" << x << ", 2) = " << pow (x, 2) << endl;
  cout << "sqrt(" << x << ") = " << sqrt (x) << endl;
  cout << "sqrt(pow(" << x << ", 2)) = " << sqrt (pow (x, 2)) << endl;
  cout << "pow(sqrt(" << x << "), 2) = " << pow (sqrt (x), 2) << endl;
  cout << "recip(" << x << ") = " << recip (x) << endl;
  cout << 1 << " / " << x << ") = " << 1 / x << endl;
  cout << y << " / " << x << ") = " << y / x << endl;
  cout << x << " / " << x << ") = " << x / x << endl;
  cout << "exp(" << x << ") = " << exp (x) << endl;
  cout << "log(" << x << ") = " << log (x) << endl;
  cout << "log(exp(" << x << ")) = " << log (exp (x)) << endl;
  cout << "exp(log(" << x << ")) = " << exp (log (x)) << endl;
  cout << "sin(" << x << ") = " << sin (x) << endl;
  cout << "cos(" << x << ") = " << cos (x) << endl;
  cout << "tan(" << x << ") = " << tan (x) << endl;
  cout << "tan(" << x << ") = " << sin (x) / cos (x) << endl;
  cout << "atan(tan(" << x << ")) = " << atan (tan (x)) << endl;
  cout << "tan(atan(" << x << ")) = " << tan (atan (x)) << endl;
  {
    AD eps = AD::var (0.0);
    cout << "f1(" << eps << ") = " << f1 (eps) << endl;
  }
}
