#include <color.h>
#include <gtest/gtest.h>
#include <intersection.h>
#include <light.h>
#include <material.h>
#include <matrix.h>
#include <plane.h>
#include <ray.h>
#include <sphere.h>
#include <tuple.h>
#include <world.h>

#include <cmath>

TEST(WorldTest, DefaultWorld_HasCorrectComponents) {
  PointLight light(Tuple::Point(-10, 10, -10), Color::White());
  Material mat(Color(0.8, 1.0, 0.6));
  mat.diffuse_ = 0.7;
  mat.specular_ = 0.2;
  Sphere s1(mat);
  Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
  World w;

  EXPECT_EQ(w.light_, light);
  EXPECT_EQ(w.shapes_.size(), 2);
  EXPECT_EQ(*dynamic_cast<const Sphere*>(w.shapes_[0]), s1);
  EXPECT_EQ(*dynamic_cast<const Sphere*>(w.shapes_[1]), s2);
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

TEST(WorldTest, ShadedIntersectionOnOutside_HasCorrectColor) {
  World w;
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  Intersection i(4, w.shapes_[0]);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(w.shade_hit(comps), Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadedIntersectionOnInside_HasCorrectColor) {
  World w;
  w.light_ = PointLight(Tuple::Point(0, 0.25, 0), Color::White());
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  Intersection i(0.5, w.shapes_[1]);  // smaller inner sphere
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
  Sphere s1(Material(Color(0.8, 1.0, 0.6), 0.7, 0.2));
  s1.material_.ambient_ = 1.0;
  Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
  s2.material_.ambient_ = 1.0;
  World w;
  w.shapes_ = {&s1, &s2};
  Ray r(Tuple::Point(0, 0, 0.75), Tuple::Vector(0, 0, -1));

  EXPECT_EQ(w.color_at(r), Material().color_);
}

TEST(WorldTest, NoObjectColinearWithLightAndPoint_NotInShadow) {
  World w;
  Tuple p = Tuple::Point(0, 10, 0);

  EXPECT_FALSE(w.is_shadowed(p));
}

TEST(WorldTest, WhenSphereBetweenLightAndPoint_PointIsInShadow) {
  World w;
  Tuple p = Tuple::Point(10, -10, 10);

  EXPECT_TRUE(w.is_shadowed(p));
}

TEST(WorldTest, LightBetweenPointAndSpheres_PointNotInShadow) {
  World w;
  Tuple p = Tuple::Point(-20, 20, -20);

  EXPECT_FALSE(w.is_shadowed(p));
}

TEST(WorldTest, PointBetweenLightAndSpheres_PointNotInShadow) {
  World w;
  Tuple p = Tuple::Point(-2, 2, -2);

  EXPECT_FALSE(w.is_shadowed(p));
}

TEST(WorldTest, PointInShadow_HasCorrectColor) {
  PointLight light(Tuple::Point(0, 0, -10), Color::White());
  Sphere s1;
  Sphere s2(Mat<4>::translator(0, 0, 10));
  World w({&s1, &s2}, light);
  Ray r(Tuple::Point(0, 0, 5), Tuple::Vector(0, 0, 1));
  Intersection i(4, &s2);

  Intersection::Comps comps = i.prepare_computations(r);
  EXPECT_EQ(w.shade_hit(comps), Color(0.1, 0.1, 0.1));
}

TEST(WorldTest, NonReflectiveMaterial_ReflectsBlack) {
  World w;
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  Sphere s2(Mat<4>::scaler(0.5, 0.5, 0.5));
  s2.material_.ambient_ = 1.0;
  w.shapes_[1] = &s2;
  Intersection i(1, &s2);
  Intersection::Comps comps = i.prepare_computations(r);
  Color color = w.reflected_color(comps);

  EXPECT_EQ(color, Color::Black());
}

TEST(WorldTest, ReflectiveMaterial_ReflectionHasCorrectColor) {
  World w;
  Plane shape(Mat<4>::translator(0, -1, 0));
  shape.material_.reflectivity_ = 0.5;
  // shape.transformation_ = ;
  w.shapes_.push_back(&shape);
  Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  Intersection i(sqrt(2), &shape);
  Intersection::Comps comps = i.prepare_computations(r);
  Color color = w.reflected_color(comps);

  EXPECT_EQ(color, Color(0.190332, 0.237915, 0.142749));
}

TEST(WorldTest, ReflectiveMaterial_ShadedReflectionHasCorrectColor) {
  World w;
  Plane shape(Mat<4>::translator(0, -1, 0));
  shape.material_.reflectivity_ = 0.5;
  w.shapes_.push_back(&shape);
  Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  Intersection i(sqrt(2), &shape);
  Intersection::Comps comps = i.prepare_computations(r);
  Color color = w.shade_hit(comps);

  EXPECT_EQ(color, Color(0.876757, 0.92434, 0.829174));
}

TEST(WorldTest, InfiniteReflections_AreAvoided) {
  World w;
  w.shapes_.clear();
  w.light_ = PointLight(Tuple::Origin(), Color(1, 1, 1));
  Plane lower;
  lower.material_.reflectivity_ = 1.0;
  lower.set_transformation(Mat<4>::translator(0, -1, 0));
  w.shapes_.push_back(&lower);
  Plane upper;
  upper.material_.reflectivity_ = 1.0;
  upper.set_transformation(Mat<4>::translator(0, 1, 0));
  w.shapes_.push_back(&upper);
  Ray r(Tuple::Origin(), Tuple::Vector(0, 1, 0));
  w.color_at(r).print();

  EXPECT_EXIT(
      {
        static_cast<void>(w.color_at(r));
        std::exit(0);
      },
      testing::ExitedWithCode(0), "");
}

TEST(WorldTest, ReflectedColorAtMaxRecursionLimit_DoesNothing) {
  World w;
  Plane shape;
  shape.material_.reflectivity_ = 0.5;
  shape.set_transformation(Mat<4>::translator(0, -1, 0));
  w.shapes_.push_back(&shape);
  Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  Intersection i(sqrt(2), &shape);
  Intersection::Comps comps = i.prepare_computations(r);

  EXPECT_EQ(w.reflected_color(comps, 0), Color::Black());
}

TEST(WorldTest, RefractedColorOfOpaqueSurface_IsBlack) {
  World w;
  const Shape* shape = w.shapes_[0];
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  std::vector<Intersection> xs = {{4.0, shape}, {6.0, shape}};
  Intersection::Comps comps = xs[0].prepare_computations(r, xs);

  EXPECT_EQ(w.refracted_color(comps, 5), Color::Black());
}

TEST(WorldTest, RefractedColorAtMaximumRecursiveDepth_IsBlack) {
  World w;
  Sphere s1;
  s1.material_.transparency_ = 1.0;
  s1.material_.refract_ = 1.5;
  w.shapes_[0] = &s1;
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  std::vector<Intersection> xs = {{4, &s1}, {6, &s1}};
  Intersection::Comps comps = xs[0].prepare_computations(r, xs);

  EXPECT_EQ(w.refracted_color(comps, 0), Color::Black());
}

TEST(WorldTest, TotalInternalReflection_IsBlack) {
  World w;
  Sphere shape;
  shape.material_.transparency_ = 1.0;
  shape.material_.refract_ = 1.5;
  w.shapes_[0] = &shape;
  Ray r(Tuple::Point(0, 0, sqrt(2) / 2), Tuple::Vector(0, 1, 0));
  std::vector<Intersection> xs = {{-sqrt(2) / 2, &shape},
                                  {sqrt(2) / 2, &shape}};
  Intersection::Comps comps = xs[1].prepare_computations(r, xs);

  EXPECT_EQ(w.refracted_color(comps, 5), Color::Black());
}

class TestPattern : public Pattern {
 private:
  [[nodiscard]] Color pattern_at(Tuple point) const override {
    return {point.x_, point.y_, point.z_};
  }
};

TEST(WorldTest, NormalRefraction_HasCorrectColor) {
  World w;

  Sphere A;
  TestPattern pat;
  A.material_.ambient_ = 1.0;
  A.material_.pattern_ = &pat;
  w.shapes_[0] = &A;

  Sphere B;
  B.material_.transparency_ = 1.0;
  B.material_.refract_ = 1.5;
  w.shapes_[1] = &B;

  Ray r(Tuple::Point(0, 0, 0.1), Tuple::Vector(0, 1, 0));
  std::vector<Intersection> xs = {
      {-0.9899, &A}, {-0.4899, &B}, {0.4899, &B}, {0.9899, &A}};
  Intersection::Comps comps = xs[2].prepare_computations(r, xs);

  EXPECT_EQ(w.refracted_color(comps, 5), Color(0, 0.998875, 0.047219));
}

TEST(WorldTest, ShadedRefractionWithTransparentMaterial_HasCorrectColor) {
  World w;
  Plane floor(Mat<4>::translator(0, -1, 0));
  floor.material_.transparency_ = 0.5;
  floor.material_.refract_ = 1.5;
  w.shapes_.push_back(&floor);

  Sphere ball(Mat<4>::translator(0, -3.5, -0.5));
  ball.material_.color_ = Color::Red();
  ball.material_.ambient_ = 0.5;
  w.shapes_.push_back(&ball);

  Ray r(Tuple::Point(0, 0, -3), Tuple::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
  std::vector<Intersection> xs = {{sqrt(2), &floor}};
  Intersection::Comps comps = xs[0].prepare_computations(r, xs);
  w.shade_hit(comps, 5).print();

  EXPECT_EQ(w.shade_hit(comps, 5), Color(0.93642, 0.68642, 0.68642));
}