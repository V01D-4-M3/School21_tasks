#include "tests.h"

START_TEST(s21_remove_matrix_1) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  ck_assert_ptr_nonnull(A.matrix);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(s21_remove_matrix_2) { s21_remove_matrix(NULL); }
END_TEST

START_TEST(s21_remove_matrix_3) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

Suite *s21_remove_matrix_suite(void) {
  Suite *suite = suite_create("s21_remove_matrix");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, s21_remove_matrix_1);
  tcase_add_test(tc, s21_remove_matrix_2);
  tcase_add_test(tc, s21_remove_matrix_3);
  suite_add_tcase(suite, tc);
  return suite;
}