#include <light.h>

#include <cmath>

PointLight::PointLight(Tuple pos, Color intns)
    : position_(pos), intensity_(intns) {}

bool PointLight::operator==(PointLight other) const {
  return position_ == other.position_ && intensity_ == other.intensity_;
}

Color PointLight::lighting(Material material, Tuple point, Tuple eyev,
                           Tuple normalv, bool in_shadow) const {
  if (material.pattern_.has_value()) {
    material.color_ = material.pattern_.value().stripe_at(point);
  }
  Color effective_color = material.color_ * intensity_;
  Color ambient = effective_color * material.ambient_;
  Tuple lightv = (position_ - point).norm();
  double light_dot_normal = lightv.dot(normalv);

  if (light_dot_normal < 0 || in_shadow) {
    return ambient;
  }

  Color diffuse = effective_color * material.diffuse_ * light_dot_normal;
  Tuple reflectv = (-lightv).reflect(normalv);
  double reflect_dot_eye = reflectv.dot(eyev);

  Color specular;
  if (reflect_dot_eye <= 0) {
    specular = Color::Black();
  } else {
    specular = intensity_ * material.specular_ *
               pow(reflect_dot_eye, material.shininess_);
  }

  return ambient + diffuse + specular;
}
