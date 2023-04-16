#include <gtest/gtest.h>
#include <helpers.h>
#include <intersection.h>
#include <plane.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>

#include <cmath>
#include <tuple>
#include <vector>

TEST(IntersectionTest, Intersection_HasCorrectComponents) {
  Sphere s;
  Intersection i(3.5, &s);

  EXPECT_DOUBLE_EQ(i.t_, 3.5);
  EXPECT_EQ(i.obj_, &s);
}

TEST(IntersectionTest, RaySphereIntersections_ContainObjects) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(xs[0].obj_, &s);
  EXPECT_EQ(xs[1].obj_, &s);
}

TEST(IntersectionTest, FindIntersectionHitWithAllPositiveT_GivesCorrectHit) {
  Sphere s;
  Intersection i1(1, &s);
  Intersection i2(2, &s);
  std::vector<Intersection> xs = {i1, i2};

  EXPECT_EQ(Intersection::hit(xs), i1);
}

TEST(IntersectionTest, FindIntersectionHitWithSomeNegativeT_GivesCorrectHit) {
  Sphere s;
  Intersection i1(-1, &s);
  Intersection i2(2, &s);
  std::vector<Intersection> xs = {i1, i2};

  EXPECT_EQ(Intersection::hit(xs), i2);
}

TEST(IntersectionTest, FindIntersectionHitWithAllNegativeT_GivesEmptyHit) {
  Sphere s;
  Intersection i1(-1, &s);
  Intersection i2(-2, &s);
  std::vector<Intersection> xs = {i1, i2};

  EXPECT_EQ(Intersection::hit(xs), std::nullopt);
}

TEST(IntersectionTest, FindIntersectionHitWithVariousT_GivesCorrectHit) {
  Sphere s;
  Intersection i1(5, &s);
  Intersection i2(7, &s);
  Intersection i3(-3, &s);
  Intersection i4(2, &s);
  std::vector<Intersection> xs = {i1, i2, i3, i4};

  EXPECT_EQ(Intersection::hit(xs), i4);
}

TEST(IntersectionTest, ScaledSphere_HasCorrectIntersections) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s(Mat<4>::scaler(2, 2, 2));
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, 3.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, 7.0);
}

TEST(IntersectionTest, TranslatedSphere_HasCorrectIntersections) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s(Mat<4>::translator(5, 0, 0));
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 0);
}

TEST(IntersectionTest, HitIsSlightlyMoved_ToPreventSelfShadows) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape(Mat<4>::translator(0, 0, 1));
  Intersection i(5, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_LT(comps.over_point_.z_, -EPS / 2);
  EXPECT_GT(comps.point_.z_, comps.over_point_.z_);
}

TEST(IntersectionTest, PrepareComputations_HasCorrectComponents) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_DOUBLE_EQ(comps.t_, i.t_);
  EXPECT_EQ(comps.obj_, i.obj_);
  EXPECT_EQ(comps.point_, Tuple::Point(0, 0, -1));
  EXPECT_EQ(comps.eyev_, Tuple::Vector(0, 0, -1));
  EXPECT_EQ(comps.normalv_, Tuple::Vector(0, 0, -1));
}

TEST(IntersectionTest, PrepareComputations_DetectsHitOnTheOutside) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_FALSE(comps.inside_);
}

TEST(IntersectionTest,
     PrepareComputations_DetectsHitOnTheInsideAndNegatesNormal) {
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  Sphere shape;
  Intersection i(1, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(comps.point_, Tuple::Point(0, 0, 1));
  EXPECT_EQ(comps.eyev_, Tuple::Vector(0, 0, -1));
  EXPECT_TRUE(comps.inside_);
  EXPECT_EQ(comps.normalv_, Tuple::Vector(0, 0, -1));
}

TEST(IntersectionTest, PrepareComputations_ComputesReflectionVector) {
  Plane shape;
  Ray r(Tuple::Point(0, 1, -1), Tuple::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  Intersection i(sqrt(2), &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(comps.reflectv_, Tuple::Vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

class RefractionFixture
    : public testing::TestWithParam<std::tuple<size_t, double, double>> {};

TEST_P(RefractionFixture, N1AndN2AtVariousIntersections_AreCorrect) {
  Sphere A = Sphere::glass_sphere();
  A.set_transformation(Mat<4>::scaler(2, 2, 2));
  A.material_.refract_ = 1.5;

  Sphere B = Sphere::glass_sphere();
  B.set_transformation(Mat<4>::translator(0, 0, -0.25));
  B.material_.refract_ = 2.0;

  Sphere C = Sphere::glass_sphere();
  C.set_transformation(Mat<4>::translator(0, 0, 0.25));
  C.material_.refract_ = 2.5;

  Ray r(Tuple::Point(0, 0, -4), Tuple::Vector(0, 0, 1));
  std::vector<Intersection> xs = {{2, &A},    {2.75, &B}, {3.25, &C},
                                  {4.75, &B}, {5.25, &C}, {6, &A}};

  size_t i = get<0>(GetParam());
  double n1 = get<1>(GetParam());
  double n2 = get<2>(GetParam());

  Intersection::Comps comps = xs[i].prepare_computations(r, xs);
  EXPECT_DOUBLE_EQ(comps.n1_, n1);
  EXPECT_DOUBLE_EQ(comps.n2_, n2);
}

INSTANTIATE_TEST_SUITE_P(LotsOfRefraction, RefractionFixture,
                         testing::Values(std::make_tuple(0, 1.0, 1.5),
                                         std::make_tuple(1, 1.5, 2.0),
                                         std::make_tuple(2, 2.0, 2.5),
                                         std::make_tuple(3, 2.5, 2.5),
                                         std::make_tuple(4, 2.5, 1.5),
                                         std::make_tuple(5, 1.5, 1.0)));

TEST(IntersectionTest, UnderPoint_IsJustBelowSurface) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape = Sphere::glass_sphere();
  shape.set_transformation(Mat<4>::translator(0, 0, 1));
  Intersection i(5, &shape);
  std::vector<Intersection> xs = {i};
  Intersection::Comps comps = i.prepare_computations(r, xs);

  EXPECT_GT(comps.under_point_.z_, EPS / 2);
  EXPECT_LT(comps.point_.z_, comps.under_point_.z_);
}