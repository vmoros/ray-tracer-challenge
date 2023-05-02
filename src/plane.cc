#include <helpers.h>
#include <intersection.h>
#include <plane.h>
#include <ray.h>
#include <tuple.h>

#include <vector>

std::vector<Intersection> Plane::local_intersect(Ray ray) const {
  if (std::abs(ray.direction_.y_) < EPS) {
    return {};  // ray is coplanar
  }

  double t = -ray.origin_.y_ / ray.direction_.y_;
  return {Intersection(t, this)};
}

// unnamed parameter to suppress "unused parameter" warnings
// we need the parameter in order to be a valid
// override but we don't actually want to use it
// because a plane has the same normal everywhere
Tuple Plane::local_normal_at(Tuple) const { return Tuple::Vector(0, 1, 0); }
