// 
/// \file driver.cpp
/// \author Nathan Eloe
/// \brief Driver to time different threading models for simulating the lorenz models
//

#include "lorenz.h"
#include "timer.h"
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

typedef void(*step_func)(point &);

const point START = {1.0, 1.0, 1.0};
const unsigned int ITER = 10000;

double time_func(step_func f, point& p);

int main()
{
  point p = START;
  cout << "Sequential: " << time_func(seq_step, p) << "s; " << p << endl;
  p = START;
  cout << "Threaded 1: " << time_func(t1_step, p) << "s; " << p << endl;
  p = START;
  cout << "Threaded 2: " << time_func(t2_step, p) << "s; " << p << endl;
  return 0;
}

double time_func(step_func f, point& p)
{
  //cout << "sockets created" << endl;
  timer t;
  for (int i=0; i<ITER; i++)
    f(p);
  t.end();
  return t.read(); 
}
