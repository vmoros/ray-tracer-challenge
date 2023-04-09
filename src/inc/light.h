#pragma once
#include <color.h>
#include <material.h>
#include <tuple.h>

class PointLight {
 public:
  PointLight(Tuple pos, Color intns);
  Color lighting(Material material, Tuple point, Tuple eyev,
                 Tuple normalv) const;

  // Member variables
  Tuple position_;
  Color intensity_;
};