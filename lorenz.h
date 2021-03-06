//
/// \file lorenz.h
/// \author Nathan Eloe
/// \brief Functions to help in threading the lorenz system simulation
//

#pragma once

#include <future>
#include <iostream>
#include <string>
#include <unistd.h>

using std::future;

// Constants for system execution.  Chosen because that's what the original assignment
// writeup said
const double P = 10;
const double B = 8.0 / 3.0;
const double R = 10;
const double DT = 0.1;
const double RKAVG = 1.0 / 6.0;
struct point
{
  double x, y, z;
  point& operator += (const point& p);
};

//Basic math and output ops for point
point operator* (const double & s, const point& p);
point operator+ (const point& p1, const point& p2);
std::ostream& operator << (std::ostream& o, const point& p);

//Function pointer shenanigans, to make it easier to thread this guy
typedef double(*dyn_var)(const point &);

void launch_xyz(future<double>& fx, future<double>& fy, future<double>& fz, const point& p);
void launch_xy(future<double>& fx, future<double>& fy, const point& p);

//
/// \brief applies function f to the point and scales it by DT
/// \pre f not null
/// \post
/// \return DT * f(p)
//
double scaledot(dyn_var f, const point& p);

//
/// \brief dynamic variable functions for modelling the lorenz system for convection rolls
/// \pre None
/// \post None
/// \return result of evaluation
//
double xdot (const point& p);
double ydot (const point& p);
double zdot (const point& p);
//
/// \brief a single RK4 step, performed with different threading models
/// \pre None
/// \post None
/// \return new point after the RK4 step is performed
void seq_step(point& p);
void t1_step(point& p);
void t2_step(point& p);
