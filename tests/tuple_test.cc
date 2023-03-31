#include <gtest/gtest.h>
#include <tuple.h>

TEST(TupleTest, PointFromTupleructor_HasRightComponents) {
  Tuple t(4.3, -4.2, 3.1, 1);

  EXPECT_DOUBLE_EQ(t.x, 4.3);
  EXPECT_DOUBLE_EQ(t.y, -4.2);
  EXPECT_DOUBLE_EQ(t.z, 3.1);
  EXPECT_EQ(t.w, 1);
  EXPECT_TRUE(t.isPoint());
  EXPECT_FALSE(t.isVector());
}

TEST(TupleTest, PointFromFactory_HasRightComponents) {
  Tuple t = Tuple::Point(4, -4, 3);

  EXPECT_DOUBLE_EQ(t.x, 4);
  EXPECT_DOUBLE_EQ(t.y, -4);
  EXPECT_DOUBLE_EQ(t.z, 3);
  EXPECT_EQ(t.w, 1);
  EXPECT_TRUE(t.isPoint());
  EXPECT_FALSE(t.isVector());
}

TEST(TupleTest, VectorFromTupleructor_HasRightComponents) {
  Tuple t(4.3, -4.2, 3.1, 0);

  EXPECT_DOUBLE_EQ(t.x, 4.3);
  EXPECT_DOUBLE_EQ(t.y, -4.2);
  EXPECT_DOUBLE_EQ(t.z, 3.1);
  EXPECT_EQ(t.w, 0);
  EXPECT_FALSE(t.isPoint());
  EXPECT_TRUE(t.isVector());
}

TEST(TupleTest, VectorFromFactory_HasRightComponents) {
  Tuple t = Tuple::Vector(4, -4, 3);

  EXPECT_DOUBLE_EQ(t.x, 4);
  EXPECT_DOUBLE_EQ(t.y, -4);
  EXPECT_DOUBLE_EQ(t.z, 3);
  EXPECT_EQ(t.w, 0);
  EXPECT_FALSE(t.isPoint());
  EXPECT_TRUE(t.isVector());
}

TEST(TupleTest, IdenticalTuples_AreEqual) {
  Tuple a(0.5, 1.5, 2.5, 1);
  Tuple b(0.5, 1.5, 2.5, 1);
  Tuple c(0.6, 1.5, 2.5, 1);

  EXPECT_EQ(a, b);
  EXPECT_NE(b, c);
}

TEST(TupleTest, PointPlusVector_GivesPoint) {
  Tuple p(3, -2, 5, 1);
  Tuple v(-2, 3, 1, 0);
  Tuple res(1, 1, 6, 1);

  EXPECT_EQ(p + v, res);
}

TEST(TupleTest, PointMinusPoint_GivesVector) {
  Tuple p1 = Tuple::Point(3, 2, 1);
  Tuple p2 = Tuple::Point(5, 6, 7);
  Tuple res = Tuple::Vector(-2, -4, -6);

  EXPECT_EQ(p1 - p2, res);
}

TEST(TupleTest, PointMinusVector_GivesPoint) {
  Tuple p = Tuple::Point(3, 2, 1);
  Tuple v = Tuple::Vector(5, 6, 7);
  Tuple res = Tuple::Point(-2, -4, -6);

  EXPECT_EQ(p - v, res);
}

TEST(TupleTest, VectorMinusVector_GivesVector) {
  Tuple v1 = Tuple::Vector(3, 2, 1);
  Tuple v2 = Tuple::Vector(5, 6, 7);
  Tuple res = Tuple::Vector(-2, -4, -6);

  EXPECT_EQ(v1 - v2, res);
}

TEST(TupleTest, ZeroVectorMinusOtherVector_NegatesOther) {
  Tuple zeroVec = Tuple::Vector(0, 0, 0);
  Tuple v = Tuple::Vector(1, -2, 3);
  Tuple res = Tuple::Vector(-1, 2, -3);

  EXPECT_EQ(zeroVec - v, res);
}

TEST(TupleTest, NegatingTuple_NegatesAllComponents) {
  Tuple t(1, -2, 3, -4);
  Tuple res(-1, 2, -3, 4);

  EXPECT_EQ(-t, res);
}