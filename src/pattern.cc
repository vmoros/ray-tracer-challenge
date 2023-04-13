#include <pattern.h>
#include <shape.h>
#include <tuple.h>

#include <cmath>

StripePat::StripePat(Color a, Color b) : a_(a), b_(b) {}

Color StripePat::stripe_at(Tuple point) const {
  if (static_cast<int>(floor(point.x_)) % 2 == 0) {
    return a_;
  }

  return b_;
}

Color StripePat::stripe_at_object(Shape& object, Tuple point) const {
  Tuple object_point = object.transformation_.inverse() * point;
  Tuple pattern_point = transformation_.inverse() * object_point;

  return stripe_at(pattern_point);
}
