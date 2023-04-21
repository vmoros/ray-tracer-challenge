#pragma once

#include <shape.h>

#include <vector>

class Group : public Shape {
 public:
  // Constructors
  Group() = default;

  // Misc
  [[nodiscard]] std::vector<Intersection> local_intersect(Ray) const override {
    return {};
  }
  [[nodiscard]] Tuple local_normal_at(Tuple) const override { return {}; }
  void add_child(Shape& shape) {
    shapes_.push_back(&shape);
    shape.parent_ = this;
  }

  // Member variables - some come from Shape
  std::vector<Shape*> shapes_;
};