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
#include <iomanip>
using namespace std;

typedef void(*step_func)(point &);

const point START = {1.0, 1.0, 1.0};
const unsigned int ITER = 10000;

const int ITERS[] = {1,10,100,1000,10000};

double time_func(step_func f, point& p, const int runs);

int main()
{
  cout << left;
  cout.precision(4);
  cout.setf(ios::floatfield);
  point p1, p2, p3;
  cout << setw(10) << "#Iters"
       << setw(10) << "Seq"
       << setw(10) << "Thread1"
       << setw(10) << "Thread2" << endl;
  for(int r: ITERS)
  {
    p1=p2=p3=START;
    cout << setw(10) << r << setw(10) << time_func(seq_step, p1, r) << setw(10)
                      << time_func(t1_step,  p2, r) << setw(10)
                      << time_func(t2_step,  p3, r) << "\n";
  }
  return 0;
}

double time_func(step_func f, point& p, const int runs)
{
  //cout << "sockets created" << endl;
  timer t;
  for (int i=0; i<runs; i++)
    f(p);
  t.end();
  return t.read(); 
}
