#pragma once

#include <color.h>
#include <intersection.h>
#include <light.h>
#include <ray.h>
#include <shape.h>

#include <vector>

static constexpr int MAX_REFLECTIONS = 4;

class World {
 public:
  // Constructors & factories
  World(std::vector<const Shape*> shapes, PointLight light);
  World();
  static World Empty();

  // Misc
  std::vector<Intersection> intersect(Ray ray) const;
  Color shade_hit(Intersection::Comps comps,
                  int remaining = MAX_REFLECTIONS) const;
  Color color_at(Ray ray, int remaining = MAX_REFLECTIONS) const;
  bool is_shadowed(Tuple point) const;
  Color reflected_color(Intersection::Comps comps,
                        int remaining = MAX_REFLECTIONS) const;

  // Member variables
  std::vector<const Shape*> shapes_;
  PointLight light_;
};