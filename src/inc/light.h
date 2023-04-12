#pragma once
#include <color.h>
#include <material.h>
#include <tuple.h>

class PointLight {
 public:
  // Constructors
  PointLight(Tuple pos, Color intns);

  // Misc
  Color lighting(Material material, Tuple point, Tuple eyev, Tuple normalv,
                 bool in_shadow = false) const;
  bool operator==(PointLight other) const;

  // Member variables
  Tuple position_;
  Color intensity_;
};