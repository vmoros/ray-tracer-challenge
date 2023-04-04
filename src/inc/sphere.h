#pragma once

#include <ray.h>
#include <tuple.h>

#include <vector>

class Sphere {
 public:
  Sphere();
  std::vector<double> intersect(Ray r) const;
  bool operator==(Sphere other) const;

  Tuple center_;
  double radius_;
};
