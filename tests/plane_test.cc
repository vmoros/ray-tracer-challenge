#include <gtest/gtest.h>
#include <plane.h>
#include <ray.h>
#include <tuple.h>

#include <vector>

TEST(PlaneTest, PlaneNormal_IsSameEverywhere) {
  Plane p;
  Tuple n1 = p.local_normal_at(Tuple::Origin());
  Tuple n2 = p.local_normal_at(Tuple::Point(10, 0, -10));
  Tuple n3 = p.local_normal_at(Tuple::Point(-5, 0, 150));

  EXPECT_EQ(n1, Tuple::Vector(0, 1, 0));
  EXPECT_EQ(n2, Tuple::Vector(0, 1, 0));
  EXPECT_EQ(n3, Tuple::Vector(0, 1, 0));
}

TEST(PlaneTest, RayParallelToPlane_HasNoIntersections) {
  Plane p;
  Ray r(Tuple::Point(0, 10, 0), Tuple::Vector(0, 0, 1));

  EXPECT_TRUE(p.local_intersect(r).empty());
}

TEST(PlaneTest, RayAlongPlane_HasNoIntersections) {
  Plane p;
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));

  EXPECT_TRUE(p.local_intersect(r).empty());
}

TEST(PlaneTest, RayAbovePlane_IntersectsOnce) {
  Plane p;
  Ray r(Tuple::Point(0, 1, 0), Tuple::Vector(0, -1, 0));
  std::vector<Intersection> xs = p.local_intersect(r);

  EXPECT_EQ(xs.size(), 1);
  EXPECT_DOUBLE_EQ(xs[0].t_, 1.0);
  EXPECT_EQ(xs[0].obj_, &p);
}

TEST(PlaneTest, RayBelowPlane_IntersectsOnce) {
  Plane p;
  Ray r(Tuple::Point(0, -1, 0), Tuple::Vector(0, 1, 0));
  std::vector<Intersection> xs = p.local_intersect(r);

  EXPECT_EQ(xs.size(), 1);
  EXPECT_DOUBLE_EQ(xs[0].t_, 1.0);
  EXPECT_EQ(xs[0].obj_, &p);
}