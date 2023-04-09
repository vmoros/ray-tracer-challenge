#pragma once

#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <tuple.h>

#include <optional>
#include <vector>

class Sphere;  // forward decl to make Intersection work

class Intersection {
 public:
  Intersection(double t, const Sphere& obj);
  static std::optional<Intersection> hit(
      std::vector<Intersection> intersections);
  bool operator==(const Intersection other) const;

  double t_;
  const Sphere& obj_;
};

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
