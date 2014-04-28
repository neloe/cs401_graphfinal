//
/// \file lorenz.cpp
/// \author Nathan Eloe
/// \brief Implementation of lorenz system threadiness
//

#include "lorenz.h"

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
  p += (1.0 / 6.0 * (k_1 + (2 * k_2) + (2 * k_3) + k_4));
  return;
}

