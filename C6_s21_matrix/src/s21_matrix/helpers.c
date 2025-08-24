#include "../s21_matrix.h"

int is_valid_input(const matrix_t *A, const matrix_t *B,
                   const matrix_t *result) {
  return (A != NULL && B != NULL && result != NULL && A->matrix != NULL &&
          B->matrix != NULL);
}

int create_result_matrix(const matrix_t *A, matrix_t *result) {
  return s21_create_matrix(A->rows, A->columns, result);
}

int are_dimensions_compatible(const matrix_t *A, const matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns);
}