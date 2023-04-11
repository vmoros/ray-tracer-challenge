#include <color.h>
#include <gtest/gtest.h>
#include <light.h>
#include <material.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <algorithm>
#include <iostream>

TEST(WorldTest, DefaultWorld_HasCorrectComponents) {
  PointLight light(Tuple::Point(-10, 10, -10), Color(1, 1, 1));
  Material mat(Color(0.8, 1.0, 0.6));
  mat.diffuse_ = 0.7;
  mat.specular_ = 0.2;
  Sphere s1(mat);
  Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
  World w;

  EXPECT_EQ(w.light_, light);
  EXPECT_EQ(w.spheres_.size(), 2);
  EXPECT_NE(std::find(w.spheres_.begin(), w.spheres_.end(), s1),
            w.spheres_.end());
  EXPECT_NE(std::find(w.spheres_.begin(), w.spheres_.end(), s2),
            w.spheres_.end());
}

TEST(WorldTest, DefaultWorld_HasCorrectIntersections) {
  World w;
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  std::vector<Intersection> xs = w.intersect(r);

  EXPECT_EQ(xs.size(), 4);
  EXPECT_DOUBLE_EQ(xs[0].t_, 4.0);
  EXPECT_DOUBLE_EQ(xs[1].t_, 4.5);
  EXPECT_DOUBLE_EQ(xs[2].t_, 5.5);
  EXPECT_DOUBLE_EQ(xs[3].t_, 6.0);
}

TEST(WorldTest, PrepareComputations_HasCorrectComponents) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_DOUBLE_EQ(comps.t_, i.t_);
  EXPECT_EQ(*comps.obj_, *i.obj_);
  EXPECT_EQ(comps.point_, Tuple::Point(0, 0, -1));
  EXPECT_EQ(comps.eyev_, Tuple::Vector(0, 0, -1));
  EXPECT_EQ(comps.normalv_, Tuple::Vector(0, 0, -1));
}

TEST(WorldTest, PrepareComputations_DetectsHitOnTheOutside) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_FALSE(comps.inside_);
}

TEST(WorldTest, PrepareComputations_DetectsHitOnTheInsideAndNegatesNormal) {
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  Sphere shape;
  Intersection i(1, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(comps.point_, Tuple::Point(0, 0, 1));
  EXPECT_EQ(comps.eyev_, Tuple::Vector(0, 0, -1));
  EXPECT_TRUE(comps.inside_);
  EXPECT_EQ(comps.normalv_, Tuple::Vector(0, 0, -1));
}

TEST(WorldTest, ShadedIntersectionOnOutside_HasCorrectColor) {
  World w;
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Sphere shape = w.spheres_[0];
  Intersection i(4, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(w.shade_hit(comps), Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadedIntersectionOnInside_HasCorrectColor) {
  World w;
  w.light_ = PointLight(Tuple::Point(0, 0.25, 0), Color(1, 1, 1));
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  Sphere shape = w.spheres_[1];
  Intersection i(0.5, &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(w.shade_hit(comps), Color(0.90498, 0.90498, 0.90498));
}

TEST(WorldTest, WhenRayMisses_ColorIsBlack) {
  World w;
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 1, 0));

  EXPECT_EQ(w.color_at(r), Color::Black());
}

TEST(WorldTest, WhenRayHits_ColorIsCorrect) {
  World w;
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));

  EXPECT_EQ(w.color_at(r), Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, WhenRayHasSeveralIntersections_FirstHitIsUsed) {
  World w;
  Sphere& outer = w.spheres_[0];
  outer.material_.ambient_ = 1.0;
  Sphere& inner = w.spheres_[1];
  inner.material_.ambient_ = 1.0;
  Ray r(Tuple::Point(0, 0, 0.75), Tuple::Vector(0, 0, -1));

  EXPECT_EQ(w.color_at(r), inner.material_.color_);
}
