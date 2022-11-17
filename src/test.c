#include "test.h"
//memchr
START_TEST(memchr_test) {
  ck_assert_pstr_eq(
      memchr(memchr_args[_i].arr, memchr_args[_i].c, memchr_args[_i].n),
      s21_memchr(memchr_args[_i].arr, memchr_args[_i].c, memchr_args[_i].n));
}
END_TEST

START_TEST(extra_memchr_test) {
  ck_assert_pstr_eq(memchr("123", 1, -1), s21_memchr("123", 1, -1));
}
END_TEST

//memset
START_TEST(memset_test) {
  ck_assert_pstr_eq(
      memset(memset_args[_i].arr, memset_args[_i].c, memset_args[_i].n),
      s21_memset(memset_args[_i].arr, memset_args[_i].c, memset_args[_i].n));
}
END_TEST

//memcmp
START_TEST(memcmp_test) {
  ck_assert_int_eq(
      memcmp(memcmp_args[_i].arr, memcmp_args[_i].arr2, memcmp_args[_i].n),
      s21_memcmp(memcmp_args[_i].arr, memcmp_args[_i].arr2, memcmp_args[_i].n));
}
END_TEST

//memcpy
START_TEST(memcpy_test) {
  
  ck_assert_pstr_eq(
      memcpy(memcpy_args[_i].dest, memcpy_args[_i].src, memcpy_args[_i].n),
      s21_memcpy(memcpy_args[_i].dest, memcpy_args[_i].src, memcpy_args[_i].n));
}
END_TEST
//-------------------------------------------
TCase *create_tc(size_t index) {
  TCase *tc = tcase_create(tcases[index].name);
  tcase_set_timeout(tc, 10);
  add_cases(&tc, index);
  return tc;
}

void add_cases(TCase** tc, size_t index) {
  switch(index) {
    case 0: {
      tcase_add_loop_test(*tc, memchr_test, 0, sizeof(memchr_args) / sizeof(memchr_args[0])); 
      tcase_add_test(*tc, extra_memchr_test);
      break;
    }
    case 1: tcase_add_loop_test(*tc, memcmp_test, 0, sizeof(memcmp_args) / sizeof(memcmp_args[0])); break;
    case 2:// tcase_add_loop_test(*tc, memcpy_test, 0, sizeof(memcpy_args) / sizeof(memcpy_args[0])); break;
    case 3: break;
    default: break;//tcase_add_loop_test(*tc, memset_test, 0, sizeof(memset_args) / sizeof(memset_args[0])); break;
  }
}

Suite *create_str_suite(void) {
  Suite *str_suite = suite_create("s21_str_suite");
  size_t size = sizeof(tcases) / sizeof(tcases[0]);
  for (size_t i = 0; i < size; i++) {
    TCase *tc = create_tc(i);
    suite_add_tcase(str_suite, tc);
  }
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
