#include <helpers.h>
#include <sphere.h>
#include <tuple.h>

#include <cmath>

Sphere::Sphere() : center_(Tuple::Point(0, 0, 0)), radius_(0.0) {}

std::vector<double> Sphere::intersect(Ray ray) const {
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
  return {t1, t2};
};

bool Sphere::operator==(const Sphere other) const {
  return (center_ == other.center_) && (dbleq(radius_, other.radius_));
}
