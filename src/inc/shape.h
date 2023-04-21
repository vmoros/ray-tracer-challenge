#pragma once

#include <intersection.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <tuple.h>
class Group;

#include <optional>
#include <vector>

class Shape {  // abstract parent class for all shapes e.g. Sphere
 public:
  // Constructors
  Shape(Mat<4> transformation, Material material);
  Shape() = default;

  // Misc
  [[nodiscard]] std::vector<Intersection> intersect(Ray r) const;
  [[nodiscard]] Tuple normal_at(Tuple point) const;
  void set_transformation(Mat<4> transformation) {
    inverse_ = transformation.inverse();
  }

  // Virtual functions
  [[nodiscard]] virtual std::vector<Intersection> local_intersect(
      Ray r) const = 0;
  [[nodiscard]] virtual Tuple local_normal_at(Tuple point) const = 0;

  // Member variables
  // Mat<4> transformation_;
  Mat<4> inverse_;
  Material material_;
  std::optional<Group*> parent_;

  virtual ~Shape() = default;
};