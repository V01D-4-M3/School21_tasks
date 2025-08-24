#include "../s21_matrix.h"

static int validate_result_pointer(matrix_t *result);
static int validate_dimensions(int rows, int columns);
static int check_memory_constraints(int rows, int columns);
static int allocate_matrix_memory(matrix_t *result, int rows, int columns);

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;

  if (!validate_result_pointer(result)) {
    status = INCORRECT_MATRIX;
  } else if (!validate_dimensions(rows, columns)) {
    status = INCORRECT_MATRIX;
  } else if (!check_memory_constraints(rows, columns)) {
    status = INCORRECT_MATRIX;
  } else {
    status = allocate_matrix_memory(result, rows, columns);
  }

  return status;
}

static int validate_result_pointer(matrix_t *result) {
  return (result != NULL);
}

static int validate_dimensions(int rows, int columns) {
  return (rows > 0 && columns > 0);
}

static int check_memory_constraints(int rows, int columns) {
  const size_t max_elements = 100000000;
  const size_t max_dimension = 10000;

  size_t s_rows = (size_t)rows;
  size_t s_columns = (size_t)columns;

  if (s_rows > max_dimension || s_columns > max_dimension) {
    return 0;
  }

  if (s_rows * s_columns > max_elements) {
    return 0;
  }

  return 1;
}

static int allocate_matrix_memory(matrix_t *result, int rows, int columns) {
  result->rows = rows;
  result->columns = columns;
  result->matrix = NULL;

  result->matrix = calloc((size_t)rows, sizeof(double *));
  if (result->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc((size_t)columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      return INCORRECT_MATRIX;
    }
  }

  return OK;
}