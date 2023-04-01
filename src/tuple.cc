#include <tuple.h>

#include <cmath>

static bool dbleq(double a, double b) {
  const double eps = 0.0000001;
  return abs(a - b) < eps;
}

// Constructors/factories
Tuple::Tuple(double x, double y, double z, int w)
    : x_(x), y_(y), z_(z), w_(w) {}
Tuple Tuple::Point(double x_, double y_, double z_) { return {x_, y_, z_, 1}; }
Tuple Tuple::Vector(double x_, double y_, double z_) { return {x_, y_, z_, 0}; }

// Operators
Tuple Tuple::operator+(Tuple other) const {
  return {x_ + other.x_, y_ + other.y_, z_ + other.z_, w_ + other.w_};
}
Tuple Tuple::operator-(Tuple other) const {
  return {x_ - other.x_, y_ - other.y_, z_ - other.z_, w_ - other.w_};
}
Tuple Tuple::operator-() const { return {-x_, -y_, -z_, -w_}; }
bool Tuple::operator==(Tuple other) const {
  return dbleq(x_, other.x_) && dbleq(y_, other.y_) && dbleq(z_, other.z_) &&
         (w_ == other.w_);
}

// Misc
bool Tuple::isPoint() const { return w_ == 1; }
bool Tuple::isVector() const { return w_ == 0; }
