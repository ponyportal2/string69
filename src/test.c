#include "test.h"
//memchr
START_TEST(memchr_test) {
  ck_assert_pstr_eq(
      memchr(test[_i].str1, test[_i].c, test[_i].n),
      s21_memchr(test[_i].str1, test[_i].c, test[_i].n));
}
END_TEST

START_TEST(extra_memchr_test) { //failed: memchr("123", 1, -1) == " ", s21_memchr("123", 1, -1) == ""
  ck_assert_pstr_eq(memchr("123", 1, -1), s21_memchr("123", 1, -1));
}
END_TEST

//memset
START_TEST(memset_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      memset(str1, test[_i].c, test[_i].n),
      s21_memset(str2, test[_i].c, test[_i].n));
}
END_TEST

//memcmp
START_TEST(memcmp_test) {
  ck_assert_int_eq(
      memcmp(test[_i].str1, test[_i].str2, test[_i].n),
      s21_memcmp(test[_i].str1, test[_i].str2, test[_i].n));
}
END_TEST

//memcpy
START_TEST(memcpy_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      memcpy(str1, test[_i].str2, test[_i].n),
      s21_memcpy(str2, test[_i].str2, test[_i].n));
}
END_TEST

//memmove
START_TEST(memmove_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      memmove(str1, test[_i].str2, test[_i].n),
      s21_memmove(str2, test[_i].str2, test[_i].n));
}
END_TEST

//strcat
START_TEST(strcat_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      strcat(str1, test[_i].str2),
      s21_strcat(str2, test[_i].str2));
}
END_TEST

//strncat
START_TEST(strncat_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      strncat(str1, test[_i].str2, test[_i].n),
      s21_strncat(str2, test[_i].str2, test[_i].n));
}
END_TEST

//strchr
START_TEST(strchr_test) {
  ck_assert_pstr_eq(
      strchr(test[_i].str2, test[_i].c),
      s21_strchr(test[_i].str2, test[_i].c));
}
END_TEST

//strcmp
START_TEST(strcmp_test) {
  ck_assert_int_eq(
      strcmp(test[_i].str1, test[_i].str2),
      s21_strcmp(test[_i].str1, test[_i].str2));
}
END_TEST

//strncmp
START_TEST(strncmp_test) {
  ck_assert_int_eq(
      strncmp(test[_i].str1, test[_i].str2, test[_i].n),
      s21_strncmp(test[_i].str1, test[_i].str2, test[_i].n));
}
END_TEST

//strcpy
START_TEST(strcpy_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      strcpy(str1, test[_i].str2),
      s21_strcpy(str2, test[_i].str2));
}
END_TEST

//strncpy
START_TEST(strncpy_test) { //fail 2
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      strncpy(str1, test[_i].str2, test[_i].n),
      s21_strncpy(str2, test[_i].str2, test[_i].n));
}
END_TEST

//strcspn
START_TEST(strcspn_test) {
  ck_assert_int_eq(
      strcspn(test[_i].str1, test[_i].str2),
      s21_strcspn(test[_i].str1, test[_i].str2));
}
END_TEST

//strerror
START_TEST(strerror_test) {
  ck_assert_pstr_eq(
      strerror(test[_i].n),
      s21_strerror(test[_i].n));
}
END_TEST

//strlen
START_TEST(strlen_test) {
  ck_assert_int_eq(
      strlen(test[_i].str1),
      s21_strlen(test[_i].str1));
}
END_TEST

//strpbrk
START_TEST(strpbrk_test) {
  ck_assert_pstr_eq(
      strpbrk(test[_i].str1, test[_i].str2),
      s21_strpbrk(test[_i].str1, test[_i].str2));
}
END_TEST

//strrchr
START_TEST(strrchr_test) {
  ck_assert_pstr_eq(
      strrchr(test[_i].str1, test[_i].c),
      s21_strrchr(test[_i].str1, test[_i].c));
}
END_TEST

//strspn
START_TEST(strspn_test) {
  ck_assert_int_eq(
      strspn(test[_i].str1, test[_i].str2),
      s21_strspn(test[_i].str1, test[_i].str2));
}
END_TEST

//strstr
START_TEST(strstr_test) {
  ck_assert_pstr_eq(
      strstr(test[_i].str1, test[_i].str2),
      s21_strstr(test[_i].str1, test[_i].str2));
}
END_TEST

//strtok
START_TEST(strtok_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      strtok(str1, test[_i].str2),
      s21_strtok(str2, test[_i].str2));
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
  size_t size = sizeof(test) / sizeof(test[0]);
  switch(index) {
    case 0: tcase_add_loop_test(*tc, memchr_test, 0, size); break;
    case 1: tcase_add_loop_test(*tc, memcmp_test, 0, size); break;
    case 2: tcase_add_loop_test(*tc, memcpy_test, 0, size); break;
    case 3: tcase_add_loop_test(*tc, memset_test, 0, size); break;
    case 4: tcase_add_loop_test(*tc, memmove_test, 0, size); break;
    case 5: tcase_add_loop_test(*tc, strcat_test, 0, size); break;
    case 6: tcase_add_loop_test(*tc, strncat_test, 0, size); break;
    case 7: tcase_add_loop_test(*tc, strchr_test, 0, size); break;
    case 8: tcase_add_loop_test(*tc, strcmp_test, 0, size); break;
    case 9: tcase_add_loop_test(*tc, strncmp_test, 0, size); break;
    case 10: tcase_add_loop_test(*tc, strcpy_test, 0, size); break;
    case 11: tcase_add_loop_test(*tc, strncpy_test, 0, size); break; //2x fail
    case 12: tcase_add_loop_test(*tc, strcspn_test, 0, size); break;
    case 13: tcase_add_loop_test(*tc, strerror_test, 0, size); break; //4x fail
    case 14: tcase_add_loop_test(*tc, strlen_test, 0, size); break;
    case 15: tcase_add_loop_test(*tc, strpbrk_test, 0, size); break;
    case 16: tcase_add_loop_test(*tc, strrchr_test, 0, size); break;
    case 17: tcase_add_loop_test(*tc, strstr_test, 0, size); break;
    case 18: tcase_add_loop_test(*tc, strtok_test, 0, size); break;
    case 19: tcase_add_loop_test(*tc, strspn_test, 0, size); break;
    default: break;
  }
}

Suite *create_str_suite(void) {
  Suite *str_suite = suite_create("s21_string_test_suite");
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
