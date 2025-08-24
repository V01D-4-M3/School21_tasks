#include "../s21_matrix.h"

static int validate_transpose_input(const matrix_t *A, const matrix_t *result) {
  if (A == NULL || result == NULL) {
    return 0;
  }
  return (A->matrix != NULL);
}

static int create_transpose_matrix(const matrix_t *A, matrix_t *result) {
  return s21_create_matrix(A->columns, A->rows, result);
}

static void perform_transpose(const matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (!validate_transpose_input(A, result)) {
    status = INCORRECT_MATRIX;
  } else {
    status = create_transpose_matrix(A, result);
    if (status == OK) {
      perform_transpose(A, result);
    }
  }

  return status;
}