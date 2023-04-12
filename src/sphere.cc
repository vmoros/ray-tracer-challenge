#include <helpers.h>
#include <shape.h>
#include <sphere.h>
#include <tuple.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

Sphere::Sphere(Mat<4> transformation, Material material)
    : Shape(transformation, material) {}
Sphere::Sphere(Mat<4> transformation) : Sphere(transformation, Material()) {}
Sphere::Sphere(Material material) : Sphere(Mat<4>::iden(), material) {}
Sphere::Sphere() : Sphere(Mat<4>::iden(), Material()) {}

bool Sphere::operator==(const Sphere other) const {
  return transformation_ == other.transformation_ &&
         material_ == other.material_;
}

std::vector<Intersection> Sphere::local_intersect(Ray ray) const {
  Tuple sphere_to_ray = ray.origin_ - Tuple::Origin();

  double a = ray.direction_.dot(ray.direction_);
  double b = 2 * ray.direction_.dot(sphere_to_ray);
  double c = sphere_to_ray.dot(sphere_to_ray) - 1;
  double discrim = b * b - 4 * a * c;

  if (discrim < 0) {
    return {};
  }

  double t1 = (-b - sqrt(discrim)) / (2 * a);
  double t2 = (-b + sqrt(discrim)) / (2 * a);
  return {{t1, this}, {t2, this}};
}

Tuple Sphere::local_normal_at(Tuple point) const {
  point.w_ = 0;
  return point;
}