#include <pattern.h>
#include <shape.h>
#include <tuple.h>

#include <cmath>

// Pattern
Color Pattern::pattern_at_shape(const Shape* shape, Tuple point) const {
  Tuple object_point = shape->transformation_.inverse() * point;
  Tuple pattern_point = transformation_.inverse() * object_point;

  return pattern_at(pattern_point);
}

// StripePat

StripePat::StripePat(Color a, Color b) : a_(a), b_(b) {}

Color StripePat::pattern_at(Tuple point) const {
  if (static_cast<int>(floor(point.x_)) % 2 == 0) {
    return a_;
  }

  return b_;
}
