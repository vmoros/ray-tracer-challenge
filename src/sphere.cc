#include <helpers.h>
#include <sphere.h>
#include <tuple.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <ranges>
#include <vector>

Intersection::Intersection(double t, const Sphere* obj) : t_(t), obj_(obj) {}

std::optional<Intersection> Intersection::hit(
    const std::vector<Intersection>& intersections) {
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

Intersection::Comps Intersection::prepare_computations(Ray ray) const {
  Tuple pos = ray.position(t_);

  Intersection::Comps ans = {
      .inside_ = false,
      .t_ = t_,
      .obj_ = obj_,
      .point_ = pos,
      // Deliberately not setting over_point_ because it will be set later
      .eyev_ = -ray.direction_,
      .normalv_ = obj_->normal_at(pos),
  };

  if (ans.normalv_.dot(ans.eyev_) < 0) {
    ans.inside_ = true;
    ans.normalv_ = -ans.normalv_;
  }

  ans.over_point_ = ans.point_ + ans.normalv_ * EPS;

  return ans;
}

Sphere::Sphere(Mat<4> transformation, Material material)
    : transformation_(transformation), material_(material) {}
Sphere::Sphere(Mat<4> transformation) : Sphere(transformation, Material()) {}
Sphere::Sphere(Material material) : Sphere(Mat<4>::iden(), material) {}
Sphere::Sphere() : Sphere(Mat<4>::iden(), Material()) {}

std::vector<Intersection> Sphere::intersect(Ray ray) const {
  ray = ray.transform(transformation_.inverse());
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

Tuple Sphere::normal_at(Tuple world_point) const {
  Tuple object_point = transformation_.inverse() * world_point;
  Tuple object_normal = object_point - Tuple::Origin();
  Tuple world_normal = transformation_.inverse().transp() * object_normal;
  world_normal.w_ = 0;

  return world_normal.norm();
}

bool Sphere::operator==(const Sphere other) const {
  return transformation_ == other.transformation_ &&
         material_ == other.material_;
}
