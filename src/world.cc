#include <color.h>
#include <intersection.h>
#include <light.h>
#include <material.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

static const Sphere s1(Material(Color(0.8, 1.0, 0.6), 0.7, 0.2));
static const Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
PointLight default_light(Tuple::Point(-10, 10, -10), Color::White());

World::World(std::vector<Sphere> spheres, PointLight light)
    : spheres_(spheres), light_(light) {}

World::World() : World({s1, s2}, {default_light}) {}

World World::Empty() {
  World ans;
  ans.spheres_.clear();
  return ans;
}

std::vector<Intersection> World::intersect(Ray ray) const {
  std::vector<Intersection> ans;

  for (auto& sphere : spheres_) {
    std::vector<Intersection> xs = sphere.intersect(ray);
    ans.insert(ans.end(), xs.begin(), xs.end());
  }

  std::sort(
      ans.begin(), ans.end(),
      [](const Intersection& a, const Intersection& b) { return a.t_ < b.t_; });
  return ans;
}

Color World::shade_hit(Intersection::Comps comps) const {
  bool shadowed = is_shadowed(comps.over_point_);

  return light_.lighting(comps.obj_->material_, comps.point_, comps.eyev_,
                         comps.normalv_, shadowed);
}

Color World::color_at(Ray ray) const {
  std::vector<Intersection> xs = intersect(ray);
  std::optional<Intersection> maybe_hit = Intersection::hit(xs);
  if (!maybe_hit.has_value()) {
    return Color::Black();
  }

  Intersection hit = maybe_hit.value();
  Intersection::Comps comps = hit.prepare_computations(ray);
  return shade_hit(comps);
}

bool World::is_shadowed(Tuple point) const {
  Tuple v = light_.position_ - point;
  double distance = v.mag();
  Tuple direction = v.norm();

  Ray r(point, direction);
  std::vector<Intersection> intersections = intersect(r);

  std::optional<Intersection> maybe_hit = Intersection::hit(intersections);
  return maybe_hit.has_value() && (maybe_hit.value().t_ < distance);
}
