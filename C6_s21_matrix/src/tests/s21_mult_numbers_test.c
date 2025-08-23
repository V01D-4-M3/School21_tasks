#include "tests.h"


START_TEST(s21_mult_number_1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 6.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 8.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 1.0;
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, -1.0, &result), OK);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], -1.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = -2.5;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = -4.0;
  A.matrix[1][1] = 5.5;
  A.matrix[1][2] = -6.5;

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -5.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], 6.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -8.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 11.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][2], -13.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_4) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &result), INCORRECT_MATRIX);
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(s21_mult_number(&A, 2.0, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST


Suite *s21_mult_number_suite(void) {
  Suite *suite = suite_create("s21_mult_number");
  TCase *tc = tcase_create("s21_mult_number_tc");

  tcase_add_test(tc, s21_mult_number_1);
  tcase_add_test(tc, s21_mult_number_2);
  tcase_add_test(tc, s21_mult_number_3);
  tcase_add_test(tc, s21_mult_number_4);

  suite_add_tcase(suite, tc);
  return suite;
}