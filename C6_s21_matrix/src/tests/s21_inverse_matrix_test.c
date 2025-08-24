#include "tests.h"

START_TEST(s21_inverse_matrix_1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  int ret = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(ret, OK);

  double expected[3][3] = {
      {-24.0, 18.0, 5.0}, {20.0, -15.0, -4.0}, {-5.0, 4.0, 1.0}};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 4.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.25, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[1][1] = 1.0;
  A.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&A, &result), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 4.0; // det = 0

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_5) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_6) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_7) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4.0;
  A.matrix[0][1] = 7.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 6.0;

  // det = 4*6 - 7*2 = 24 - 14 = 10
  // A⁻¹ = (1/10) * [6 -7; -2 4] = [0.6 -0.7; -0.2 0.4]

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_inverse_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_inverse_matrix_1);
  tcase_add_test(tc_core, s21_inverse_matrix_2);
  tcase_add_test(tc_core, s21_inverse_matrix_3);
  tcase_add_test(tc_core, s21_inverse_matrix_4);
  tcase_add_test(tc_core, s21_inverse_matrix_5);
  tcase_add_test(tc_core, s21_inverse_matrix_6);
  tcase_add_test(tc_core, s21_inverse_matrix_7);

  suite_add_tcase(s, tc_core);
  return s;
}