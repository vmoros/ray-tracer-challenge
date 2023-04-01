#include <color.h>
#include <gtest/gtest.h>

TEST(ColorTest, Color_HasExpectedComponents) {
  Color c(-0.5, 0.4, 1.7);

  EXPECT_DOUBLE_EQ(c.r(), -0.5);
  EXPECT_DOUBLE_EQ(c.g(), 0.4);
  EXPECT_DOUBLE_EQ(c.b(), 1.7);
}

TEST(ColorTest, AddingColors_Works) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color res(1.6, 0.7, 1.0);

  EXPECT_EQ(c1 + c2, res);
}

TEST(ColorTest, SubtractingColors_Works) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  Color res(0.2, 0.5, 0.5);

  EXPECT_EQ(c1 - c2, res);
}

TEST(ColorTest, ColorScalarMultiplication_Works) {
  Color c(0.2, 0.3, 0.4);
  Color res(0.4, 0.6, 0.8);

  EXPECT_EQ(c * 2.0, res);
}

TEST(ColorTest, ColorMultiplication_Works) {
  Color c1(1.0, 0.2, 0.4);
  Color c2(0.9, 1.0, 0.1);
  Color res(0.9, 0.2, 0.04);

  EXPECT_EQ(c1 * c2, res);
}