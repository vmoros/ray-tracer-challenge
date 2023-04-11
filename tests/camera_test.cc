#include <camera.h>
#include <color.h>
#include <gtest/gtest.h>
#include <helpers.h>
#include <matrix.h>
#include <world.h>

#include <cmath>

TEST(CameraTest, BasicCamera_HasCorrectComponents) {
  Camera c(160, 120, PI / 2);

  EXPECT_EQ(c.hsize_, 160);
  EXPECT_EQ(c.vsize_, 120);
  EXPECT_DOUBLE_EQ(c.fov_, PI / 2);
  EXPECT_EQ(c.transform_, Mat<4>::iden());
}

TEST(CameraTest, PixelSizes_AreCorrect) {
  Camera c1(200, 125, PI / 2);
  Camera c2(125, 200, PI / 2);

  EXPECT_DOUBLE_EQ(c1.pixel_size_, 0.01);
  EXPECT_DOUBLE_EQ(c2.pixel_size_, 0.01);
}

TEST(CameraTest, RayThroughCenterOfCanvas_HasCorrectComponents) {
  Camera c(201, 101, PI / 2);
  Ray r = c.ray_for_pixel(100, 50);

  EXPECT_EQ(r.origin_, Tuple::Point(0, 0, 0));
  EXPECT_EQ(r.direction_, Tuple::Vector(0, 0, -1));
}

TEST(CameraTest, RayThroughCornerOfCanvas_HasCorrectComponents) {
  Camera c(201, 101, PI / 2);
  Ray r = c.ray_for_pixel(0, 0);

  EXPECT_EQ(r.origin_, Tuple::Point(0, 0, 0));
  EXPECT_EQ(r.direction_, Tuple::Vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayWhenCameraIsTransformed_HasCorrectComponents) {
  Camera c(201, 101, PI / 2);
  c.transform_ = Mat<4>::rotator_y(PI / 4) * Mat<4>::translator(0, -2, 5);
  Ray r = c.ray_for_pixel(100, 50);

  EXPECT_EQ(r.origin_, Tuple::Point(0, 2, -5));
  EXPECT_EQ(r.direction_, Tuple::Vector(sqrt(2) / 2, 0, -sqrt(2) / 2));
}

TEST(CameraTest, RenderingBasicWorldWithCamera_HasCorrectComponents) {
  World w;
  Camera c(11, 11, PI / 2);
  Tuple from = Tuple::Point(0, 0, -5);
  Tuple to = Tuple::Point(0, 0, 0);
  Tuple up = Tuple::Vector(0, 1, 0);
  c.transform_ = Mat<4>::view_transform(from, to, up);
  auto image = c.render(w);

  EXPECT_EQ(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}