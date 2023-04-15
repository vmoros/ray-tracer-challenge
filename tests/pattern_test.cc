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

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 1, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 2, 0)), white);
}

TEST(PatternTest, StripePattern_IsConstantInZ) {
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 1)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 2)), white);
}

TEST(PatternTest, StripePattern_AlternatesInX) {
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0.9, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(1, 0, 0)), black);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(-0.1, 0, 0)), black);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(-1, 0, 0)), black);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(-1.1, 0, 0)), white);
}

TEST(PatternTest, StripesOnTransformedObject_AreColoredCorrectly) {
  Sphere object(Mat<4>::scaler(2, 2, 2));
  StripePat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at_shape(&object, Tuple::Point(1.5, 0, 0)), white);
}

TEST(PatternTest, TransformedStripesOnObject_AreColoredCorrectly) {
  Sphere object;
  StripePat pattern(white, black);
  pattern.set_transformation(Mat<4>::scaler(2, 2, 2));

  EXPECT_EQ(pattern.pattern_at_shape(&object, Tuple::Point(1.5, 0, 0)), white);
}

TEST(PatternTest, TransformedStripesOnTransformedObject_AreColoredCorrectly) {
  Sphere object;
  object.transformation_ = Mat<4>::scaler(2, 2, 2);
  StripePat pattern(white, black);
  pattern.set_transformation(Mat<4>::translator(0.5, 0, 0));

  EXPECT_EQ(pattern.pattern_at_shape(&object, Tuple::Point(2.5, 0, 0)), white);
}

class TestPattern : public Pattern {
 private:
  Color pattern_at(Tuple point) const override {
    return Color(point.x_, point.y_, point.z_);
  }
};

TEST(PatternTest, DefaultPattern_HasAssignableTransformation) {
  TestPattern pattern;
  EXPECT_EQ(pattern.inverse_.inverse(),
            Mat<4>::iden());  // Pattern only stores its transformation's
                              // inverse so we invert the inverse to find the
                              // original transformation

  pattern.set_transformation(Mat<4>::translator(1, 2, 3));
  EXPECT_EQ(pattern.inverse_.inverse(), Mat<4>::translator(1, 2, 3));
}

TEST(PatternTest, PatternWithObjectTransformation_TransformsCorrectly) {
  Sphere shape(Mat<4>::scaler(2, 2, 2));
  TestPattern pattern;

  EXPECT_EQ(pattern.pattern_at_shape(&shape, Tuple::Point(2, 3, 4)),
            Color(1, 1.5, 2));
}

TEST(PatternTest, PatternWithPatternTransformation_TransformsCorrectly) {
  Sphere shape;
  TestPattern pattern;
  pattern.set_transformation(Mat<4>::scaler(2, 2, 2));

  EXPECT_EQ(pattern.pattern_at_shape(&shape, Tuple::Point(2, 3, 4)),
            Color(1, 1.5, 2));
}

TEST(PatternTest,
     PatternWithObjectAndPatternTransformation_TransformsCorrectly) {
  Sphere shape(Mat<4>::scaler(2, 2, 2));
  TestPattern pattern;
  pattern.set_transformation(Mat<4>::translator(0.5, 1, 1.5));

  EXPECT_EQ(pattern.pattern_at_shape(&shape, Tuple::Point(2.5, 3, 3.5)),
            Color(0.75, 0.5, 0.25));
}

TEST(PatternTest, GradientPattern_LinearlyInterpolates) {
  GradientPat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0.25, 0, 0)),
            Color(0.75, 0.75, 0.75));
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0.75, 0, 0)),
            Color(0.25, 0.25, 0.25));
}

TEST(PatternTest, RingPattern_DependsOnXAndZ) {
  RingPat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(1, 0, 0)), black);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 1)), black);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0.708, 0, 0.708)), black);
}

TEST(PatternTest, CheckerPattern_RepeatsInX) {
  CheckerPat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0.99, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(1.01, 0, 0)), black);
}

TEST(PatternTest, CheckerPattern_RepeatsInY) {
  CheckerPat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0.99, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 1.01, 0)), black);
}

TEST(PatternTest, CheckerPattern_RepeatsInZ) {
  CheckerPat pattern(white, black);

  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 0.99)), white);
  EXPECT_EQ(pattern.pattern_at(Tuple::Point(0, 0, 1.01)), black);
}