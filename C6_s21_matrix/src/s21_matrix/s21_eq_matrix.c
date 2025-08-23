#include "../s21_matrix.h"

static int are_matrices_valid(matrix_t *A, matrix_t *B) {
  int result =
      (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL);
  return result;
}

static int have_same_dimensions(matrix_t *A, matrix_t *B) {
  int result = (A->rows == B->rows && A->columns == B->columns);
  return result;
}

static int compare_matrix_elements(matrix_t *A, matrix_t *B) {
  int result = EQUAL;
  for (int i = 0; i < A->rows && result == EQUAL; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        result = NOT_EQUAL;
        break;
      }
    }
  }
  return result;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = NOT_EQUAL;

  if (are_matrices_valid(A, B)) {
    if (have_same_dimensions(A, B)) {
      status = compare_matrix_elements(A, B);
    } else {
      status = NOT_EQUAL;
    }
  }

  return status;
}
