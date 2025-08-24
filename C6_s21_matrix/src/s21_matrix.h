/*
Created by V01D-4-M3
Check my github: github.com/V01D-4-M3
*/

#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum matrix_err {
  OK = 0,
  INCORRECT_MATRIX,
  CALCULATION_ERROR,
};

#define MAX_ALLOWED_ROWS 10000
#define MAX_ALLOWED_COLUMNS 10000
#define MAX_ALLOWED_ELEMENTS ((size_t)100 * 1000 * 1000)

enum eq_matrix { NOT_EQUAL = 0, EQUAL };

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int is_valid_input(const matrix_t *A, const matrix_t *B,
                   const matrix_t *result);
int are_dimensions_compatible(const matrix_t *A, const matrix_t *B);
int create_result_matrix(const matrix_t *A, matrix_t *result);
#endif