#include <color.h>
#include <gtest/gtest.h>
#include <matrix.h>
#include <pattern.h>
#include <sphere.h>
#include <tuple.h>

static Color white = Color::White();
static Color black = Color::Black();

TEST(PatternTest, StripePattern_HasCorrectComponents) {
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.a_, white);
  EXPECT_EQ(pattern.b_, black);
}

TEST(PatternTest, StripePattern_IsConstantInY) {
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 1, 0)), white);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 2, 0)), white);
}

TEST(PatternTest, StripePattern_IsConstantInZ) {
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 0, 1)), white);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 0, 2)), white);
}

TEST(PatternTest, StripePattern_AlternatesInX) {
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(0.9, 0, 0)), white);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(1, 0, 0)), black);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(-0.1, 0, 0)), black);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(-1, 0, 0)), black);
  EXPECT_EQ(pattern.stripe_at(Tuple::Point(-1.1, 0, 0)), white);
}

TEST(PatternTest, StripesOnTransformedObject_AreColoredCorrectly) {
  Sphere object;
  object.transformation_ = Mat<4>::scaler(2, 2, 2);
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.stripe_at_object(object, Tuple::Point(1.5, 0, 0)), white);
}

TEST(PatternTest, TransformedStripesOnObject_AreColoredCorrectly) {
  Sphere object;
  StripePat pattern(white, black);
  pattern.transformation_ = Mat<4>::scaler(2, 2, 2);

  EXPECT_EQ(pattern.stripe_at_object(object, Tuple::Point(1.5, 0, 0)), white);
}

TEST(PatternTest, TransformedStripesOnTransformedObject_AreColoredCorrectly) {
  Sphere object;
  object.transformation_ = Mat<4>::scaler(2, 2, 2);
  StripePat pattern(white, black);
  pattern.transformation_ = Mat<4>::translator(0.5, 0, 0);

  EXPECT_EQ(pattern.stripe_at_object(object, Tuple::Point(2.5, 0, 0)), white);
}