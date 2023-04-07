#pragma once

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
  Sphere();
  Sphere(Mat<4> transformation);

  std::vector<Intersection> intersect(Ray r) const;
  bool operator==(Sphere other) const;

  Mat<4> transformation_;
};
