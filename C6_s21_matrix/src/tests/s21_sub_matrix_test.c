#include "tests.h"

START_TEST(s21_sub_matrix_1) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 8.0;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -4.0, 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(100, 100, &A);
  s21_create_matrix(100, 100, &B);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      A.matrix[i][j] = 5.0;
      B.matrix[i][j] = 2.0;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 3.0, 1e-6);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(1, 1, &result);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  B.matrix[0][0] = 5.0;
  B.matrix[0][1] = 6.0;
  B.matrix[1][0] = 7.0;
  B.matrix[1][1] = 8.0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], -4.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 10.5;
  A.matrix[0][1] = 20.25;
  A.matrix[1][0] = 30.75;
  A.matrix[1][1] = 40.0;

  B.matrix[0][0] = 5.5;
  B.matrix[0][1] = 6.75;
  B.matrix[1][0] = 7.25;
  B.matrix[1][1] = 8.0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 5.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 13.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 23.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 32.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_7) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = 5.0;
      B.matrix[i][j] = 5.0;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_8) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 987654321.0;
  B.matrix[0][0] = 123456789.0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 864197532.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_9) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(1, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 0.1;
  A.matrix[0][2] = 0.01;

  B.matrix[0][0] = 0.9;
  B.matrix[0][1] = 0.09;
  B.matrix[0][2] = 0.009;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.1, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.01, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.001, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_10) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 1, &B);

  A.matrix[0][0] = 100.1;
  A.matrix[1][0] = 200.2;
  A.matrix[2][0] = 300.3;

  B.matrix[0][0] = 0.1;
  B.matrix[1][0] = 0.2;
  B.matrix[2][0] = 0.3;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 100.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 200.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[2][0], 300.0, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_sub_matrix_suite(void) {
  Suite *suite = suite_create("s21_sub_matrix");
  TCase *tc = tcase_create("core");
  tcase_add_test(tc, s21_sub_matrix_1);
  tcase_add_test(tc, s21_sub_matrix_2);
  tcase_add_test(tc, s21_sub_matrix_3);
  tcase_add_test(tc, s21_sub_matrix_4);
  tcase_add_test(tc, s21_sub_matrix_5);
  tcase_add_test(tc, s21_sub_matrix_6);
  tcase_add_test(tc, s21_sub_matrix_7);
  tcase_add_test(tc, s21_sub_matrix_8);
  tcase_add_test(tc, s21_sub_matrix_9);
  tcase_add_test(tc, s21_sub_matrix_10);
  suite_add_tcase(suite, tc);
  return suite;
}