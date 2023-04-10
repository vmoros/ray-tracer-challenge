#pragma once

#include <color.h>

class Material {
 public:
  Material();
  Material(Color color);
  Material(Color color, double diffuse, double specular);

  bool operator==(Material other) const;

  // Member variables
  Color color_;
  double ambient_;
  double diffuse_;
  double specular_;
  double shininess_;
};