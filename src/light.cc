#include <light.h>

#include <cmath>

PointLight::PointLight(Tuple pos, Color intns)
    : position_(pos), intensity_(intns) {}

Color PointLight::lighting(Material material, Tuple point, Tuple eyev,
                           Tuple normalv) const {
  Color effective_color = material.color_ * intensity_;
  Color ambient = effective_color * material.ambient_;
  Tuple lightv = (position_ - point).norm();
  double light_dot_normal = lightv.dot(normalv);

  if (light_dot_normal < 0) {
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
