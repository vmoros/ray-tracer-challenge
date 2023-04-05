#include <gtest/gtest.h>
#include <ray.h>
#include <sphere.h>

#include <optional>
#include <vector>

TEST(IntersectionTest, Intersection_HasCorrectComponents) {
  Sphere s;
  Intersection i(3.5, s);

  EXPECT_DOUBLE_EQ(i.t_, 3.5);
  EXPECT_EQ(i.obj_, s);
}

TEST(IntersectionTest, RaySphereIntersections_ContainObjects) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].obj_, s);
  EXPECT_EQ(xs[1].obj_, s);
}

TEST(IntersectionTest, FindIntersectionHitWithAllPositiveT_GivesCorrectHit) {
  Sphere s;
  Intersection i1(1, s);
  Intersection i2(2, s);
  std::vector<Intersection> xs = {i1, i2};

  EXPECT_EQ(Intersection::hit(xs), i1);
}

TEST(IntersectionTest, FindIntersectionHitWithSomeNegativeT_GivesCorrectHit) {
  Sphere s;
  Intersection i1(-1, s);
  Intersection i2(2, s);
  std::vector<Intersection> xs = {i1, i2};

  EXPECT_EQ(Intersection::hit(xs), i2);
}

TEST(IntersectionTest, FindIntersectionHitWithAllNegativeT_GivesEmptyHit) {
  Sphere s;
  Intersection i1(-1, s);
  Intersection i2(-2, s);
  std::vector<Intersection> xs = {i1, i2};

  EXPECT_EQ(Intersection::hit(xs), std::nullopt);
}

TEST(IntersectionTest, FindIntersectionHitWithVariousT_GivesCorrectHit) {
  Sphere s;
  Intersection i1(5, s);
  Intersection i2(7, s);
  Intersection i3(-3, s);
  Intersection i4(2, s);
  std::vector<Intersection> xs = {i1, i2, i3, i4};

  EXPECT_EQ(Intersection::hit(xs), i4);
}