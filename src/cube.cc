#include <cube.h>
#include <helpers.h>

#include <algorithm>

std::pair<double, double> Cube::check_axis(double origin, double direction) {
  double tmin_numerator = -1 - origin;
  double tmax_numerator = 1 - origin;

  double tmin{};
  double tmax{};
  if (!dbleq(direction, 0.0)) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    tmin = tmin_numerator * INFINITY;
    tmax = tmax_numerator * INFINITY;
  }

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  return {tmin, tmax};
}

std::vector<Intersection> Cube::local_intersect(Ray ray) const {
  auto [xtmin, xtmax] = check_axis(ray.origin_.x_, ray.direction_.x_);
  auto [ytmin, ytmax] = check_axis(ray.origin_.y_, ray.direction_.y_);
  auto [ztmin, ztmax] = check_axis(ray.origin_.z_, ray.direction_.z_);

  double tmin = std::max({xtmin, ytmin, ztmin});
  double tmax = std::min({xtmax, ytmax, ztmax});
  if (tmin > tmax) {
    return {};
  }

  return {{tmin, this}, {tmax, this}};
}

Tuple Cube::local_normal_at(Tuple point) const {
  double maxc = std::max({abs(point.x_), abs(point.y_), abs(point.z_)});

  if (dbleq(maxc, abs(point.x_))) {
    return Tuple::Vector(point.x_, 0, 0);
  } else if (dbleq(maxc, abs(point.y_))) {
    return Tuple::Vector(0, point.y_, 0);
  }
  return Tuple::Vector(0, 0, point.z_);
}
