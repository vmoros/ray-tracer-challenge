#include <gtest/gtest.h>
#include <matrix.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>

TEST(RayTest, Ray_HasCorrectComponents) {
  Tuple origin = Tuple::Point(1, 2, 3);
  Tuple direction = Tuple::Vector(4, 5, 6);
  Ray r(origin, direction);

  EXPECT_EQ(r.origin_, origin);
  EXPECT_EQ(r.direction_, direction);
}

TEST(RayTest, RayPosition_IsCorrect) {
  Ray r(Tuple::Point(2, 3, 4), Tuple::Vector(1, 0, 0));

  EXPECT_EQ(r.position(0), Tuple::Point(2, 3, 4));
  EXPECT_EQ(r.position(1), Tuple::Point(3, 3, 4));
  EXPECT_EQ(r.position(-1), Tuple::Point(1, 3, 4));
  EXPECT_EQ(r.position(2.5), Tuple::Point(4.5, 3, 4));
}

TEST(RayTest, RayIntersectsSphere_TwiceThroughTheOrigin) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, 4.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, 6.0);
}

TEST(RayTest, RayIntersectsSphere_TwiceAtTangent) {
  Ray r(Tuple::Point(0, 1, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, 5.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, 5.0);
}

TEST(RayTest, RayAboveSphere_DoesNotIntersect) {
  Ray r(Tuple::Point(0, 2, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 0);
}

TEST(RayTest, RayStartingInsideSphere_IntersectsSphereTwice) {
  Ray r(Tuple::Origin(), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, -1.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, 1.0);
}

TEST(RayTest, RayStartingInFrontOfSphere_IntersectsSphereTwice) {
  Ray r(Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, -6.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, -4.0);
}

TEST(RayTest, RayCanBeTranslated) {
  Ray r(Tuple::Point(1, 2, 3), Tuple::Vector(0, 1, 0));
  Mat<4> m = Mat<4>::translator(3, 4, 5);
  Ray r2 = r.transform(m);

  EXPECT_EQ(r2.origin_, Tuple::Point(4, 6, 8));
  EXPECT_EQ(r2.direction_, Tuple::Vector(0, 1, 0));
}

TEST(RayTest, RayCanBeScaled) {
  Ray r(Tuple::Point(1, 2, 3), Tuple::Vector(0, 1, 0));
  Mat<4> m = Mat<4>::scaler(2, 3, 4);
  Ray r2 = r.transform(m);

  EXPECT_EQ(r2.origin_, Tuple::Point(2, 6, 12));
  EXPECT_EQ(r2.direction_, Tuple::Vector(0, 3, 0));
}