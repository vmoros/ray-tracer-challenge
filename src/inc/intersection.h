#pragma once

#include <sphere.h>

class Intersection {
 public:
  Intersection(double t, Sphere obj);

  double t_;
  Sphere obj_;
};