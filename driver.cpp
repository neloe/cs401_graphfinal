// 
/// \file driver.cpp
/// \author Nathan Eloe
/// \brief Driver to time different threading models for simulating the lorenz models
//

#include "lorenz.h"
#include "timer.h"
#include <iostream>

using namespace std;

typedef void(*step_func)(point &);

const point START = {1.0, 1.0, 1.0};
const unsigned int ITER = 100000;

double time_func(step_func f, point& p);

int main()
{
  point p = START;
  cout << "Sequential: " << time_func(seq_step, p) << "s; " << p << endl; 
  return 0;
}

double time_func(step_func f, point& p)
{
  timer t;
  for (int i=0; i<ITER; i++)
    f(p);
  t.end();
  return t.read(); 
}
