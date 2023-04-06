#include <helpers.h>
#include <sphere.h>
#include <tuple.h>

#include <algorithm>
#include <cmath>
#include <optional>
#include <ranges>
#include <vector>

Intersection::Intersection(double t, const Sphere& obj) : t_(t), obj_(obj) {}

std::optional<Intersection> Intersection::hit(
    std::vector<Intersection> intersections) {
  auto filtered = intersections | std::views::filter([](const auto inter) {
                    return inter.t_ >= 0.0;
                  });
  auto ans = std::ranges::min_element(
      filtered, [](const auto a, const auto b) { return a.t_ < b.t_; });

  if (ans == std::ranges::end(filtered)) {
    return std::nullopt;
  }
  return *ans;
}

bool Intersection::operator==(const Intersection other) const {
  return dbleq(t_, other.t_) && (obj_ == other.obj_);
}

Sphere::Sphere()
    : radius_(0.0),
      center_(Tuple::Point(0, 0, 0)),
      transformation_(Mat<4>::iden()) {}

Sphere::Sphere(double radius, Tuple center, Mat<4> transformation)
    : radius_(radius), center_(center), transformation_(transformation) {}

std::vector<Intersection> Sphere::intersect(Ray ray) const {
  Tuple sphere_to_ray = ray.origin_ - Tuple::Point(0, 0, 0);

  double a = ray.direction_.dot(ray.direction_);
  double b = 2 * ray.direction_.dot(sphere_to_ray);
  double c = sphere_to_ray.dot(sphere_to_ray) - 1;
  double discrim = b * b - 4 * a * c;

  if (discrim < 0) {
    return {};
  }

  double t1 = (-b - sqrt(discrim)) / (2 * a);
  double t2 = (-b + sqrt(discrim)) / (2 * a);
  return {{t1, *this}, {t2, *this}};
};

bool Sphere::operator==(const Sphere other) const {
  return (center_ == other.center_) && (dbleq(radius_, other.radius_));
}
