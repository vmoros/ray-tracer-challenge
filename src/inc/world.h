#pragma once

#include <color.h>
#include <intersection.h>
#include <light.h>
#include <ray.h>
#include <shape.h>

#include <vector>

static constexpr int MAX_RECURSION = 10;

class World {
 public:
  // Constructors & factories
  World(const std::vector<const Shape*>& shapes, PointLight light);
  World();

  // Misc
  [[nodiscard]] std::vector<Intersection> intersect(Ray ray) const;
  [[nodiscard]] Color shade_hit(const Intersection::Comps& comps,
                                int remaining = MAX_RECURSION) const;
  [[nodiscard]] Color color_at(const Ray& ray,
                               int remaining = MAX_RECURSION) const;
  [[nodiscard]] bool is_shadowed(const Tuple& point) const;
  [[nodiscard]] Color reflected_color(const Intersection::Comps& comps,
                                      int remaining = MAX_RECURSION) const;
  [[nodiscard]] Color refracted_color(const Intersection::Comps& comps,
                                      int remaining = MAX_RECURSION) const;

  // Member variables
  std::vector<const Shape*> shapes_;
  PointLight light_;
};