#include "tests.h"

void s21_suit_execution(SRunner *runner, int *failed_count,
                        const char *suite_name) {
  if (!runner)
    return;
  srunner_run_all(runner, CK_NORMAL);
  int count = srunner_ntests_failed(runner);
  *failed_count += count;
  if (count == 0) {
    printf("\033[32m[✓] %s: All tests passed [✓]\033[0m\n", suite_name);
  } else {
    printf("\033[31m[✗] %s: %d tests failed [✗]\033[0m\n", suite_name, count);
  }
  printf("---------------------------------------------------\n");
  srunner_free(runner);
}

int main(void) {
  int failed_count = 0;
  s21_suit_execution(srunner_create(s21_create_matrix_suite()), &failed_count,
                     "s21_create_matrix");
  s21_suit_execution(srunner_create(s21_remove_matrix_suite()), &failed_count,
                     "s21_remove_matrix");
  s21_suit_execution(srunner_create(s21_eq_matrix_suite()), &failed_count,
                     "s21_eq_matrix");
  s21_suit_execution(srunner_create(s21_sum_matrix_suite()), &failed_count,
                     "s21_sum_matrix");
  s21_suit_execution(srunner_create(s21_sub_matrix_suite()), &failed_count,
                     "s21_sub_matrix");
  s21_suit_execution(srunner_create(s21_mult_number_suite()), &failed_count,
                     "s21_mult_number");
  s21_suit_execution(srunner_create(s21_mult_matrix_suite()), &failed_count,
                     "s21_mult_matrix");
  s21_suit_execution(srunner_create(s21_transpose_suite()), &failed_count,
                     "s21_transpose");
  s21_suit_execution(srunner_create(s21_calc_complements_suite()), &failed_count,
                     "s21_calc_complements");
  s21_suit_execution(srunner_create(s21_determinant_suite()), &failed_count,
                     "s21_determinant");
  printf("\n\033[1;36mTotal failed: %d\033[0m\n", failed_count);
  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}