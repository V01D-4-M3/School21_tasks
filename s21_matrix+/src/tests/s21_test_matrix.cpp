#include "../s21_matrix_oop.h"
#include <gtest/gtest.h>

TEST(MatrixTest, CreateMatrixDefault) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.getRows(), 0);
  EXPECT_EQ(matrix.getCols(), 0);
}

TEST(MatrixTest, CreateMatrixWithSize) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_DOUBLE_EQ(matrix(i, j), 0.0);
    }
  }
}

TEST(MatrixTest, CreateMatrixInvalidSize) {
  EXPECT_THROW(S21Matrix matrix(0, 5), std::length_error);
  EXPECT_THROW(S21Matrix matrix(5, 0), std::length_error);
  EXPECT_THROW(S21Matrix matrix(-1, 5), std::length_error);
}

TEST(MatrixTest, CreateMatrixCopy) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(matrix1);
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 4.0);
}

TEST(MatrixTest, CreateMatrixMove) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;

  S21Matrix matrix2(std::move(matrix1));
  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.0);
  EXPECT_EQ(matrix1.getRows(), 0);
  EXPECT_EQ(matrix1.getCols(), 0);
}

TEST(MatrixTest, SetRowsIncrease) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.setRows(3);
  EXPECT_EQ(matrix.getRows(), 3);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(2, 1), 0.0);
}

TEST(MatrixTest, SetRowsDecrease) {
  S21Matrix matrix(3, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 6.0;

  matrix.setRows(2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
}

TEST(MatrixTest, SetRowsInvalid) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.setRows(0), std::length_error);
  EXPECT_THROW(matrix.setRows(-1), std::length_error);
}

TEST(MatrixTest, SetColsIncrease) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.setCols(3);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 3);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 2), 0.0);
}

TEST(MatrixTest, SetColsDecrease) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  matrix.setCols(2);
  EXPECT_EQ(matrix.getRows(), 2);
  EXPECT_EQ(matrix.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 5.0);
}

TEST(MatrixTest, SetColsInvalid) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.setCols(0), std::length_error);
  EXPECT_THROW(matrix.setCols(-1), std::length_error);
}

TEST(MatrixTest, EqMatrixTrue) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixFalse) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 5.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, EqMatrixDifferentSizes) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 3);

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(MatrixTest, SumMatrixValid) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1.SumMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(MatrixTest, SumMatrixInvalid) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 3);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::logic_error);
}

TEST(MatrixTest, SubMatrixValid) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 8.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  matrix1.SubMatrix(matrix2);

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 4.0);
}

TEST(MatrixTest, SubMatrixInvalid) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 3);

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::logic_error);
}

TEST(MatrixTest, MulNumberValid) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

TEST(MatrixTest, MulMatrixValid) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 154.0);
}

TEST(MatrixTest, MulMatrixInvalid) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::logic_error);
}

TEST(MatrixTest, TransposeValid) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.getRows(), 3);
  EXPECT_EQ(result.getCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

TEST(MatrixTest, Determinant1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), 5.0);
}

TEST(MatrixTest, Determinant2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), -2.0);
}

TEST(MatrixTest, Determinant3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), 0.0);
}

TEST(MatrixTest, DeterminantInvalid) {
  S21Matrix matrix(2, 3);

  EXPECT_THROW(matrix.Determinant(), std::logic_error);
}

TEST(MatrixTest, CalcComplements2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix.CalcComplements();

  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 1.0);
}

TEST(MatrixTest, CalcComplements3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 4.0;
  matrix(1, 2) = 2.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 2.0;
  matrix(2, 2) = 1.0;

  S21Matrix result = matrix.CalcComplements();

  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(result(0, 2), -20.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -14.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 8.0);
  EXPECT_DOUBLE_EQ(result(2, 0), -8.0);
  EXPECT_DOUBLE_EQ(result(2, 1), -2.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 4.0);
}

TEST(MatrixTest, CalcComplementsInvalid) {
  S21Matrix matrix(2, 3);

  EXPECT_THROW(matrix.CalcComplements(), std::logic_error);
}

TEST(MatrixTest, InverseMatrix2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_DOUBLE_EQ(result(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(result(1, 1), -0.5);
}

TEST(MatrixTest, InverseMatrix3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 2.0;
  matrix(0, 1) = 5.0;
  matrix(0, 2) = 7.0;
  matrix(1, 0) = 6.0;
  matrix(1, 1) = 3.0;
  matrix(1, 2) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = -2.0;
  matrix(2, 2) = -3.0;

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -1.0);
  EXPECT_DOUBLE_EQ(result(0, 2), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -38.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 41.0);
  EXPECT_DOUBLE_EQ(result(1, 2), -34.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 27.0);
  EXPECT_DOUBLE_EQ(result(2, 1), -29.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 24.0);
}

TEST(MatrixTest, InverseMatrixInvalid) {
  S21Matrix matrix1(2, 3);
  EXPECT_THROW(matrix1.InverseMatrix(), std::logic_error);

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 2.0;
  matrix2(1, 1) = 4.0;

  EXPECT_THROW(matrix2.InverseMatrix(), std::logic_error);
}

TEST(MatrixTest, OperatorPlus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 + matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(MatrixTest, OperatorMinus) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 8.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  S21Matrix result = matrix1 - matrix2;

  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST(MatrixTest, OperatorMultiplyNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix result = matrix * 2.0;

  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST(MatrixTest, OperatorMultiplyMatrix) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix result = matrix1 * matrix2;

  EXPECT_EQ(result.getRows(), 2);
  EXPECT_EQ(result.getCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 154.0);
}

TEST(MatrixTest, OperatorEqual) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(MatrixTest, OperatorAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2 = matrix1;

  EXPECT_EQ(matrix2.getRows(), 2);
  EXPECT_EQ(matrix2.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 4.0);
}

TEST(MatrixTest, OperatorPlusAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  matrix1 += matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(MatrixTest, OperatorMinusAssignment) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 5.0;
  matrix1(0, 1) = 6.0;
  matrix1(1, 0) = 7.0;
  matrix1(1, 1) = 8.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  matrix1 -= matrix2;

  EXPECT_DOUBLE_EQ(matrix1(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 4.0);
}

TEST(MatrixTest, OperatorMultiplyNumberAssignment) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix *= 2.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

TEST(MatrixTest, OperatorMultiplyMatrixAssignment) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  matrix1 *= matrix2;

  EXPECT_EQ(matrix1.getRows(), 2);
  EXPECT_EQ(matrix1.getCols(), 2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 58.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 64.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 139.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 154.0);
}

TEST(MatrixTest, OperatorParentheses) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 4.0);
}

TEST(MatrixTest, OperatorParenthesesConst) {
  const S21Matrix matrix(2, 2);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 0.0);
}

TEST(MatrixTest, OperatorParenthesesInvalid) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix(2, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 2), std::out_of_range);
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}