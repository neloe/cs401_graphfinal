//
/// \file lorenz.cpp
/// \author Nathan Eloe
/// \brief Implementation of lorenz system threadiness
//

#include "lorenz.h"

#include <iostream>
using namespace std;

point operator* (const double & s, const point& p)
{
  return {s * p.x, s * p.y, s * p.z};
}

point operator+ (const point& p1, const point& p2)
{
  return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

point& point::operator+= (const point& p)
{
  x += p.x;
  y += p.y;
  z += p.z;
  return *this;
}

std::ostream& operator << (std::ostream& o, const point& p)
{
  o << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return o;
}

double xdot (const point& p)
{
  return P * (p.y - p.x);
}

double ydot(const point& p)
{
  return R *  p.x - p.y - p.x * p.z;
}

double zdot(const point& p)
{
  return p.x * p.y - B * p.z;
}

void seq_step(point& p)
{
  point k_1 = DT * point({xdot(p), ydot(p), zdot(p)});
  point t1 = (0.5 * k_1) + p;
  point k_2 = DT * point({xdot(t1), ydot(t1), zdot(t1)});
  point t2 = (0.5 * k_2) + p;
  point k_3 = DT * point({xdot(t2), ydot(t2), zdot(t2)});
  point t3 = p + k_3;
  point k_4 = DT * point({xdot(t3), ydot(t3), zdot(t3)});
  p += (RKAVG * (k_1 + (2 * k_2) + (2 * k_3) + k_4));
  //cout << t1 << t2 << t3 << endl;
  //cout << k_1 << k_2 << k_3 << k_4 << p << endl;
  return;
}

double scaledot(dyn_var f, const point& p)
{
  return DT * f(p);
}

void launch_xyz(future<double>& fx, future<double>& fy, future<double>& fz, const point& p)
{
  fx = std::async(scaledot, xdot, p);
  fy = std::async(scaledot, ydot, p);
  fz = std::async(scaledot, zdot, p);
}

void launch_xy(future<double>& fx, future<double>& fy, const point& p)
{
  fx = std::async(scaledot, xdot, p);
  fy = std::async(scaledot, ydot, p);
}


void t1_step(point& p)
{
  static future<double> fx, fy, fz;
  launch_xyz (fx, fy, fz, p);
  point k_1 = {fx.get(), fy.get(), fz.get()};
  point t1 = (0.5 * k_1) + p;
  launch_xyz (fx, fy, fz, t1);
  point k_2 = {fx.get(), fy.get(), fz.get()};
  point t2 = (0.5 * k_2) + p;
  launch_xyz (fx, fy, fz, t2);
  point k_3 = {fx.get(), fy.get(), fz.get()};
  point t3 = p + k_3;
  launch_xyz (fx, fy, fz,t3);
  point k_4 = {fx.get(), fy.get(), fz.get()};
  p += (RKAVG * (k_1 + (2 * k_2) + (2 * k_3) + k_4));
  return;
}

void t2_step(point& p)
{
  static future<double> fx, fy;
  launch_xy (fx, fy, p);
  double z = scaledot(zdot, p);
  point k_1 = {fx.get(), fy.get(), z};
  point t1 = (0.5 * k_1) + p;
  launch_xy (fx, fy, p);
  z = scaledot(zdot, t1);
  point k_2 = {fx.get(), fy.get(), z};
  point t2 = (0.5 * k_2) + p;
  launch_xy (fx, fy, t2);
  z = scaledot(zdot, t2);
  point k_3 = {fx.get(), fy.get(), z};
  point t3 = p + k_3;
  launch_xy (fx, fy, t3);
  z = scaledot(zdot, t3);
  point k_4 = {fx.get(), fy.get(), z};
  p += (RKAVG * (k_1 + (2 * k_2) + (2 * k_3) + k_4));
  return;
}
