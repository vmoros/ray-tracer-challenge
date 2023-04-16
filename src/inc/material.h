#pragma once

#include <color.h>
#include <pattern.h>

#include <optional>

class Material {
 public:
  Material();
  explicit Material(Color color);
  Material(Color color, double diffuse, double specular);

  bool operator==(Material other) const;

  // Member variables
  Color color_;
  double ambient_;
  double diffuse_;
  double specular_;
  double shininess_;
  double reflectivity_;
  double transparency_;
  double refract_;
  std::optional<const Pattern*> pattern_;
};