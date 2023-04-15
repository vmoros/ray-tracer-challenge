#pragma once

#include <ray.h>
#include <tuple.h>

#include <optional>

class Shape;  // forward decl to make Intersection work
              // Shape and Intersection have a cyclic dependency so Shape
              // in the Intersection class must always be by pointer

class Intersection {
 public:
  // Constructors & assigners
  Intersection(double t, const Shape* obj);

  // Misc
  static std::optional<Intersection> hit(
      const std::vector<Intersection>& intersections);
  bool operator==(const Intersection other) const;

  struct Comps {  // pre-computed values
    bool inside_;
    double t_;
    const Shape* obj_;
    Tuple point_;
    Tuple over_point_;
    Tuple eyev_;
    Tuple normalv_;
    Tuple reflectv_;
  };

  Comps prepare_computations(Ray ray) const;

  // Member variables
  double t_;
  const Shape* obj_;
};