#pragma once

#include <intersection.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <tuple.h>

#include <vector>
class Shape {  // abstract parent class for all shapes e.g. Sphere
 public:
  // Constructors
  Shape(Mat<4> transformation, Material material);
  Shape() = default;

  // Misc
  std::vector<Intersection> intersect(Ray r) const;
  Tuple normal_at(Tuple point) const;

  // Member variables
  Mat<4> transformation_;
  Material material_;

  // Virtual functions
  virtual std::vector<Intersection> local_intersect(Ray r) const = 0;
  virtual Tuple local_normal_at(Tuple point) const = 0;
  virtual ~Shape() = default;
};