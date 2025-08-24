#include "../s21_matrix.h"

static int validate_inverse_input(matrix_t *A, matrix_t *result) {
  return (A != NULL && result != NULL && A->matrix != NULL && A->rows > 0 &&
          A->columns > 0);
}

static int calculate_determinant_safely(matrix_t *A, double *det) {
  int status = s21_determinant(A, det);
  if (status != OK)
    return status;
  return (*det == 0.0) ? CALCULATION_ERROR : OK;
}

static int compute_cofactors_safely(matrix_t *A, matrix_t *cofactors) {
  int status = s21_calc_complements(A, cofactors);
  if (status != OK) {
    s21_remove_matrix(cofactors);
  }
  return status;
}

static int compute_adjugate_safely(matrix_t *cofactors, matrix_t *adjugate) {
  int status = s21_transpose(cofactors, adjugate);
  if (status != OK) {
    s21_remove_matrix(adjugate);
  }
  return status;
}

static int create_and_fill_inverse(matrix_t *adjugate, double det,
                                   matrix_t *result) {
  int status = s21_create_matrix(adjugate->rows, adjugate->columns, result);
  if (status == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = adjugate->matrix[i][j] / det;
      }
    }
  }
  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;

  if (!validate_inverse_input(A, result)) {
    status = INCORRECT_MATRIX; // 1
  } else if (A->rows != A->columns) {
    status = CALCULATION_ERROR; // 2
  } else {
    double det = 0.0;
    int det_status = calculate_determinant_safely(A, &det);
    if (det_status != OK) {
      status = det_status;
    } else {
      matrix_t cofactors = {0};
      if (compute_cofactors_safely(A, &cofactors) != OK) {
        status = CALCULATION_ERROR;
      } else {
        matrix_t adjugate = {0};
        status = compute_adjugate_safely(&cofactors, &adjugate);
        s21_remove_matrix(&cofactors);
        if (status == OK) {
          status = create_and_fill_inverse(&adjugate, det, result);
          s21_remove_matrix(&adjugate);
        }
      }
    }
  }

  return status;
}