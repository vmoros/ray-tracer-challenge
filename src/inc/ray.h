#pragma once
#include <tuple.h>
class Ray {
 public:
  Ray(Tuple origin, Tuple direction);

  Tuple position(double t) const;

  Tuple origin_;
  Tuple direction_;
};
