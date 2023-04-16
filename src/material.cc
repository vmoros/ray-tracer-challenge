#include <color.h>
#include <helpers.h>
#include <material.h>

static constexpr double AMB = 0.1;
static constexpr double DIFF = 0.9;
static constexpr double SPEC = 0.9;
static constexpr double SHIN = 200.0;
static constexpr double REFL = 0.0;
static constexpr double TRAN = 0.0;
static constexpr double REFR = 1.0;

Material::Material(Color color)
    : color_(color),
      ambient_(AMB),
      diffuse_(DIFF),
      specular_(SPEC),
      shininess_(SHIN),
      reflectivity_(REFL),
      transparency_(TRAN),
      refract_(REFR) {}

Material::Material() : Material(Color::White()) {}

Material::Material(Color color, double diffuse, double specular)
    : color_(color),
      ambient_(AMB),
      diffuse_(diffuse),
      specular_(specular),
      shininess_(SHIN),
      reflectivity_(REFL),
      transparency_(TRAN),
      refract_(REFR) {}

bool Material::operator==(Material other) const {
  return color_ == other.color_ && dbleq(ambient_, other.ambient_) &&
         dbleq(diffuse_, other.diffuse_) && dbleq(specular_, other.specular_) &&
         dbleq(shininess_, other.shininess_) &&
         dbleq(reflectivity_, other.reflectivity_) &&
         dbleq(transparency_, other.transparency_) &&
         dbleq(refract_, other.refract_);
}