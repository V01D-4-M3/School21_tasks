#include "../s21_matrix.h"

static int validate_input(const matrix_t *A, const matrix_t *result) {
  return (A != NULL && result != NULL && A->matrix != NULL);
}

static int is_square_matrix(const matrix_t *A) {
  return (A->rows == A->columns);
}

static int create_minor_matrix(const matrix_t *A, int exclude_row,
                               int exclude_col, matrix_t *minor) {
  int new_rows = A->rows - 1;
  int new_cols = A->columns - 1;

  if (new_rows <= 0 || new_cols <= 0) {
    return s21_create_matrix(0, 0, minor);
  }

  int status = s21_create_matrix(new_rows, new_cols, minor);
  if (status == OK) {
    int minor_i = 0;
    for (int i = 0; i < A->rows; i++) {
      if (i == exclude_row)
        continue;
      int minor_j = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j == exclude_col)
          continue;
        minor->matrix[minor_i][minor_j] = A->matrix[i][j];
        minor_j++;
      }
      minor_i++;
    }
  }
  return status;
}

static double calculate_cofactor_sign(int i, int j) {
  return ((i + j) % 2 == 0) ? 1.0 : -1.0;
}

static int calculate_cofactor_for_element(const matrix_t *A, matrix_t *result,
                                          int i, int j) {
  if (A->rows == 1) {
    result->matrix[i][j] = 1.0;
    return OK;
  } else {
    matrix_t minor = {0};
    int status = create_minor_matrix(A, i, j, &minor);
    if (status != OK) {
      return status;
    }

    double det = 0.0;
    status = s21_determinant(&minor, &det);
    if (status == OK) {
      result->matrix[i][j] = calculate_cofactor_sign(i, j) * det;
    }

    s21_remove_matrix(&minor);
    return status;
  }
}

static int calculate_all_cofactors(const matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      int status = calculate_cofactor_for_element(A, result, i, j);
      if (status != OK) {
        return status;
      }
    }
  }
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (!validate_input(A, result)) {
    status = INCORRECT_MATRIX;
  } else if (!is_square_matrix(A)) {
    status = CALCULATION_ERROR;
  } else {
    status = create_result_matrix(A, result);
    if (status == OK) {
      status = calculate_all_cofactors(A, result);
      if (status != OK) {
        s21_remove_matrix(result);
      }
    }
  }

  return status;
}