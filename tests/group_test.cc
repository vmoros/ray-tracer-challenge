#include <group.h>
#include <gtest/gtest.h>
#include <helpers.h>
#include <matrix.h>
#include <sphere.h>

TEST(GroupTest, DefaultGroup_IsEmpty) {
  Group g;

  EXPECT_EQ(g.inverse_, Mat<4>::iden());
  EXPECT_EQ(g.shapes_.size(), 0);
}

TEST(GroupTest, DefaultGroup_HasNoIntersections) {
  Group g;
  Ray r(Tuple::Point(0, 0, 0), Tuple::Vector(0, 0, 1));
  auto xs = g.local_intersect(r);

  EXPECT_TRUE(xs.empty());
}

TEST(GroupTest, NonEmptyGroup_HasCorrectIntersections) {
  Group g;
  Sphere s1;
  Sphere s2(Mat<4>::translator(0, 0, -3));
  Sphere s3(Mat<4>::translator(5, 0, 0));

  g.add_child(s1);
  g.add_child(s2);
  g.add_child(s3);

  Ray r(Tuple::Point(0, 0, -5), Tuple::Vector(0, 0, 1));
  auto xs = g.local_intersect(r);

  EXPECT_EQ(xs.size(), 4);
  EXPECT_EQ(*dynamic_cast<const Sphere*>(xs[0].obj_), s2);
  EXPECT_EQ(*dynamic_cast<const Sphere*>(xs[1].obj_), s2);
  EXPECT_EQ(*dynamic_cast<const Sphere*>(xs[2].obj_), s1);
  EXPECT_EQ(*dynamic_cast<const Sphere*>(xs[3].obj_), s1);
}

TEST(GroupTest, TransformationsFromGroupAndShapes_BothAreApplied) {
  Group g(Mat<4>::scaler(2, 2, 2));
  Sphere s(Mat<4>::translator(5, 0, 0));
  g.add_child(s);
  Ray r(Tuple::Point(10, 0, -10), Tuple::Vector(0, 0, 1));
  auto xs = g.intersect(r);

  EXPECT_EQ(xs.size(), 2);
}

TEST(GroupTest, ConversionFromWorldToObjectSpace_IsCorrect) {
  Group g1(Mat<4>::rotator_y(PI / 2));
  Group g2(Mat<4>::scaler(2, 2, 2));
  g1.add_child(g2);
  Sphere s(Mat<4>::translator(5, 0, 0));
  g2.add_child(s);
  world_to_object(&s, Tuple::Point(-2, 0, -10)).print();
  EXPECT_EQ(world_to_object(&s, Tuple::Point(-2, 0, -10)),
            Tuple::Point(0, 0, -1));
}

TEST(GroupTest, ConversionOfNormalFromObjectToWorldSpace_IsCorrect) {
  Group g1(Mat<4>::rotator_y(PI / 2));
  Group g2(Mat<4>::scaler(1, 2, 3));
  g1.add_child(g2);
  Sphere s(Mat<4>::translator(5, 0, 0));
  g2.add_child(s);
  normal_to_world(&s, Tuple::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3))
      .print();
  EXPECT_EQ(
      normal_to_world(&s, Tuple::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3)),
      Tuple::Vector(0.285714, 0.428571, -0.857143));
}