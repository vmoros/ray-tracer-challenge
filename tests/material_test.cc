#include <color.h>
#include <gtest/gtest.h>
#include <material.h>
#include <sphere.h>

TEST(MaterialTest, Material_HasCorrectComponents) {
  Material m;

  EXPECT_EQ(m.color_, Color::White());
  EXPECT_DOUBLE_EQ(m.ambient_, 0.1);
  EXPECT_DOUBLE_EQ(m.diffuse_, 0.9);
  EXPECT_DOUBLE_EQ(m.specular_, 0.9);
  EXPECT_DOUBLE_EQ(m.shininess_, 200.0);
}

TEST(MaterialTest, Material_HasReflectivityComponent) {
  Material m;

  EXPECT_DOUBLE_EQ(m.reflectivity_, 0.0);
}

TEST(MaterialTest, DefaultMaterial_HasTransparencyAndRefractiveIndex) {
  Material m;

  EXPECT_DOUBLE_EQ(m.transparency_, 0.0);
  EXPECT_DOUBLE_EQ(m.refract_, 1.0);
}

TEST(MaterialTest, GlassSphere_HasCorrectComponents) {
  Sphere s = Sphere::glass_sphere();

  EXPECT_DOUBLE_EQ(s.material_.transparency_, 1.0);
  EXPECT_DOUBLE_EQ(s.material_.refract_, 1.5);
}