#include "../s21_matrix.h"

static int are_dimensions_compatible(const matrix_t *A, const matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns);
}

static int create_result_matrix(const matrix_t *A, matrix_t *result) {
  return s21_create_matrix(A->rows, A->columns, result);
}

static void add_matrix_elements(const matrix_t *A, const matrix_t *B,
                                matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;

  if (!is_valid_input(A, B, result)) {
    status = INCORRECT_MATRIX;
  } else if (!are_dimensions_compatible(A, B)) {
    status = CALCULATION_ERROR;
  } else {
    status = create_result_matrix(A, result);
    if (status == OK) {
      add_matrix_elements(A, B, result);
    }
  }

  return status;
}