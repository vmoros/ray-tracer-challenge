#include <cylinder.h>
#include <gtest/gtest.h>
#include <helpers.h>
#include <ray.h>
#include <tuple.h>

#include <iostream>
#include <tuple>

class RayMiss : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

TEST_P(RayMiss, Ray_MissesCylinder) {
  Cylinder cyl;
  Tuple direction = get<1>(GetParam()).norm();
  Ray r(get<0>(GetParam()), direction);
  auto xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.size(), 0);
}

INSTANTIATE_TEST_SUITE_P(
    RayMiss, RayMiss,
    testing::Values(
        std::make_tuple(Tuple::Point(1, 0, 0), Tuple::Vector(0, 1, 0)),
        std::make_tuple(Tuple::Point(0, 0, 0), Tuple::Vector(0, 1, 0)),
        std::make_tuple(Tuple::Point(0, 0, -5), Tuple::Vector(1, 1, 1))));

class RayHit
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, double, double>> {
};

TEST_P(RayHit, Ray_HitsCylinder) {
  Cylinder cyl;
  Tuple direction = get<1>(GetParam()).norm();
  Ray r(get<0>(GetParam()), direction);
  auto xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_TRUE(dbleq(xs[0].t_, get<2>(GetParam())));
  EXPECT_TRUE(dbleq(xs[1].t_, get<3>(GetParam())));
}

INSTANTIATE_TEST_SUITE_P(
    RayHit, RayHit,
    testing::Values(
        std::make_tuple(Tuple::Point(1, 0, -5), Tuple::Vector(0, 0, 1), 5, 5),
        std::make_tuple(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1), 4, 6),
        std::make_tuple(Tuple::Point(0.5, 0, -5), Tuple::Vector(0.1, 1, 1),
                        6.807982, 7.088723)));

class CylNormal : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

TEST_P(CylNormal, NormalsOnCylinder_AreCorrect) {
  Cylinder cyl;

  EXPECT_EQ(cyl.local_normal_at(get<0>(GetParam())), get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    CylNormal, CylNormal,
    testing::Values(
        std::make_tuple(Tuple::Point(1, 0, 0), Tuple::Vector(1, 0, 0)),
        std::make_tuple(Tuple::Point(0, 5, -1), Tuple::Vector(0, 0, -1)),
        std::make_tuple(Tuple::Point(0, -2, 1), Tuple::Vector(0, 0, 1)),
        std::make_tuple(Tuple::Point(-1, 1, 0), Tuple::Vector(-1, 0, 0))));

TEST(CylinderTest, DefaultCylinder_IsInfinitelyLong) {
  Cylinder cyl;

  EXPECT_DOUBLE_EQ(cyl.min_, -INFTY);
  EXPECT_DOUBLE_EQ(cyl.max_, INFTY);
}

class TruncatedCyl
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, size_t>> {};

TEST_P(TruncatedCyl, TruncatedCylinder_HasCorrectIntersections) {
  Cylinder cyl(1.0, 2.0, false);
  Tuple direction = get<1>(GetParam()).norm();
  Ray r(get<0>(GetParam()), direction);
  auto xs = cyl.local_intersect(r);
  //  std::cout << xs[0].t_ << "           " << xs[1].t_ << std::endl;
  EXPECT_EQ(xs.size(), get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    TruncatedCyl, TruncatedCyl,
    testing::Values(
        std::make_tuple(Tuple::Point(0, 1.5, 0), Tuple::Vector(0.1, 1, 0), 0),
        std::make_tuple(Tuple::Point(0, 3, -5), Tuple::Vector(0, 0, 1), 0),
        std::make_tuple(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1), 0),
        std::make_tuple(Tuple::Point(0, 2, -5), Tuple::Vector(0, 0, 1), 0),
        std::make_tuple(Tuple::Point(0, 1, -5), Tuple::Vector(0, 0, 1), 0),
        std::make_tuple(Tuple::Point(0, 1.5, -2), Tuple::Vector(0, 0, 1), 2)));

TEST(CylinderTest, DefaultCylinder_HasOpenEnds) {
  Cylinder cyl;
  EXPECT_FALSE(cyl.closed_);
}

class ClosedCylinderHits
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, size_t>> {};

TEST_P(ClosedCylinderHits, ClosedCylinder_HasCorrectIntersections) {
  Cylinder cyl(1.0, 2.0);
  Tuple direction = get<1>(GetParam()).norm();
  Ray r(get<0>(GetParam()), direction);
  auto xs = cyl.local_intersect(r);

  EXPECT_EQ(xs.size(), get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    ClosedCylinderHits, ClosedCylinderHits,
    testing::Values(
        std::make_tuple(Tuple::Point(0, 3, 0), Tuple::Vector(0, -1, 0), 2),
        std::make_tuple(Tuple::Point(0, 3, -2), Tuple::Vector(0, -1, 2), 2),
        std::make_tuple(Tuple::Point(0, 4, -2), Tuple::Vector(0, -1, 1), 2),
        std::make_tuple(Tuple::Point(0, 0, -2), Tuple::Vector(0, 1, 2), 2),
        std::make_tuple(Tuple::Point(0, -1, -2), Tuple::Vector(0, 1, 1), 2)));