#include "../s21_matrix.h"

static int validate_mult_number_input(const matrix_t *A,
                                      const matrix_t *result) {
  return (A != NULL && result != NULL && A->matrix != NULL);
}

static void multiply_matrix_by_number(const matrix_t *A, double number,
                                      matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;

  if (!validate_mult_number_input(A, result)) {
    status = INCORRECT_MATRIX;
  } else {
    status = create_result_matrix(A, result);
    if (status == OK) {
      multiply_matrix_by_number(A, number, result);
    }
  }

  return status;
}