#include <pattern.h>
#include <shape.h>
#include <tuple.h>

#include <cmath>

Pattern::Pattern(Mat<4> transformation) : inverse_(transformation.inverse()) {}

// Pattern
Color Pattern::pattern_at_shape(const Shape* shape, Tuple point) const {
  Tuple object_point = shape->inverse_ * point;
  Tuple pattern_point = inverse_ * object_point;

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

Color GradientPat::pattern_at(Tuple point) const {
  auto distance = b_ - a_;
  auto fraction = point.x_ - floor(point.x_);

  return a_ + distance * fraction;
}

Color RingPat::pattern_at(Tuple point) const {
  double hyp = sqrt(point.x_ * point.x_ + point.z_ * point.z_);
  if (static_cast<int>(floor(hyp)) % 2 == 0) {
    return a_;
  }

  return b_;
}

Color CheckerPat::pattern_at(Tuple point) const {
  double hyp = floor(point.x_) + floor(point.y_) + floor(point.z_);
  if (static_cast<int>(hyp) % 2 == 0) {
    return a_;
  }

  return b_;
}
