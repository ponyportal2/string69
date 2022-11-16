#include "test.h"

START_TEST(memchr_test) {
  ck_assert_pstr_eq(
      memchr(memchr_args[_i].arr, memchr_args[_i].c, memchr_args[_i].n),
      s21_memchr(memchr_args[_i].arr, memchr_args[_i].c, memchr_args[_i].n));
}
END_TEST

START_TEST(extra_memchr_test) {
  ck_assert_pstr_eq(memchr("123",1, -1),s21_memchr("123",1, -1));
}
END_TEST

TCase *create_memchr_tc(void) {
  TCase *tcase_memchr = tcase_create("memchr_test_case");
  int test_memchr_size = sizeof(memchr_args) / sizeof(memchr_args[0]);
  tcase_set_timeout(tcase_memchr, 10);
  tcase_add_test(tcase_memchr, extra_memchr_test);
  tcase_add_loop_test(tcase_memchr, memchr_test, 0, test_memchr_size);
  return tcase_memchr;
}

Suite *create_str_suite(void) {
  Suite *str_suite = suite_create("s21_str_suite");
  TCase *tcase_memchr = create_memchr_tc();
  suite_add_tcase(str_suite, tcase_memchr);

  return str_suite;
}

int main(void) {
  Suite *str_suite = create_str_suite();
  SRunner *suite_runner = srunner_create(str_suite);
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
