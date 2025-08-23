#ifndef _S21_MATRIX_TEST_H_
#define _S21_MATRIX_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite *s21_create_matrix_suite(void);
Suite *s21_remove_matrix_suite(void);
Suite *s21_eq_matrix_suite(void);
Suite *s21_sum_matrix_suite(void);
Suite *s21_sub_matrix_suite(void);
Suite *s21_mult_number_suite(void);
Suite *s21_mult_matrix_suite(void);
Suite *s21_transpose_suite(void);
Suite *s21_calc_complements_suite(void);
Suite *s21_determinant_suite(void);
Suite *s21_inverse_matrix_suite(void);

void s21_suit_execution(SRunner *runner, int *failed_count,
                        const char *suite_name);
#endif