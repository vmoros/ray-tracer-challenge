#pragma once

#include <matrix.h>
#include <tuple.h>

class Ray {
 public:
  Ray(Tuple origin, Tuple direction);

  Tuple position(double t) const;
  Ray transform(Mat<4> mat) const;
  void print() const;

  Tuple origin_;
  Tuple direction_;
};
