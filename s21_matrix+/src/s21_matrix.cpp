#include "s21_matrix.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace {
double add_op(double a, double b) { return a + b; }
double sub_op(double a, double b) { return a - b; }
} // namespace

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  validateMatrixSize(rows, cols);
  allocateMemory();
  initializeMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) { copyFrom(other); }

S21Matrix::S21Matrix(S21Matrix &&other) { moveFrom(std::move(other)); }

S21Matrix::~S21Matrix() { cleanUp(); }

void S21Matrix::validateMatrixSize(int rows, int cols) const {
  if (rows < 1 || cols < 1) {
    throw std::length_error("Matrix size must be greater than 0");
  }
}

void S21Matrix::allocateMemory() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::initializeMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0.0;
    }
  }
}

void S21Matrix::copyFrom(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  allocateMemory();

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::moveFrom(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

void S21Matrix::cleanUp() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int new_rows) {
  validateMatrixSize(new_rows, cols_);
  if (new_rows == rows_)
    return;

  S21Matrix tmp(new_rows, cols_);
  copyDataTo(tmp, std::min(rows_, new_rows), cols_);
  moveFrom(std::move(tmp));
}

void S21Matrix::setCols(int new_cols) {
  validateMatrixSize(rows_, new_cols);
  if (new_cols == cols_)
    return;

  S21Matrix tmp(rows_, new_cols);
  copyDataTo(tmp, rows_, std::min(cols_, new_cols));
  moveFrom(std::move(tmp));
}

void S21Matrix::copyDataTo(S21Matrix &target, int rows, int cols) const {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      target.matrix_[i][j] = matrix_[i][j];
    }
  }
}

bool S21Matrix::isValid() const {
  return matrix_ != nullptr && rows_ > 0 && cols_ > 0;
}

void S21Matrix::validateMatrixForOperations(const S21Matrix &other) const {
  if (!isValid() || !other.isValid()) {
    throw std::logic_error("Invalid matrix");
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("Matrix dimensions must be equal");
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  validateMatrixForOperations(other);

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  return compareMatrixElements(other);
}

bool S21Matrix::compareMatrixElements(const S21Matrix &other) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  validateMatrixForOperations(other);
  performElementWiseOperation(other, add_op);
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  validateMatrixForOperations(other);
  performElementWiseOperation(other, sub_op);
}

void S21Matrix::performElementWiseOperation(const S21Matrix &other,
                                            ElementWiseOp op) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = op(matrix_[i][j], other.matrix_[i][j]);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!isValid()) {
    throw std::logic_error("Invalid matrix");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::validateMatrixForMultiplication(const S21Matrix &other) const {
  if (!isValid() || !other.isValid()) {
    throw std::logic_error("Invalid matrix");
  }
  if (cols_ != other.rows_) {
    throw std::logic_error("Matrix A columns must be equal to matrix B rows");
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  validateMatrixForMultiplication(other);

  S21Matrix result(rows_, other.cols_);
  calculateMatrixMultiplication(other, result);
  moveFrom(std::move(result));
}

void S21Matrix::calculateMatrixMultiplication(const S21Matrix &other,
                                              S21Matrix &result) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < other.rows_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() const {
  if (!isValid()) {
    throw std::logic_error("Invalid matrix");
  }

  S21Matrix transposed(cols_, rows_);
  fillTransposedMatrix(transposed);
  return transposed;
}

void S21Matrix::fillTransposedMatrix(S21Matrix &transposed) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
}

void S21Matrix::validateSquareMatrix() const {
  if (!isValid()) {
    throw std::logic_error("Invalid matrix");
  }
  if (rows_ != cols_) {
    throw std::logic_error("Matrix must be square");
  }
}

double S21Matrix::Determinant() const {
  validateSquareMatrix();

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  if (rows_ == 2) {
    return calculate2x2Determinant();
  }

  return calculateNxNDeterminant();
}

double S21Matrix::calculate2x2Determinant() const {
  return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
}

double S21Matrix::calculateNxNDeterminant() const {
  double result = 0.0;
  int sign = 1;

  for (int i = 0; i < cols_; i++) {
    S21Matrix minor = getMinor(0, i);
    result += sign * matrix_[0][i] * minor.Determinant();
    sign = -sign;
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  validateSquareMatrix();
  validateMatrixSizeForComplements();

  S21Matrix result(rows_, cols_);
  calculateComplements(result);
  return result;
}

void S21Matrix::validateMatrixSizeForComplements() const {
  if (rows_ < 2) {
    throw std::logic_error("Matrix size must be at least 2x2 for complements");
  }
}

void S21Matrix::calculateComplements(S21Matrix &result) const {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = getMinor(i, j);
      double determinant = minor.Determinant();
      result.matrix_[i][j] = ((i + j) % 2 == 0 ? determinant : -determinant);
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  validateSquareMatrix();

  double determinant = Determinant();
  if (std::fabs(determinant) < EPS) {
    throw std::logic_error("Matrix determinant is zero");
  }

  return calculateInverse(determinant);
}

S21Matrix S21Matrix::calculateInverse(double determinant) const {
  S21Matrix complements = CalcComplements();
  S21Matrix transposed = complements.Transpose();
  transposed.MulNumber(1.0 / determinant);
  return transposed;
}

S21Matrix S21Matrix::getMinor(int excluded_row, int excluded_col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  fillMinor(excluded_row, excluded_col, minor);
  return minor;
}

void S21Matrix::fillMinor(int excluded_row, int excluded_col,
                          S21Matrix &minor) const {
  int minor_row = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == excluded_row)
      continue;

    int minor_col = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == excluded_col)
        continue;

      minor.matrix_[minor_row][minor_col] = matrix_[i][j];
      minor_col++;
    }
    minor_row++;
  }
}

double &S21Matrix::operator()(int row, int col) {
  validateIndexes(row, col);
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  validateIndexes(row, col);
  return matrix_[row][col];
}

void S21Matrix::validateIndexes(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Matrix index out of range");
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    cleanUp();
    copyFrom(other);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    cleanUp();
    moveFrom(std::move(other));
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix operator*(double number, const S21Matrix &matrix) {
  return matrix * number;
}