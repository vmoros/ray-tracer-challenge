#pragma once

#include <ray.h>
#include <tuple.h>

#include <optional>
#include <vector>

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
  bool operator==(const Intersection& other) const = default;

  struct Comps {  // pre-computed values
    bool inside_{};
    double t_{};
    double n1_{};
    double n2_{};
    const Shape* obj_{};
    Tuple point_;
    Tuple over_point_;
    Tuple under_point_;
    Tuple eyev_;
    Tuple normalv_;
    Tuple reflectv_;

    [[nodiscard]] double schlick() const;
  };

  [[nodiscard]] Comps prepare_computations(
      Ray ray, const std::vector<Intersection>& xs) const;
  [[nodiscard]] Comps prepare_computations(Ray ray) const {
    std::vector<Intersection> xs;
    return prepare_computations(ray, xs);
  }

  // Member variables
  double t_;
  const Shape* obj_;
};