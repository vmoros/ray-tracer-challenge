#include <cone.h>
#include <gtest/gtest.h>
#include <helpers.h>
#include <ray.h>
#include <tuple.h>

#include <tuple>

class ConeIntersections
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, double, double>> {
};

TEST_P(ConeIntersections, ConeIntersections_AreCorrect) {
  Cone shape;
  Tuple direction = get<1>(GetParam()).norm();
  Ray r(get<0>(GetParam()), direction);
  auto xs = shape.local_intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_TRUE(dbleq(xs[0].t_, get<2>(GetParam())));
  EXPECT_TRUE(dbleq(xs[1].t_, get<3>(GetParam())));
}

INSTANTIATE_TEST_SUITE_P(
    ConeIntersections, ConeIntersections,
    testing::Values(std::make_tuple(Tuple::Point(0, 0, -5),
                                    Tuple::Vector(0, 0, 1), 5.0, 5.0),
                    std::make_tuple(Tuple::Point(0, 0, -5),
                                    Tuple::Vector(1, 1, 1), 8.66025, 8.66025),
                    std::make_tuple(Tuple::Point(1, 1, -5),
                                    Tuple::Vector(-0.5, -1, 1), 4.55006,
                                    49.44994)));

TEST(ConeTest, RayParallelToHalfOfCone_Intersects) {
  Cone shape;
  Tuple direction = Tuple::Vector(0, 1, 1).norm();
  Ray r(Tuple::Point(0, 0, -1), direction);
  auto xs = shape.local_intersect(r);

  EXPECT_EQ(xs.size(), 1);
  EXPECT_TRUE(dbleq(xs[0].t_, 0.35355));
}

class ConeCapInt
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, size_t>> {};

TEST_P(ConeCapInt, ConeCaps_HaveCorrectIntersections) {
  Cone shape(-0.5, 0.5);
  Tuple direction = get<1>(GetParam()).norm();
  Ray r(get<0>(GetParam()), direction);
  auto xs = shape.local_intersect(r);

  EXPECT_EQ(xs.size(), get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    ConeCapInt, ConeCapInt,
    testing::Values(
        std::make_tuple(Tuple::Point(0, 0, -5), Tuple::Vector(0, 1, 0), 0),
        std::make_tuple(Tuple::Point(0, 0, -0.25), Tuple::Vector(0, 1, 1), 2),
        std::make_tuple(Tuple::Point(0, 0, -0.25), Tuple::Vector(0, 1, 0), 4)));

class ConeNormals : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};
TEST_P(ConeNormals, ConeNormals_AreCorrect) {
  Cone shape;
  Tuple n = shape.local_normal_at(get<0>(GetParam()));

  EXPECT_EQ(n, get<1>(GetParam()));
}
INSTANTIATE_TEST_SUITE_P(
    ConeNormals, ConeNormals,
    testing::Values(
        std::make_tuple(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 0)),
        std::make_tuple(Tuple::Point(1, 1, 1), Tuple::Vector(1, -sqrt(2), 1)),
        std::make_tuple(Tuple::Point(-1, -1, 0), Tuple::Vector(-1, 1, 0))));