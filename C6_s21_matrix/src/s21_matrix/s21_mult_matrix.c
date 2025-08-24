#include "../s21_matrix.h"

static int are_dimensions_compatible_for_multiplication(const matrix_t *A,
                                                        const matrix_t *B) {
  return (A->columns == B->rows);
}

static int create_multiplication_result_matrix(const matrix_t *A,
                                               const matrix_t *B,
                                               matrix_t *result) {
  return s21_create_matrix(A->rows, B->columns, result);
}

static void multiply_matrices(const matrix_t *A, const matrix_t *B,
                              matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0.0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;

  if (!is_valid_input(A, B, result)) {
    status = INCORRECT_MATRIX;
  } else if (!are_dimensions_compatible_for_multiplication(A, B)) {
    status = CALCULATION_ERROR;
  } else {
    status = create_multiplication_result_matrix(A, B, result);
    if (status == OK) {
      multiply_matrices(A, B, result);
    }
  }

  return status;
}