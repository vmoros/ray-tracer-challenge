#pragma once

#include <matrix.h>
#include <shape.h>

#include <algorithm>
#include <stdexcept>
#include <vector>

class Group : public Shape {
 public:
  // Constructors
  Group() = default;
  explicit Group(const Mat<4> transf) : Shape(transf, Material()) {}

  // Misc
  [[nodiscard]] std::vector<Intersection> local_intersect(
      Ray ray) const override {
    std::vector<Intersection> ans;

    for (auto shape : shapes_) {
      std::vector<Intersection> xs = shape->intersect(ray);
      ans.insert(ans.end(), xs.begin(), xs.end());
    }

    std::sort(ans.begin(), ans.end(),
              [](const Intersection& a, const Intersection& b) {
                return a.t_ < b.t_;
              });
    return ans;
  }
  [[nodiscard]] Tuple local_normal_at(Tuple) const override {
    throw std::runtime_error("Don't call local_normal_at on a Group");
  }

  void add_child(Shape& shape) {
    shapes_.push_back(&shape);
    shape.parent_ = this;
  }

  // Member variables - some come from Shape
  std::vector<Shape*> shapes_;
};