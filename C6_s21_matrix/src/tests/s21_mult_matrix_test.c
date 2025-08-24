#include "tests.h"

START_TEST(test_mult_matrix_1) {
  matrix_t A, B, result, expected;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  B.matrix[0][0] = 7.0;
  B.matrix[0][1] = 8.0;
  B.matrix[1][0] = 9.0;
  B.matrix[1][1] = 10.0;
  B.matrix[2][0] = 11.0;
  B.matrix[2][1] = 12.0;

  expected.matrix[0][0] = 58.0;   // (1*7 + 2*9 + 3*11)
  expected.matrix[0][1] = 64.0;   // (1*8 + 2*10 + 3*12)
  expected.matrix[1][0] = 139.0; // (4*7 + 5*9 + 6*11)
  expected.matrix[1][1] = 154.0; // (4*8 + 5*10 + 6*12)

  int res = s21_mult_matrix(&A, &B, &result);
  
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), EQUAL);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 8.0;
  B.matrix[2][0] = 9.0;
  B.matrix[2][1] = 10.0;

  int res = s21_mult_matrix(&A, &B, &result);
  
  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST


Suite *s21_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_mult_matrix");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_mult_matrix_1);
  tcase_add_test(tc_core, test_mult_matrix_2);

  suite_add_tcase(s, tc_core);
  return s;
}
