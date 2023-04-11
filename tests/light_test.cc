#include <color.h>
#include <gtest/gtest.h>
#include <light.h>
#include <material.h>
#include <tuple.h>

TEST(LightTest, PointLight_HasCorrectComponents) {
  Color intensity(1, 1, 1);
  Tuple position = Tuple::Point(0, 0, 0);
  PointLight light(position, intensity);

  EXPECT_EQ(light.position_, position);
  EXPECT_EQ(light.intensity_, intensity);
}

class LightingFixture : public ::testing::Test {
 public:
  Material m{};
  Tuple position = Tuple::Origin();
};

TEST_F(LightingFixture, EyeBetweenLightAndSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, -10), Color(1, 1, 1));

  Color result = light.lighting(m, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST_F(LightingFixture,
       EyeAt45DegreesBetweenLightAndSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, sqrt(2) / 2, -sqrt(2) / 2);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, -10), Color(1, 1, 1));

  Color result = light.lighting(m, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST_F(LightingFixture,
       LightAt45DegreesBetweenEyeAndSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 10, -10), Color(1, 1, 1));

  Color result = light.lighting(m, position, eyev, normalv);
  EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST_F(LightingFixture, EyeInPathOfReflectionVector_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 10, -10), Color(1, 1, 1));

  Color result = light.lighting(m, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST_F(LightingFixture, LightBehindSurface_GivesCorrectLighting) {
  Tuple eyev = Tuple::Vector(0, 0, -1);
  Tuple normalv = Tuple::Vector(0, 0, -1);
  PointLight light(Tuple::Point(0, 0, 10), Color(1, 1, 1));

  Color result = light.lighting(m, position, eyev, normalv);
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}
