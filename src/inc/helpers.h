#pragma once
#include <cmath>
#include <numbers>

constexpr double PI = std::numbers::pi;

inline bool dbleq(double a, double b) {
  const double eps = 0.00001;
  return abs(a - b) < eps;
}