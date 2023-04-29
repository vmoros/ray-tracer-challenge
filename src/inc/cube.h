#pragma once

#include <intersection.h>
#include <ray.h>
#include <shape.h>
#include <tuple.h>

#include <utility>
#include <vector>

class Cube : public Shape {
 public:
  // Constructors
  Cube() = default;
  Cube(const Mat<4>& transformation, const Material& mat)
      : Shape(transformation, mat) {}
  explicit Cube(const Material& mat) : Cube(Mat<4>::iden(), mat) {}

  // Misc
  bool operator==(const Cube& other) const {
    return inverse_ == other.inverse_ && material_ == other.material_;
  }

  // Member variables come from Shape

  [[nodiscard]] std::vector<Intersection> local_intersect(
      Ray ray) const override;
  [[nodiscard]] Tuple local_normal_at(Tuple point) const override;

 private:
  [[nodiscard]] static std::pair<double, double> check_axis(double origin,
                                                            double direction);
};