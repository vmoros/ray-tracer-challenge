#include <cube.h>
#include <gtest/gtest.h>
#include <ray.h>
#include <tuple.h>

#include <tuple>

class CubeIntersections
    : public testing::TestWithParam<std::tuple<Tuple, Tuple, double, double>> {
};

TEST_P(CubeIntersections, VariousRayIntersections_AreCorrect) {
  Cube c;

  Tuple origin = get<0>(GetParam());
  Tuple direction = get<1>(GetParam());
  Ray r(origin, direction);
  auto xs = c.local_intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, get<2>(GetParam()));
  EXPECT_DOUBLE_EQ(xs[1].t_, get<3>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    LotsOfCubeIntersections, CubeIntersections,
    testing::Values(
        std::make_tuple(Tuple::Point(5, 0.5, 0), Tuple::Vector(-1, 0, 0), 4, 6),
        std::make_tuple(Tuple::Point(-5, 0.5, 0), Tuple::Vector(1, 0, 0), 4, 6),
        std::make_tuple(Tuple::Point(0.5, 5, 0), Tuple::Vector(0, -1, 0), 4, 6),
        std::make_tuple(Tuple::Point(0.5, -5, 0), Tuple::Vector(0, 1, 0), 4, 6),
        std::make_tuple(Tuple::Point(0.5, 0, 5), Tuple::Vector(0, 0, -1), 4, 6),
        std::make_tuple(Tuple::Point(0.5, 0, -5), Tuple::Vector(0, 0, 1), 4, 6),
        std::make_tuple(Tuple::Point(0, 0.5, 0), Tuple::Vector(0, 0, 1), -1,
                        1)));

class CubeMisses : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

TEST_P(CubeMisses, VariousRays_DoNotIntersectCube) {
  Cube c;
  Tuple origin = get<0>(GetParam());
  Tuple direction = get<1>(GetParam());
  Ray r(origin, direction);
  auto xs = c.local_intersect(r);

  EXPECT_EQ(xs.size(), 0);
}

INSTANTIATE_TEST_SUITE_P(
    LotsOfCubeMisses, CubeMisses,
    testing::Values(
        std::make_tuple(Tuple::Point(-2, 0, 0),
                        Tuple::Vector(0.2673, 0.5345, 0.8018)),
        std::make_tuple(Tuple::Point(0, -2, 0),
                        Tuple::Vector(0.8018, 0.2673, 0.5345)),
        std::make_tuple(Tuple::Point(0, 0, -2),
                        Tuple::Vector(0.5345, 0.8018, 0.2673)),
        std::make_tuple(Tuple::Point(2, 0, 2), Tuple::Vector(0, 0, -1)),
        std::make_tuple(Tuple::Point(0, 2, 2), Tuple::Vector(0, -1, 0)),
        std::make_tuple(Tuple::Point(2, 2, 0), Tuple::Vector(-1, 0, 0))));

class CubeNormals : public testing::TestWithParam<std::tuple<Tuple, Tuple>> {};

TEST_P(CubeNormals, VariousCubeNormals_AreCorrect) {
  Cube c;
  Tuple p = get<0>(GetParam());

  EXPECT_EQ(c.local_normal_at(p), get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    LotsOfCubeNormals, CubeNormals,
    testing::Values(
        std::make_tuple(Tuple::Point(1, 0.5, -0.8), Tuple::Vector(1, 0, 0)),
        std::make_tuple(Tuple::Point(-1, -0.2, 0.9), Tuple::Vector(-1, 0, 0)),
        std::make_tuple(Tuple::Point(-0.4, 1, -0.1), Tuple::Vector(0, 1, 0)),
        std::make_tuple(Tuple::Point(0.3, -1, -0.7), Tuple::Vector(0, -1, 0)),
        std::make_tuple(Tuple::Point(-0.6, 0.3, 1), Tuple::Vector(0, 0, 1)),
        std::make_tuple(Tuple::Point(0.4, 0.4, -1), Tuple::Vector(0, 0, -1)),
        std::make_tuple(Tuple::Point(1, 1, 1), Tuple::Vector(1, 0, 0)),
        std::make_tuple(Tuple::Point(-1, -1, -1), Tuple::Vector(-1, 0, 0))));