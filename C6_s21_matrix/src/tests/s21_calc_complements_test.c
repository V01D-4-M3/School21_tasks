#include "tests.h"

#include "tests.h"

START_TEST(s21_calc_complements_1) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0; A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0; A.matrix[1][1] = 4.0; A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 5.0; A.matrix[2][1] = 2.0; A.matrix[2][2] = 1.0;

  expected.matrix[0][0] =  0;   // (4*1 - 2*2)
  expected.matrix[0][1] =  10;  // -(0*1 - 2*5) = -(-10) = 10
  expected.matrix[0][2] = -20;  // (0*2 - 4*5) = -20 → (+)

  expected.matrix[1][0] =  4;   // -(2*1 - 3*2) = -(2 - 6) = -(-4) = 4
  expected.matrix[1][1] = -14;  // (1*1 - 3*5) = 1 - 15 = -14
  expected.matrix[1][2] =  8;   // -(1*2 - 2*5) = -(2 - 10) = -(-8) = 8

  expected.matrix[2][0] = -8;   // (2*2 - 3*4) = 4 - 12 = -8
  expected.matrix[2][1] = -2;   // -(1*2 - 3*0) = -2
  expected.matrix[2][2] =  4;   // (1*4 - 2*0) = 4

  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST


START_TEST(s21_calc_complements_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 42.0;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);  // C₀₀ = 1

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0; A.matrix[1][1] = 4.0;
  // C₀₀ = +det([4]) = 4
  // C₀₁ = -det([3]) = -3
  // C₁₀ = -det([2]) = -2
  // C₁₁ = +det([1]) = 1
  expected.matrix[0][0] =  4.0;
  expected.matrix[0][1] = -3.0;
  expected.matrix[1][0] = -2.0;
  expected.matrix[1][1] =  1.0;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][2], 1.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, 1e-6);
  matrix_t expected = {0};
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = expected.matrix[1][1] = expected.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_eq_matrix(&result, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(s21_calc_complements_5) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_6) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_calc_complements(NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_7) {
  matrix_t A = {0};  // rows = 0, cols = 0
  matrix_t result = {0};

  ck_assert_int_eq(s21_calc_complements(&A, &result), INCORRECT_MATRIX);
}
END_TEST

Suite *s21_calc_complements_suite(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_calc_complements_1);
  tcase_add_test(tc_core, s21_calc_complements_2);
  tcase_add_test(tc_core, s21_calc_complements_3);
  tcase_add_test(tc_core, s21_calc_complements_4);
  tcase_add_test(tc_core, s21_calc_complements_5);
  tcase_add_test(tc_core, s21_calc_complements_6);
  tcase_add_test(tc_core, s21_calc_complements_7);

  suite_add_tcase(s, tc_core);

  return s;
}