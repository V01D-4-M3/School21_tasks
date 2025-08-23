#include "../s21_matrix.h"

static int should_cleanup(matrix_t *A) {
  return (A != NULL && A->matrix != NULL);
}

static void free_matrix_rows(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
}

static void reset_matrix(matrix_t *A) {
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

void s21_remove_matrix(matrix_t *A) {
  if (should_cleanup(A)) {
    free_matrix_rows(A);
    reset_matrix(A);
  }
}
