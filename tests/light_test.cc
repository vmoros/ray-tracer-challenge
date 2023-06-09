#include <color.h>
#include <gtest/gtest.h>
#include <light.h>
#include <material.h>
#include <pattern.h>
#include <sphere.h>
#include <tuple.h>

#include <cmath>

static const Sphere s;

TEST(LightTest, PointLight_HasCorrectComponents) {
  Color intensity(1, 1, 1);
  Tuple position = Tuple::Point(0, 0, 0);
  PointLight light(position, intensity);

  EXPECT_EQ(light.position_, position);
  EXPECT_EQ(light.intensity_, intensity);
}

class LightingFixture : public testing::Test {
 public:
  Material m{};
  Tuple position = Tuple::Origin();
};

TEST_F(LightingFixture, EyeBetweenLightAndSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, -10), Color::White());

  Color result = light.lighting(m, &s, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST_F(LightingFixture,
       EyeAt45DegreesBetweenLightAndSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, -10), Color::White());

  Color result = light.lighting(m, &s, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST_F(LightingFixture,
       LightAt45DegreesBetweenEyeAndSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 10, -10), Color::White());

  Color result = light.lighting(m, &s, position, eyev, normalv);
  EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST_F(LightingFixture, EyeInPathOfReflectionVector_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 10, -10), Color::White());

  Color result = light.lighting(m, &s, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST_F(LightingFixture, LightBehindSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, 10), Color::White());

  Color result = light.lighting(m, &s, position, eyev, normalv);
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST_F(LightingFixture, SurfaceInShadow_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, -10), Color::White());

  Color result = light.lighting(m, &s, position, eyev, normalv, true);
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}

TEST_F(LightingFixture, Lighting_AppliesStripePattern) {
  StripePat pat(Color::White(), Color::Black());
  m.pattern_ = &pat;
  m.ambient_ = 1;
  m.diffuse_ = 0;
  m.specular_ = 0;
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, -10), Color::White());
  Color c1 = light.lighting(m, &s, Tuple::Point(0.9, 0, 0), eyev, normalv);
  Color c2 = light.lighting(m, &s, Tuple::Point(1.1, 0, 0), eyev, normalv);

  EXPECT_EQ(c1, Color::White());
  EXPECT_EQ(c2, Color::Black());
}