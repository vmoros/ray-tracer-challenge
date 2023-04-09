#include <color.h>
#include <helpers.h>
#include <material.h>

static const Color COL(1, 1, 1);
static constexpr double AMB = 0.1;
static constexpr double DIFF = 0.9;
static constexpr double SPEC = 0.9;
static constexpr double SHIN = 200.0;

Material::Material(Color color)
    : color_(color),
      ambient_(AMB),
      diffuse_(DIFF),
      specular_(SPEC),
      shininess_(SHIN) {}

Material::Material() : Material(COL) {}

bool Material::operator==(Material other) const {
  return color_ == other.color_ && dbleq(ambient_, other.ambient_) &&
         dbleq(diffuse_, other.diffuse_) && dbleq(specular_, other.specular_) &&
         dbleq(shininess_, other.shininess_);
};