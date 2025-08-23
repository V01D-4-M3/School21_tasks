#include "../s21_matrix.h"

static int is_invalid_dimensions(int rows, int columns);
static int is_too_large_for_int(int rows, int columns);
static int is_excessively_sized(int rows, int columns);
static int will_overflow_memory(int rows, int columns);
static int initialize_matrix(matrix_t *result, int rows, int columns);
static int allocate_row_pointers(matrix_t *result, int rows);
static int allocate_matrix_elements(matrix_t *result, int rows, int columns);
static void free_allocated_matrix_on_error(matrix_t *result);

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;

  if (is_invalid_dimensions(rows, columns)) {
    status = INCORRECT_MATRIX;
  } else if (is_too_large_for_int(rows, columns)) {
    status = INCORRECT_MATRIX;
  } else if (result == NULL) {
    status = INCORRECT_MATRIX;
  } else if (is_excessively_sized(rows, columns)) {
    status = INCORRECT_MATRIX;
  } else if (will_overflow_memory(rows, columns)) {
    status = INCORRECT_MATRIX;
  } else {
    status = initialize_matrix(result, rows, columns);
  }

  return status;
}

static int is_invalid_dimensions(int rows, int columns) {
  return (rows <= 0 || columns <= 0);
}

static int is_too_large_for_int(int rows, int columns) {
  return (rows > INT_MAX || columns > INT_MAX);
}

static int is_excessively_sized(int rows, int columns) {
  size_t s_rows = (size_t)rows;
  size_t s_columns = (size_t)columns;

  if (s_rows > MAX_ALLOWED_ROWS) return 1;
  if (s_columns > MAX_ALLOWED_COLUMNS) return 1;
  if (s_rows * s_columns > MAX_ALLOWED_ELEMENTS) return 1;

  return 0;
}

static int will_overflow_memory(int rows, int columns) {
  size_t s_rows = (size_t)rows;
  size_t s_columns = (size_t)columns;

  if (s_columns > SIZE_MAX / sizeof(double)) return 1;

  size_t row_size = s_columns * sizeof(double);
  if (row_size > 0 && s_rows > SIZE_MAX / row_size) return 1;

  if (s_rows > SIZE_MAX / sizeof(double *)) return 1;

  return 0;
}

static int initialize_matrix(matrix_t *result, int rows, int columns) {
  result->rows = rows;
  result->columns = columns;
  result->matrix = NULL;

  if (allocate_row_pointers(result, rows) != OK) {
    return INCORRECT_MATRIX;
  }

  if (allocate_matrix_elements(result, rows, columns) != OK) {
    free_allocated_matrix_on_error(result);
    return INCORRECT_MATRIX;
  }

  return OK;
}

static int allocate_row_pointers(matrix_t *result, int rows) {
  result->matrix = calloc((size_t)rows, sizeof(double *));
  return (result->matrix == NULL) ? INCORRECT_MATRIX : OK;
}

static int allocate_matrix_elements(matrix_t *result, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc((size_t)columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      return INCORRECT_MATRIX;
    }
  }
  return OK;
}

static void free_allocated_matrix_on_error(matrix_t *result) {
  s21_remove_matrix(result);
}