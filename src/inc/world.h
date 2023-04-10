#pragma once

#include <color.h>
#include <light.h>
#include <ray.h>
#include <sphere.h>

#include <vector>

class World {
 public:
  // Constructors
  World(std::vector<Sphere> spheres, PointLight light);
  World();

  // Misc
  std::vector<Intersection> intersect(Ray ray);
  Color shade_hit(Intersection::Comps comps) const;
  Color color_at(Ray ray);

  // Member variables
  std::vector<Sphere> spheres_;
  PointLight light_;
};