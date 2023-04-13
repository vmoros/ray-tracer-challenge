#pragma once

#include <intersection.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <shape.h>
#include <tuple.h>

#include <optional>
#include <vector>

class Sphere : public Shape {
 public:
  // Constructors
  Sphere(Mat<4> transformation, Material material);
  Sphere(Mat<4> transformation);
  Sphere(Material material);
  Sphere();

  // Misc
  bool operator==(Sphere other) const;

  // Member variables come from Shape

  // Overrides
  std::vector<Intersection> local_intersect(Ray ray) const override;
  Tuple local_normal_at(Tuple point) const override;
  ~Sphere() = default;
};
