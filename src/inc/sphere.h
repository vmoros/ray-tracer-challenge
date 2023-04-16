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
  explicit Sphere(Mat<4> transformation);
  explicit Sphere(Material material);
  Sphere();

  // Misc
  bool operator==(const Sphere& other) const;
  static Sphere glass_sphere() {
    Material mat;
    mat.reflectivity_ = 0.9;
    mat.transparency_ = 1.0;
    mat.refract_ = 1.5;
    mat.diffuse_ = 0.1;
    mat.specular_ = 1.0;
    mat.shininess_ = 300.0;
    mat.color_ = Color(0.5, 0.5, 0.5);
    return Sphere(mat);
  }

  // Member variables come from Shape

  // Overrides
  [[nodiscard]] std::vector<Intersection> local_intersect(
      Ray ray) const override;
  [[nodiscard]] Tuple local_normal_at(Tuple point) const override;
};
