#pragma once

#include <color.h>
#include <intersection.h>
#include <light.h>
#include <ray.h>
#include <sphere.h>

#include <vector>

class World {
 public:
  // Constructors & factories
  World(std::vector<Sphere> spheres, PointLight light);
  World();
  static World Empty();

  // Misc
  std::vector<Intersection> intersect(Ray ray) const;
  Color shade_hit(Intersection::Comps comps) const;
  Color color_at(Ray ray) const;
  bool is_shadowed(Tuple point) const;

  // Member variables
  std::vector<Sphere> spheres_;
  PointLight light_;
};