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
#include <cmath>
#include <optional>
#include <vector>

static const Sphere s1(Material(Color(0.8, 1.0, 0.6), 0.7, 0.2));
static const Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
static const PointLight default_light(Tuple::Point(-10, 10, -10),
                                      Color::White());

World::World(const std::vector<const Shape*>& shapes, PointLight light)
    : shapes_(shapes), light_(light) {}

World::World() : World({&s1, &s2}, {default_light}) {}

std::vector<Intersection> World::intersect(Ray ray) const {
  std::vector<Intersection> ans;

  for (auto& shape : shapes_) {
    std::vector<Intersection> xs = shape->intersect(ray);
    ans.insert(ans.end(), xs.begin(), xs.end());
  }

  std::sort(
      ans.begin(), ans.end(),
      [](const Intersection& a, const Intersection& b) { return a.t_ < b.t_; });
  return ans;
}

Color World::shade_hit(Intersection::Comps comps, int remaining) const {
  bool shadowed = is_shadowed(comps.over_point_);

  Color surface =
      light_.lighting(comps.obj_->material_, comps.obj_, comps.over_point_,
                      comps.eyev_, comps.normalv_, shadowed);
  Color reflected = reflected_color(comps, remaining);
  Color refracted = refracted_color(comps, remaining);

  if (const Material& mat = comps.obj_->material_;
      mat.reflectivity_ > 0.0 && mat.transparency_ > 0.0) {
    double reflectance = comps.schlick();
    return surface + reflected * reflectance + refracted * (1.0 - reflectance);
  }

  return surface + reflected + refracted;
}

Color World::color_at(Ray ray, int remaining) const {
  std::vector<Intersection> xs = intersect(ray);
  std::optional<Intersection> maybe_hit = Intersection::hit(xs);
  if (!maybe_hit.has_value()) {
    return Color::Black();
  }

  Intersection hit = maybe_hit.value();
  Intersection::Comps comps = hit.prepare_computations(ray, xs);
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

Color World::refracted_color(Intersection::Comps comps, int remaining) const {
  if (remaining < 1) {
    return Color::Black();
  }
  if (dbleq(comps.obj_->material_.transparency_, 0.0)) {
    return Color::Black();
  }

  double n_ratio = comps.n1_ / comps.n2_;
  double cos_i = comps.eyev_.dot(comps.normalv_);
  double sin2_t = n_ratio * n_ratio * (1 - (cos_i * cos_i));
  if (sin2_t > 1) {  // total internal reflection
    return Color::Black();
  }

  double cos_t = sqrt(1.0 - sin2_t);
  Tuple direction =
      comps.normalv_ * (n_ratio * cos_i - cos_t) - comps.eyev_ * n_ratio;
  Ray refract_ray(comps.under_point_, direction);

  return color_at(refract_ray, remaining - 1) *
         comps.obj_->material_.transparency_;
}