#pragma once

#include <cmath>
#include <numbers>

constexpr double PI = std::numbers::pi;
constexpr double EPS = 0.00001;

inline bool dbleq(double a, double b) { return abs(a - b) < EPS; }