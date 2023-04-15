#include <color.h>
#include <helpers.h>
#include <intersection.h>
#include <light.h>
#include <material.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <algorithm>
#include <optional>
#include <vector>

static Sphere s1(Material(Color(0.8, 1.0, 0.6), 0.7, 0.2));
static Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
PointLight default_light(Tuple::Point(-10, 10, -10), Color::White());

World::World(std::vector<const Shape *> shapes, PointLight light)
    : shapes_(shapes), light_(light) {}

World::World() : World({&s1, &s2}, {default_light}) {}

World World::Empty() {
  World ans;
  ans.shapes_.clear();
  return ans;
}

std::vector<Intersection> World::intersect(Ray ray) const {
  std::vector<Intersection> ans;

  for (auto &shape : shapes_) {
    std::vector<Intersection> xs = shape->intersect(ray);
    ans.insert(ans.end(), xs.begin(), xs.end());
  }

  std::sort(
      ans.begin(), ans.end(),
      [](const Intersection &a, const Intersection &b) { return a.t_ < b.t_; });
  return ans;
}

Color World::shade_hit(Intersection::Comps comps, int remaining) const {
  bool shadowed = is_shadowed(comps.over_point_);

  Color surface =
      light_.lighting(comps.obj_->material_, comps.obj_, comps.over_point_,
                      comps.eyev_, comps.normalv_, shadowed);
  Color reflected = reflected_color(comps, remaining);
  return surface + reflected;
}

Color World::color_at(Ray ray, int remaining) const {
  std::vector<Intersection> xs = intersect(ray);
  std::optional<Intersection> maybe_hit = Intersection::hit(xs);
  if (!maybe_hit.has_value()) {
    return Color::Black();
  }

  Intersection hit = maybe_hit.value();
  Intersection::Comps comps = hit.prepare_computations(ray);
  return shade_hit(comps, remaining);
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

Color World::reflected_color(Intersection::Comps comps, int remaining) const {
  if (remaining < 1) {
    return Color::Black();  // black because this reflected color will be added
                            // to the surface's color, so if no reflection
                            // happens, we want that addition to do nothing
  }

  double reflectivity = comps.obj_->material_.reflectivity_;
  if (dbleq(reflectivity, 0.0)) {
    return Color::Black();
  }

  Ray reflect_ray(comps.over_point_, comps.reflectv_);
  Color color = color_at(reflect_ray, remaining - 1);
  return color * reflectivity;
}
