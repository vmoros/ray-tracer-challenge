#pragma once
#include <cmath>

inline bool dbleq(double a, double b) {
  const double eps = 0.00001;
  return abs(a - b) < eps;
}