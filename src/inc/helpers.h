#pragma once

#include <cmath>
#include <limits>
#include <numbers>

constexpr double PI = std::numbers::pi;
constexpr double EPS = 0.00001;
constexpr double INFTY = std::numeric_limits<double>::infinity();

inline bool dbleq(double a, double b) { return std::abs(a - b) < EPS; }
inline auto sqr(auto a) { return a * a; }