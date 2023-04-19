#include <gtest/gtest.h>
#include <helpers.h>
#include <matrix.h>
#include <sphere.h>

#include <cmath>

TEST(SphereTest, SphereNormalAtPointOnXAxis_IsCorrect) {
  Sphere s;
  Tuple n = s.normal_at(Tuple::Point(1, 0, 0));

  EXPECT_EQ(n, Tuple::Vector(1, 0, 0));
}

TEST(SphereTest, SphereNormalAtPointOnYAxis_IsCorrect) {
  Sphere s;
  Tuple n = s.normal_at(Tuple::Point(0, 1, 0));

  EXPECT_EQ(n, Tuple::Vector(0, 1, 0));
}

TEST(SphereTest, SphereNormalAtPointOnZAxis_IsCorrect) {
  Sphere s;
  Tuple n = s.normal_at(Tuple::Point(0, 0, 1));

  EXPECT_EQ(n, Tuple::Vector(0, 0, 1));
}

TEST(SphereTest, SphereNormalAtNonAxialPoint_IsCorrect) {
  Sphere s;
  Tuple n = s.normal_at(Tuple::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

  EXPECT_EQ(n, Tuple::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
  EXPECT_EQ(n, n.norm());
}

TEST(SphereTest, NormalOnTranslatedSphere_IsCorrect) {
  Sphere s(Mat<4>::translator(0, 1, 0));
  Tuple n = s.normal_at(Tuple::Point(0, 1.70711, -0.70711));

  EXPECT_EQ(n, Tuple::Vector(0, 0.70711, -0.70711));
}

TEST(SphereTest, NormalOnTransformedSphere_IsCorrect) {
  Sphere s(Mat<4>::scaler(1, 0.5, 1) * Mat<4>::rotator_z(PI / 5));
  Tuple n = s.normal_at(Tuple::Point(0, sqrt(2) / 2, -sqrt(2) / 2));

  EXPECT_EQ(n, Tuple::Vector(0, 0.97014, -0.24254));
}

TEST(SphereTest, Sphere_IsAShape) {
  Sphere s;
  EXPECT_NE(dynamic_cast<Shape*>(&s), nullptr);
}