#include <gtest/gtest.h>
#include <intersection.h>
#include <ray.h>
#include <sphere.h>

#include <vector>

TEST(IntersectionTest, Intersection_HasCorrectComponents) {
  Sphere s;
  Intersection i(3.5, s);

  EXPECT_DOUBLE_EQ(i.t_, 3.5);
  EXPECT_EQ(i.obj_, s);
}

// TEST(IntersectionTest, RaySphereIntersections_ContainObjects) {
//   Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
//   Sphere s;
//   auto xs = s.intersect(r);

//   EXPECT_EQ(xs.size(), 2);
//   EXPECT_EQ(xs[0], s);
//   EXPECT_EQ(xs[1], s);
// }