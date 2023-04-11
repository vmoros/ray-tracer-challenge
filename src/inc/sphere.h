#pragma once

#include <intersection.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <tuple.h>

#include <optional>
#include <vector>

class Sphere {
 public:
  // Constructors
  Sphere(Mat<4> transformation, Material material);
  Sphere(Mat<4> transformation);
  Sphere(Material material);
  Sphere();

  // Misc
  std::vector<Intersection> intersect(Ray r) const;
  bool operator==(Sphere other) const;
  Tuple normal_at(Tuple world_point) const;

  // Member variables
  Mat<4> transformation_;
  Material material_;
};
