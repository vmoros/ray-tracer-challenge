#include <gtest/gtest.h>
#include <helpers.h>
#include <intersection.h>
#include <material.h>
#include <matrix.h>
#include <ray.h>
#include <shape.h>
#include <tuple.h>

#include <cmath>
#include <vector>

static Ray saved_ray;

class TestShape : public Shape {
 public:
  TestShape(Mat<4> transformation) : Shape(transformation, Material()) {}
  TestShape() = default;

 private:
  std::vector<Intersection> local_intersect(Ray r) const override {
    saved_ray = r;
    return {};
  }
  Tuple local_normal_at(Tuple point) const override {
    point.w_ = 0;
    return point;
  }
};

TEST(ShapeTest, DefaultTransformationInShape_IsIdentity) {
  TestShape s;

  EXPECT_EQ(s.inverse_.inverse(), Mat<4>::iden());
}

TEST(ShapeTest, TransformationAssignedToShape_IsPreserved) {
  TestShape s;
  Mat<4> mat = Mat<4>::translator(2, 3, 4);
  s.set_transformation(mat);

  EXPECT_EQ(s.inverse_.inverse(), mat);
}

TEST(ShapeTest, DefaultMaterialInShape_IsNoArgMaterial) {
  TestShape s;
  EXPECT_EQ(s.material_, Material());
}

TEST(ShapeTest, MaterialAssignedToShape_IsPreserved) {
  TestShape s;
  Material m;
  m.ambient_ = 1.0;
  s.material_ = m;

  EXPECT_EQ(s.material_, m);
}

TEST(ShapeTest, IntersectionWithScaledShape_IsTransformed) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  TestShape s(Mat<4>::scaler(2, 2, 2));
  std::vector<Intersection> xs = s.intersect(r);

  EXPECT_EQ(saved_ray.origin_, Tuple::Point(0, 0, -2.5));
  EXPECT_EQ(saved_ray.direction_, Tuple::Vector(0, 0, 0.5));
}

TEST(ShapeTest, IntersectionWithTranslatedShape_IsTransformed) {
  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  TestShape s(Mat<4>::translator(5, 0, 0));
  std::vector<Intersection> xs = s.intersect(r);

  EXPECT_EQ(saved_ray.origin_, Tuple::Point(-5, 0, -5));
  EXPECT_EQ(saved_ray.direction_, Tuple::Vector(0, 0, 1));
}

TEST(ShapeTest, NormalOnTranslatedShape_IsTransformed) {
  TestShape s(Mat<4>::translator(0, 1, 0));
  Tuple n = s.normal_at(Tuple::Point(0, 1.70711, -0.70711));

  EXPECT_EQ(n, Tuple::Vector(0, 0.70711, -0.70711));
}

TEST(ShapeTest, NormalOnTransformedShape_IsTransformed) {
  TestShape s(Mat<4>::scaler(1, 0.5, 1) * Mat<4>::rotator_z(PI / 5));
  Tuple n = s.normal_at(Tuple::Point(0, sqrt(2) / 2, -sqrt(2) / 2));

  EXPECT_EQ(n, Tuple::Vector(0, 0.97014, -0.24254));
}