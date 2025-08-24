#include "tests.h"

START_TEST(s21_transpose_1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 2, &A);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[1][0] = -3.0;
  A.matrix[1][1] = -4.0;
  A.matrix[2][0] = -5.0;
  A.matrix[2][1] = -6.0;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  ck_assert_double_eq_tol(result.matrix[0][0], -1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], -5.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][2], -6.0, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 4, &A);

  A.matrix[0][0] = 7.0;
  A.matrix[0][1] = 8.0;
  A.matrix[0][2] = 9.0;
  A.matrix[0][3] = 10.0;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 4);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 7.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 8.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][0], 9.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[3][0], 10.0, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], 7.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][2], 8.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][2], 9.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_5) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.0;
  A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0;
  A.matrix[2][1] = 0.0;
  A.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&A, &result), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_transpose");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_transpose_1);
  tcase_add_test(tc_core, s21_transpose_2);
  tcase_add_test(tc_core, s21_transpose_3);
  tcase_add_test(tc_core, s21_transpose_4);
  tcase_add_test(tc_core, s21_transpose_5);
  suite_add_tcase(s, tc_core);
  return s;
}
