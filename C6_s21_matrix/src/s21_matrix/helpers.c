#include "../s21_matrix.h"

int is_valid_input(const matrix_t *A, const matrix_t *B,
                   const matrix_t *result) {
  return (A != NULL && B != NULL && result != NULL && A->matrix != NULL &&
          B->matrix != NULL);
}

