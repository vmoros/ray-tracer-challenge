#include <gtest/gtest.h>
#include <matrix.h>
#include <tuple.h>

#include <array>

TEST(MatrixTest, Mat4_HasCorrectComponents) {
  Mat<4> m({{{1, 2, 3, 4},
             {5.5, 6.5, 7.5, 8.5},
             {9, 10, 11, 12},
             {13.5, 14.5, 15.5, 16.5}}});

  EXPECT_EQ(m.data_[0][0], 1.0);
  EXPECT_EQ(m.data_[0][3], 4.0);
  EXPECT_EQ(m.data_[1][0], 5.5);
  EXPECT_EQ(m.data_[1][2], 7.5);
  EXPECT_EQ(m.data_[2][2], 11.0);
  EXPECT_EQ(m.data_[3][0], 13.5);
  EXPECT_EQ(m.data_[3][2], 15.5);
}

TEST(MatrixTest, Mat2_HasCorrectComponents) {
  Mat<2> m({{{-3, 5}, {1, -2}}});
  EXPECT_EQ(m.data_[0][0], -3.0);
  EXPECT_EQ(m.data_[0][1], 5.0);
  EXPECT_EQ(m.data_[1][0], 1.0);
  EXPECT_EQ(m.data_[1][1], -2.0);
}

TEST(MatrixTest, Mat3_HasCorrectComponents) {
  Mat<3> m({{{-3, 5, 0}, {1, -2, -7}, {0, 1, 1}}});
  EXPECT_EQ(m.data_[0][0], -3.0);
  EXPECT_EQ(m.data_[1][1], -2.0);
  EXPECT_EQ(m.data_[2][2], 1.0);
}

TEST(MatrixTest, IdenticalMat4s_AreEqual) {
  Mat<4> a({{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}});
  Mat<4> b({{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}});

  EXPECT_EQ(a, b);
}

TEST(MatrixTest, DifferentMat4s_AreNotEqual) {
  Mat<4> a({{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}});
  Mat<4> b({{{2, 3, 4, 5}, {6, 7, 8, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}}});

  EXPECT_NE(a, b);
}

TEST(MatrixTest, Mat4Multiplication_HasCorrectResult) {
  Mat<4> a({{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}});
  Mat<4> b({{{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}});
  Mat<4> res({{{20, 22, 50, 48},
               {44, 54, 114, 108},
               {40, 58, 110, 102},
               {16, 26, 46, 42}}});

  EXPECT_EQ(a * b, res);
}

TEST(MatrixTest, Mat4MultipliedByTuple_GivesTuple) {
  Mat<4> a({{{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}}});
  Tuple b(1, 2, 3, 1);
  Tuple res(18, 24, 33, 1);

  EXPECT_EQ(a * b, res);
}