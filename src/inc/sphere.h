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
  // Constructors & assigners
  Intersection(double t, const Sphere* obj);

  // Misc
  static std::optional<Intersection> hit(
      const std::vector<Intersection>& intersections);
  bool operator==(const Intersection other) const;

  struct Comps {  // pre-computed values
    bool inside_;
    double t_;
    const Sphere* obj_;
    Tuple point_;
    Tuple over_point_;
    Tuple eyev_;
    Tuple normalv_;
  };

  Comps prepare_computations(Ray ray) const;

  // Member variables
  double t_;
  const Sphere* obj_;
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
