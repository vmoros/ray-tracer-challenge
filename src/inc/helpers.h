#pragma once
#include <cmath>

inline bool dbleq(double a, double b) {
  const double eps = 0.0000001;
  return abs(a - b) < eps;
}