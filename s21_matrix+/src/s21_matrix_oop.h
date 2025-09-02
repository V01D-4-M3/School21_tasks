#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

class S21Matrix {
public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int getRows() const;
  int getCols() const;
  void setRows(int new_rows);
  void setCols(int new_cols);

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(double number) const;
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(double number);
  S21Matrix &operator*=(const S21Matrix &other);

  double &operator()(int row, int col);
  const double &operator()(int row, int col) const;

private:
  int rows_, cols_;
  double **matrix_;

  static constexpr double EPS = 1e-7;

  typedef double (*ElementWiseOp)(double, double);

  void validateMatrixSize(int rows, int cols) const;
  void allocateMemory();
  void initializeMatrix();
  void copyFrom(const S21Matrix &other);
  void moveFrom(S21Matrix &&other);
  void cleanUp();

  void copyDataTo(S21Matrix &target, int rows, int cols) const;
  bool isValid() const;
  void validateMatrixForOperations(const S21Matrix &other) const;
  bool compareMatrixElements(const S21Matrix &other) const;
  void performElementWiseOperation(const S21Matrix &other, ElementWiseOp op);
  void validateMatrixForMultiplication(const S21Matrix &other) const;
  void calculateMatrixMultiplication(const S21Matrix &other,
                                     S21Matrix &result) const;
  void fillTransposedMatrix(S21Matrix &transposed) const;
  void validateSquareMatrix() const;
  double calculate2x2Determinant() const;
  double calculateNxNDeterminant() const;
  void validateMatrixSizeForComplements() const;
  void calculateComplements(S21Matrix &result) const;
  S21Matrix calculateInverse(double determinant) const;
  S21Matrix getMinor(int excluded_row, int excluded_col) const;
  void fillMinor(int excluded_row, int excluded_col, S21Matrix &minor) const;
  void validateIndexes(int row, int col) const;
};

S21Matrix operator*(double number, const S21Matrix &matrix);

#endif