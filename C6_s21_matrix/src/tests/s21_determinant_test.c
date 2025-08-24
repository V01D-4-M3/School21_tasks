#include "tests.h"  


START_TEST(s21_determinant_1) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -2.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_2) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 42.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 42.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_3) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2.0; A.matrix[0][1] = 1.0; A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 1.0; A.matrix[1][1] = 3.0; A.matrix[1][2] = 2.0;
  A.matrix[2][0] = 3.0; A.matrix[2][1] = 2.0; A.matrix[2][2] = 1.0;

  // det = 2*(3*1 - 2*2) - 1*(1*1 - 2*3) + 3*(1*2 - 3*3)
  //     = 2*(-1) - 1*(-5) + 3*(-7) = -2 + 5 - 21 = -18
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -18.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0;
  A.matrix[1][0] = 0.0; A.matrix[1][1] = 1.0; A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 0.0; A.matrix[2][1] = 0.0; A.matrix[2][2] = 1.0;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 1.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_5) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0; A.matrix[1][1] = 4.0;  

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_6) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 1.0; A.matrix[0][1] = 0.0; A.matrix[0][2] = 0.0; A.matrix[0][3] = 1.0;
  A.matrix[1][0] = 0.0; A.matrix[1][1] = 2.0; A.matrix[1][2] = 1.0; A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 0.0; A.matrix[2][1] = 1.0; A.matrix[2][2] = 2.0; A.matrix[2][3] = 0.0;
  A.matrix[3][0] = 1.0; A.matrix[3][1] = 0.0; A.matrix[3][2] = 0.0; A.matrix[3][3] = 1.0;


  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_7) {
  double result = 0.0;
  ck_assert_int_eq(s21_determinant(NULL, &result), INCORRECT_MATRIX);
}
END_TEST


START_TEST(s21_determinant_8) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_determinant(&A, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_9) {
  matrix_t A = {0};
  double result = 0.0;
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_determinant(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST


START_TEST(s21_determinant_10) {
  matrix_t A = {0};  
  double result = 0.0;

  ck_assert_int_eq(s21_determinant(&A, &result), INCORRECT_MATRIX);
}
END_TEST


Suite *s21_determinant_suite(void){
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_calc_determinant");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_determinant_1);
  tcase_add_test(tc_core, s21_determinant_2);
  tcase_add_test(tc_core, s21_determinant_3);
  tcase_add_test(tc_core, s21_determinant_4);
  tcase_add_test(tc_core, s21_determinant_5);
  tcase_add_test(tc_core, s21_determinant_6);
  tcase_add_test(tc_core, s21_determinant_7);
  tcase_add_test(tc_core, s21_determinant_8);
  tcase_add_test(tc_core, s21_determinant_9);
  tcase_add_test(tc_core, s21_determinant_10);

  suite_add_tcase(s, tc_core);
  return s;
}