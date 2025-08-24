#include "../s21_matrix.h"

static void subtract_matrix_elements(const matrix_t *A, const matrix_t *B,
                                     matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;

  if (!is_valid_input(A, B, result)) {
    status = INCORRECT_MATRIX;
  } else if (!are_dimensions_compatible(A, B)) {
    status = CALCULATION_ERROR;
  } else {
    if (result->matrix != NULL) {
      s21_remove_matrix(result);
    }
    status = create_result_matrix(A, result);
    if (status == OK) {
      subtract_matrix_elements(A, B, result);
    }
  }

  return status;
}
