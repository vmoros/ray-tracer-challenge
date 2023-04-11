#include <gtest/gtest.h>
#include <helpers.h>
#include <intersection.h>
#include <sphere.h>

TEST(IntersectionTest, Intersection_HasCorrectComponents) {
  Sphere s;
  Intersection i(3.5, &s);

  EXPECT_DOUBLE_EQ(i.t_, 3.5);
  EXPECT_EQ(*i.obj_, s);
}

TEST(IntersectionTest, RaySphereIntersections_ContainObjects) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_EQ(*xs[0].obj_, s);
  EXPECT_EQ(*xs[1].obj_, s);
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

TEST(IntersectionTest, Sphere_ContainsCorrectTransformation) {
  Sphere s;
  EXPECT_EQ(s.transformation_, Mat<4>::iden());

  Mat<4> newTransformation = Mat<4>::translator(2, 3, 4);
  s.transformation_ = newTransformation;
  EXPECT_EQ(s.transformation_, newTransformation);
}

TEST(IntersectionTest, ScaledSphere_HasCorrectIntersections) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  s.transformation_ = Mat<4>::scaler(2, 2, 2);
  auto xs = s.intersect(r);

  EXPECT_EQ(xs.size(), 2);
  EXPECT_DOUBLE_EQ(xs[0].t_, 3.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, 7.0);
}

TEST(IntersectionTest, TranslatedSphere_HasCorrectIntersections) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere s;
  s.transformation_ = Mat<4>::translator(5, 0, 0);
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