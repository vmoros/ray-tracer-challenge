#pragma once

#include <color.h>
#include <pattern.h>

#include <optional>

class Material {
 public:
  // Constructors
  Material();
  explicit Material(Color color);
  Material(Color color, double diffuse, double specular);

  // Misc
  bool operator==(Material other) const;
  static Material Glass() {
    Material mat(Color::Gray());
    mat.reflectivity_ = 0.9;
    mat.transparency_ = 1.0;
    mat.refract_ = 1.5;
    mat.diffuse_ = 0.1;
    mat.specular_ = 1.0;
    mat.shininess_ = 300.0;
    return mat;
  }

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