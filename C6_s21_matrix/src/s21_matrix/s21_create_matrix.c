#include "../s21_matrix.h"
#include <stdlib.h>

static int validate_input(const matrix_t *result_ptr);
static int validate_dimensions(int rows, int columns);
static int allocate_matrix_data(matrix_t *result, int rows, int columns);

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;

  if (validate_input(result) != OK) {
    error = INCORRECT_MATRIX;
  } else if ((error = validate_dimensions(rows, columns)) != OK) {
  } else {
    error = allocate_matrix_data(result, rows, columns);
  }

  return error;
}

static int validate_input(const matrix_t *result_ptr) {
  return (result_ptr == NULL) ? INCORRECT_MATRIX : OK;
}

static int validate_dimensions(int rows, int columns) {
  const int MAX_SIZE = 100000;

  if (rows < 1 || columns < 1 || rows > MAX_SIZE || columns > MAX_SIZE) {
    return INCORRECT_MATRIX;
  }

  return OK;
}

static int allocate_matrix_data(matrix_t *result, int rows, int columns) {
  result->rows = 0;
  result->columns = 0;
  result->matrix = NULL;

  result->matrix = calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    return CALCULATION_ERROR;
  }

  result->rows = rows;
  result->columns = columns;

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return CALCULATION_ERROR;
    }
  }

  return OK;
}