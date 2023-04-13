#pragma once

#include <intersection.h>
#include <shape.h>
#include <tuple.h>

#include <vector>

class Plane : public Shape {
 public:
  // Constructors
  Plane() = default;

  // Overrides
  std::vector<Intersection> local_intersect(Ray ray) const override;
  Tuple local_normal_at(Tuple point) const override;
  ~Plane() = default;
};