#include "test.h"
//memchr
START_TEST(memchr_test) {
  ck_assert_pstr_eq(
      memchr(test[_i].str1, test[_i].c, test[_i].n),
      s21_memchr(test[_i].str1, test[_i].c, test[_i].n));
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
START_TEST(strncpy_test) {
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

TCase *create_tc(size_t index) {
  TCase *tc = tcase_create(tcases[index].name);
  tcase_set_timeout(tc, 10);
  add_cases(&tc, index);
  return tc;
}

void print_log() {
    FILE *f = fopen("log.xml","r");
    if (f != NULL) {
      size_t len = 0;
      int found_err = 0, found_name = 0, iteration = 0;
    char *line = NULL;
    ssize_t read = getline(&line, &len, f);
    char name[SIZE] = "", num[SIZE] = "";
    while (read != -1) {
      size_t size = strlen(line);
      if (!found_err && found_pattern(line, "failure")) found_err = 1;
      if (!found_name && found_err && found_pattern(line, "<id>")) {
        memset(name, 0, sizeof(name));
        for (size_t i = 0; line[i + 10] != '<'; i++) name[i] = line[i + 10];
        found_name = 1;
      }
      if (found_name && found_pattern(line, "<iteration>")) {
        memset(num, 0, sizeof(num));
        for (size_t i = 0; line[i + 17] != '<'; i++)  num[i] = line[i + 17];
        iteration = atoi(num);
        print_error(name, iteration);
        found_err = 0;
        found_name = 0;
      }
      read = getline(&line, &len, f);
    }
    if (line) free(line);
      fclose(f);
    }
}

void print_error(char name_test[SIZE], int index) {
  printf("FAILED %s №%d:", name_test, index);
  printf("\t{ %s, %s, %d, %d }\n", test[index].str1, test[index].str2, test[index].c, test[index].n);
  printf("-------------------------------------------------\n");
}

int found_pattern(char *line, char *pattern) {
  int res = 0;
  regex_t regex = {};
  regmatch_t pmatch[1] = {};
  regcomp(&regex, pattern, REG_NEWLINE);
  if (regexec(&regex, line, 1, pmatch, 0) == 0) {
      res = 1;
  }
  regfree(&regex);
  return res;
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
    case 11: tcase_add_loop_test(*tc, strncpy_test, 0, size); break;
    case 12: tcase_add_loop_test(*tc, strcspn_test, 0, size); break;
    case 13: tcase_add_loop_test(*tc, strerror_test, 0, size); break;
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

list* add_elem(list* elem, char* str1, char* str2, int c, int n) {
  struct list* tmp = (list*) malloc(sizeof(list));
  tmp->str1 = str1;
  tmp->str2 = str2;
  tmp->c = c;
  tmp->n = n;
  if (elem == NULL) {
    tmp->next = NULL;
    elem = tmp;
  } else {
    list *p = elem;
    while (p->next != NULL) p = p->next;
    p->next = tmp;
    tmp->next = NULL;
  }
  return elem;
}

void destroy(list* root) {
  while (root != NULL) {
    list *p = root;
    root = root->next;
    free(p->str1);
    free(p->str2);
    free(p);
  }
}

list* set_tests(char* filename, list* tests_, list** tmp) {
  *tmp = set_params(filename, *tmp);
  FILE *f = fopen(filename, "rb");
  if (f != NULL) {
    size_t len = 0;
    char *line = NULL;
    ssize_t read = getline(&line, &len, f);
    while (read != -1) {
           list* p = *tmp;
           while (p != NULL) {
            for (int i = MIN_C; i <= MAX_C; i++) {
              for (int j = MIN_N; j <= MAX_N; j++) {
                  char* buf = strdup(line);
                  char* buf1 = strdup(p->str1);
                  tests_ = add_elem(tests_, buf, buf1, i, j);
                }
            }
                  p = p->next;
           }
      read = getline(&line, &len, f);
    }
    if (line) free(line); 
    fclose(f);
    }
  
  return tests_;
}

list* set_params(char* filename, list* tmp) {
  FILE *f = fopen(filename, "rb");
  if (f != NULL) {
    size_t len = 0;
    char *line = NULL;
    ssize_t read = getline(&line, &len, f);
    while (read != -1) {
        char* buf = strdup(line);
        char* buf1 = strdup(line);
        tmp = add_elem(tmp, buf, buf1, 't', 8);
        read = getline(&line, &len, f);
      }
      if (line) free(line);
      fclose(f);
    }
  return tmp;
  }

int main(void) {
  list* tests = NULL;
  list* tmp = NULL;
  tests = set_tests("txt.txt", tests, &tmp);
  list* p = tests;
  int i = 0;
 while (p!= NULL) {
  printf("case %d: {%s},{%s},{%d},{%d}\n", i, p->str1, p->str2, p->c, p->n);
  printf("::::::::::::::::::::::::::::::::::\n");
  p = p->next;
  i++;
 }
  destroy(tests);
  destroy(tmp);
  Suite *str_suite = create_str_suite();
  SRunner *suite_runner = srunner_create(str_suite);
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_set_xml(suite_runner, "log.xml");
  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  if (failed_count != 0) print_log();
  srunner_free(suite_runner);
  return EXIT_SUCCESS;
}
