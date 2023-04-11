#include <gtest/gtest.h>
#include <helpers.h>
#include <matrix.h>
#include <tuple.h>

#include <array>
#include <numbers>

TEST(MatrixTest, Mat4_HasCorrectComponents) {
  Mat<4> m({{{1, 2, 3, 4},
             {5.5, 6.5, 7.5, 8.5},
             {9, 10, 11, 12},
             {13.5, 14.5, 15.5, 16.5}}});

  EXPECT_DOUBLE_EQ(m.data_[0][0], 1.0);
  EXPECT_DOUBLE_EQ(m.data_[0][3], 4.0);
  EXPECT_DOUBLE_EQ(m.data_[1][0], 5.5);
  EXPECT_DOUBLE_EQ(m.data_[1][2], 7.5);
  EXPECT_DOUBLE_EQ(m.data_[2][2], 11.0);
  EXPECT_DOUBLE_EQ(m.data_[3][0], 13.5);
  EXPECT_DOUBLE_EQ(m.data_[3][2], 15.5);
}

TEST(MatrixTest, Mat2_HasCorrectComponents) {
  Mat<2> m({{{-3, 5}, {1, -2}}});
  EXPECT_DOUBLE_EQ(m.data_[0][0], -3.0);
  EXPECT_DOUBLE_EQ(m.data_[0][1], 5.0);
  EXPECT_DOUBLE_EQ(m.data_[1][0], 1.0);
  EXPECT_DOUBLE_EQ(m.data_[1][1], -2.0);
}

TEST(MatrixTest, Mat3_HasCorrectComponents) {
  Mat<3> m({{{-3, 5, 0}, {1, -2, -7}, {0, 1, 1}}});
  EXPECT_DOUBLE_EQ(m.data_[0][0], -3.0);
  EXPECT_DOUBLE_EQ(m.data_[1][1], -2.0);
  EXPECT_DOUBLE_EQ(m.data_[2][2], 1.0);
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

TEST(MatrixTest, Mat4MultipliedByIdentity_DoesNotChange) {
  Mat<4> a({{{0, 1, 2, 4}, {1, 2, 4, 8}, {2, 4, 8, 16}, {4, 8, 16, 32}}});

  EXPECT_EQ(a * Mat<4>::iden(), a);
}

TEST(MatrixTest, Mat4Transposed_FlipsRowsAndColumns) {
  Mat<4> a({{{0, 9, 3, 0}, {9, 8, 0, 8}, {1, 8, 5, 3}, {0, 0, 5, 8}}});
  Mat<4> res({{{0, 9, 1, 0}, {9, 8, 8, 0}, {3, 0, 5, 5}, {0, 8, 3, 8}}});

  EXPECT_EQ(a.transp(), res);
}

TEST(MatrixTest, Mat4IdentityTransposed_IsStillIdentity) {
  EXPECT_EQ(Mat<4>::iden(), Mat<4>::iden().transp());
}

TEST(MatrixTest, Mat2Determinant_IsCorrect) {
  Mat<2> a({{{1, 5}, {-3, 2}}});

  EXPECT_DOUBLE_EQ(a.det(), 17.0);
}

TEST(MatrixTest, Mat3Submatrix_IsTheCorrectMat2) {
  Mat<3> a({{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}}});
  Mat<2> res({{{-3, 2}, {0, 6}}});

  EXPECT_EQ(a.submat(0, 2), res);
}

TEST(MatrixTest, Mat4Submatrix_IsTheCorrectMat3) {
  Mat<4> a({{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}}});
  Mat<3> res({{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}}});

  EXPECT_EQ(a.submat(2, 1), res);
}

TEST(MatrixTest, MinorOfMat3_IsCorrectDeterminant) {
  Mat<3> a({{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}});
  Mat<2> submat = a.submat(1, 0);

  EXPECT_DOUBLE_EQ(submat.det(), 25.0);
  EXPECT_DOUBLE_EQ(a.minor(1, 0), 25.0);
}

TEST(MatrixTest, Mat3Cofactors_AreCorrect) {
  Mat<3> a({{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}});

  EXPECT_DOUBLE_EQ(a.minor(0, 0), -12.0);
  EXPECT_DOUBLE_EQ(a.cofactor(0, 0), -12.0);
  EXPECT_DOUBLE_EQ(a.minor(1, 0), 25.0);
  EXPECT_DOUBLE_EQ(a.cofactor(1, 0), -25.0);
}

TEST(MatrixTest, Mat3Determinant_IsCorrect) {
  Mat<3> a({{{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}}});

  EXPECT_DOUBLE_EQ(a.cofactor(0, 0), 56.0);
  EXPECT_DOUBLE_EQ(a.cofactor(0, 1), 12.0);
  EXPECT_DOUBLE_EQ(a.cofactor(0, 2), -46.0);
  EXPECT_DOUBLE_EQ(a.det(), -196.0);
}

TEST(MatrixTest, Mat4DeterminantAndCofactors_AreCorrect) {
  Mat<4> a({{{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}}});

  EXPECT_DOUBLE_EQ(a.cofactor(0, 0), 690.0);
  EXPECT_DOUBLE_EQ(a.cofactor(0, 1), 447.0);
  EXPECT_DOUBLE_EQ(a.cofactor(0, 2), 210.0);
  EXPECT_DOUBLE_EQ(a.cofactor(0, 3), 51.0);
  EXPECT_DOUBLE_EQ(a.det(), -4071.0);
}

TEST(MatrixTest, GivenMat4_IsInvertible) {
  Mat<4> a({{{6, 4, 4, 4}, {5, 5, 7, 6}, {4, -9, 3, -7}, {9, 1, 7, -6}}});

  EXPECT_DOUBLE_EQ(a.det(), -2120.0);
  EXPECT_TRUE(a.isInvertible());
}

TEST(MatrixTest, GivenMat4_IsNotInvertible) {
  Mat<4> a({{{-4, 2, -2, -3}, {9, 6, 2, 6}, {0, -5, 1, -5}, {0, 0, 0, 0}}});

  EXPECT_DOUBLE_EQ(a.det(), 0.0);
  EXPECT_FALSE(a.isInvertible());
}

TEST(MatrixTest, GivenMat4_HasCorrectInverse) {
  Mat<4> a({{{-5, 2, 6, -8}, {1, -5, 1, 8}, {7, 7, -6, -7}, {1, -3, 7, 4}}});
  Mat<4> b = a.inverse();

  // res is different from the one given in the book because I needed more
  // precision so I got this from WolframAlpha
  Mat<4> res({{{0.218045, 0.451128, 0.240602, -0.0451128},
               {-0.808271, -1.45677, -0.443609, 0.520677},
               {-0.0789474, -0.223684, -0.0526316, 0.197368},
               {-0.522556, -0.81391, -0.300752, 0.306391}}});

  EXPECT_DOUBLE_EQ(a.det(), 532.0);
  EXPECT_DOUBLE_EQ(a.cofactor(2, 3), -160.0);
  EXPECT_DOUBLE_EQ(a.cofactor(3, 2), 105.0);
  EXPECT_EQ(b, res);
}

TEST(MatrixTest, GivenMat4_HasCorrectInverseV2) {
  Mat<4> a({{{8, -5, 9, 2}, {7, 5, 6, 1}, {-6, 0, 9, 6}, {-3, 0, -9, -4}}});
  Mat<4> b = a.inverse();

  Mat<4> res({{{-0.153846, -0.153846, -0.282051, -0.538462},
               {-0.0769231, 0.123077, 0.025641, 0.0307692},
               {0.358974, 0.358974, 0.435897, 0.923077},
               {-0.692308, -0.692308, -0.769231, -1.92308}}});

  EXPECT_EQ(b, res);
}

TEST(MatrixTest, GivenMat4_HasCorrectInverseV3) {
  Mat<4> a({{{9, 3, 0, 9}, {-5, -2, -6, -3}, {-4, 9, 6, 4}, {-7, 6, 6, 2}}});
  Mat<4> b = a.inverse();

  Mat<4> res({{{-0.0407407, -0.0777778, 0.144444, -0.222222},
               {-0.0777778, 0.0333333, 0.366667, -0.333333},
               {-0.0290123, -0.146296, -0.109259, 0.12963},
               {0.177778, 0.0666667, -0.266667, 0.333333}}});

  EXPECT_EQ(b, res);
}

TEST(MatrixTest, Mat4MultiplicationByInverse_UndoesMultiplication) {
  Mat<4> a({{{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}}});
  Mat<4> b({{{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}}});

  EXPECT_EQ(a * b * b.inverse(), a);
}

TEST(MatrixTest, TranslationMatrix_MovesPointByCorrectAmount) {
  Mat<4> translator = Mat<4>::translator(5, -3, 2);
  Tuple origPoint = Tuple::Point(-3, 4, 5);
  Tuple newPoint = Tuple::Point(2, 1, 7);

  EXPECT_EQ(translator * origPoint, newPoint);
}

TEST(MatrixTest, MultiplyingByInverseOfTranslation_MovesBackwards) {
  Mat<4> translator = Mat<4>::translator(5, -3, 2);
  Mat<4> invTrans = translator.inverse();
  Tuple origPoint = Tuple::Point(-3, 4, 5);
  Tuple newPoint = Tuple::Point(-8, 7, 3);

  EXPECT_EQ(invTrans * origPoint, newPoint);
}

TEST(MatrixTest, MultiplyingVectorByTranslation_DoesNotChangeTheVector) {
  Mat<4> translator = Mat<4>::translator(5, -3, 2);
  Tuple vec = Tuple::Vector(-3, 4, 5);

  EXPECT_EQ(translator * vec, vec);
}

TEST(MatrixTest, ScalingMatrix_ScalesPointCorrectly) {
  Mat<4> transform = Mat<4>::scaler(2, 3, 4);
  Tuple p = Tuple::Point(-4, 6, 8);
  Tuple res = Tuple::Point(-8, 18, 32);

  EXPECT_EQ(transform * p, res);
}

TEST(MatrixTest, ScalingMatrix_ScalesVectorCorrectly) {
  Mat<4> transform = Mat<4>::scaler(2, 3, 4);
  Tuple v = Tuple::Vector(-4, 6, 8);
  Tuple res = Tuple::Vector(-8, 18, 32);

  EXPECT_EQ(transform * v, res);
}

TEST(MatrixTest, InverseOfScaler_ScalesBackwards) {
  Mat<4> transform = Mat<4>::scaler(2, 3, 4);
  Mat<4> inv = transform.inverse();
  Tuple v = Tuple::Vector(-4, 6, 8);
  Tuple res = Tuple::Vector(-2, 2, 2);

  EXPECT_EQ(inv * v, res);
}

TEST(MatrixTest, NegativeScaler_Reflects) {
  Mat<4> transform = Mat<4>::scaler(-1, 1, 1);
  Tuple p = Tuple::Point(2, 3, 4);
  Tuple res = Tuple::Point(-2, 3, 4);

  EXPECT_EQ(transform * p, res);
}

TEST(MatrixTest, xAxisRotation_Works) {
  Tuple p = Tuple::Point(0, 1, 0);
  Mat<4> half_quarter = Mat<4>::rotator_x(PI / 4);
  Mat<4> full_quarter = Mat<4>::rotator_x(PI / 2);

  EXPECT_EQ(half_quarter * p, Tuple::Point(0, sqrt(2) / 2, sqrt(2) / 2));
  EXPECT_EQ(full_quarter * p, Tuple::Point(0, 0, 1));
}

TEST(MatrixTest, InverseOfXRotation_ReversesRotation) {
  Tuple p = Tuple::Point(0, 1, 0);
  Mat<4> half_quarter = Mat<4>::rotator_x(PI / 4);

  EXPECT_EQ(half_quarter.inverse() * p,
            Tuple::Point(0, sqrt(2) / 2, -sqrt(2) / 2));
}

TEST(MatrixTest, yAxisRotation_Works) {
  Tuple p = Tuple::Point(0, 0, 1);
  Mat<4> half_quarter = Mat<4>::rotator_y(PI / 4);
  Mat<4> full_quarter = Mat<4>::rotator_y(PI / 2);

  EXPECT_EQ(half_quarter * p, Tuple::Point(sqrt(2) / 2, 0, sqrt(2) / 2));
  EXPECT_EQ(full_quarter * p, Tuple::Point(1, 0, 0));
}

TEST(MatrixTest, zAxisRotation_Works) {
  Tuple p = Tuple::Point(0, 1, 0);
  Mat<4> half_quarter = Mat<4>::rotator_z(PI / 4);
  Mat<4> full_quarter = Mat<4>::rotator_z(PI / 2);

  EXPECT_EQ(half_quarter * p, Tuple::Point(-sqrt(2) / 2, sqrt(2) / 2, 0));
  EXPECT_EQ(full_quarter * p, Tuple::Point(-1, 0, 0));
}

TEST(MatrixTest, Shearing_MovesEachDimensionInProportionToEachOtherDimension) {
  Tuple p = Tuple::Point(2, 3, 4);
  Mat<4> shearXY = Mat<4>::shearer(1, 0, 0, 0, 0, 0);
  Mat<4> shearXZ = Mat<4>::shearer(0, 1, 0, 0, 0, 0);
  Mat<4> shearYX = Mat<4>::shearer(0, 0, 1, 0, 0, 0);
  Mat<4> shearYZ = Mat<4>::shearer(0, 0, 0, 1, 0, 0);
  Mat<4> shearZX = Mat<4>::shearer(0, 0, 0, 0, 1, 0);
  Mat<4> shearZY = Mat<4>::shearer(0, 0, 0, 0, 0, 1);

  EXPECT_EQ(shearXY * p, Tuple::Point(5, 3, 4));
  EXPECT_EQ(shearXZ * p, Tuple::Point(6, 3, 4));
  EXPECT_EQ(shearYX * p, Tuple::Point(2, 5, 4));
  EXPECT_EQ(shearYZ * p, Tuple::Point(2, 7, 4));
  EXPECT_EQ(shearZX * p, Tuple::Point(2, 3, 6));
  EXPECT_EQ(shearZY * p, Tuple::Point(2, 3, 7));
}

TEST(MatrixTest, ChainedTransformations_CombineInReverseOrder) {
  Tuple p = Tuple::Point(1, 0, 1);
  Mat<4> A = Mat<4>::rotator_x(PI / 2);
  Mat<4> B = Mat<4>::scaler(5, 5, 5);
  Mat<4> C = Mat<4>::translator(10, 5, 7);
  Tuple finalPoint = Tuple::Point(15, 0, 7);

  // Applying transformations one at a time and then all together
  Tuple p2 = A * p;
  Tuple p3 = B * p2;  // B * (A * p)
  Tuple p4 = C * p3;  // C * (B * (A * p))
  Tuple allTransformations = C * B * A * p;

  EXPECT_EQ(p2, Tuple::Point(1, -1, 0));
  EXPECT_EQ(p3, Tuple::Point(5, -5, 0));
  EXPECT_EQ(p4, finalPoint);
  EXPECT_EQ(allTransformations, finalPoint);
}

TEST(MatrixTest, DefaultTransformationMatrix_HasCorrectComponents) {
  Tuple from = Tuple::Point(0, 0, 0);
  Tuple to = Tuple::Point(0, 0, -1);
  Tuple up = Tuple::Vector(0, 1, 0);

  EXPECT_EQ(Mat<4>::view_transform(from, to, up), Mat<4>::iden());
}

TEST(MatrixTest, TransformationLookingAtPositiveZ_Mirrors) {
  Tuple from = Tuple::Point(0, 0, 0);
  Tuple to = Tuple::Point(0, 0, 1);
  Tuple up = Tuple::Vector(0, 1, 0);

  EXPECT_EQ(Mat<4>::view_transform(from, to, up), Mat<4>::scaler(-1, 1, -1));
}

TEST(MatrixTest, TransformationLookingAtOriginFromZAxis_MovesTheWorld) {
  Tuple from = Tuple::Point(0, 0, 8);
  Tuple to = Tuple::Point(0, 0, 0);
  Tuple up = Tuple::Vector(0, 1, 0);

  EXPECT_EQ(Mat<4>::view_transform(from, to, up), Mat<4>::translator(0, 0, -8));
}

TEST(MatrixTest, ArbitraryViewTransformation_HasCorrectComponents) {
  Tuple from = Tuple::Point(1, 3, 2);
  Tuple to = Tuple::Point(4, -2, 8);
  Tuple up = Tuple::Vector(1, 1, 0);
  Mat<4> res({{{-0.50709, 0.50709, 0.67612, -2.36643},
               {0.76772, 0.60609, 0.12122, -2.82843},
               {-0.35857, 0.59761, -0.71714, 0.0},
               {0.0, 0.0, 0.0, 1.0}}});

  EXPECT_EQ(Mat<4>::view_transform(from, to, up), res);
}
