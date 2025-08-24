#include "tests.h"

START_TEST(s21_create_matrix_1) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(5, 5, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(5, 0, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(0, 5, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(-1, 3, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(3, -1, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(-1, -1, &A), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(0, 0, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t A = {0};
  int result = s21_create_matrix(INT_MAX, 1, &A);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_5) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_6) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(3, 5, &A), OK);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 5);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_7) {
  matrix_t A = {0};

  int result = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(result, OK);

  result = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(result, OK);

  result = s21_create_matrix(INT_MAX, 1000000, &A);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_8) {
  matrix_t A = {0};
  int result = s21_create_matrix(100000000, 100000000, &A);
  ck_assert_int_eq(result, INCORRECT_MATRIX);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *suite = suite_create("s21_create_matrix");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, s21_create_matrix_1);
  tcase_add_test(tc, s21_create_matrix_2);
  tcase_add_test(tc, s21_create_matrix_3);
  tcase_add_test(tc, s21_create_matrix_4);
  tcase_add_test(tc, s21_create_matrix_5);
  tcase_add_test(tc, s21_create_matrix_6);
  tcase_add_test(tc, s21_create_matrix_7);
  tcase_add_test(tc, s21_create_matrix_8);
  suite_add_tcase(suite, tc);
  return suite;
}