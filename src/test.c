#include "test.h"

//sprintf
START_TEST(sprintf_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  sprintf(str1, "Value of Pi = %f", M_PI);
  s21_sprintf(str2, "Value of Pi = %f", M_PI);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_extra_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  s21_sprintf(str1, "Takaya shtuka: -#o %0.f %+i gj %20f %s%c\n",4.44, 300, 9999999.08, "zepi", 6);
  sprintf(str2, "Takaya shtuka: -#o %0.f %+i gj %20f %s%c\n",4.44, 300, 9999999.08, "zepi", 6);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

//sscanf
START_TEST(sscanf_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  int i = 0, j = 0;
  sscanf("hello 1 2 3 4 5", "%s%d", str1, &i);
  s21_sscanf("hello 1 2 3 4 5", "%s%d", str2, &j);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sscanf_extra_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  int i = 0, j = 0;
  float n, m;
  sscanf("shrek 1 2 3 4 0.05", "%hhn%X%f", str1, &i, &n);
  s21_sscanf("shrek 1 2 3 4 0.05", "%hhn%X%f", str2, &j, &m);
  ck_assert_int_eq(n, m);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sscanf_bonus_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  int i = 0, j = 0;
  sscanf("sdsd 4", "%s%o", str1, &i);
  s21_sscanf("sdsd 4", "%s%o", str2, &j);
  ck_assert_int_eq(i, j);
}
END_TEST

//memchr
START_TEST(memchr_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  ck_assert_pstr_eq(
      memchr(str1, test[_i].c, test[_i].n),
      s21_memchr(str2, test[_i].c, test[_i].n));
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
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  char str3[SIZE] = "";
  char str4[SIZE] = "";
  strcpy(str1, test[_i].str2);
  strcpy(str2, test[_i].str2);
  strcpy(str3, test[_i].str1);
  strcpy(str4, test[_i].str1);
  int i = 0, j = 0;
  i = memcmp(str3, str1, test[_i].n);
  j = s21_memcmp(str4, str2, test[_i].n);
  if (i == -1 || i == 1) {
    if (j < 0) j = -1;
    else if (j > 0) j = 1;
  }
  ck_assert_int_eq(i, j);
}
END_TEST

//memcpy
START_TEST(memcpy_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  char str3[SIZE] = "";
  char str4[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  strcpy(str3, test[_i].str2);
  strcpy(str4, test[_i].str2);
  ck_assert_pstr_eq(
      memcpy(str1, str3, test[_i].n),
      s21_memcpy(str2, str4, test[_i].n));
}
END_TEST

//memmove
START_TEST(memmove_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  char str3[SIZE] = "";
  char str4[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  strcpy(str3, test[_i].str2);
  strcpy(str4, test[_i].str2);
  ck_assert_pstr_eq(
      memmove(str1, str3, test[_i].n),
      s21_memmove(str2, str4, test[_i].n));
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
  int i = 0, j = 0;
  i = strcmp(test[_i].str1, test[_i].str2);
  j = s21_strcmp(test[_i].str1, test[_i].str2);
  if (i == -1 || i == 1) {
    if (j < 0) j = -1;
    else if (j > 0) j = 1;
  }
  ck_assert_int_eq(i, j);
}
END_TEST

//strncmp
START_TEST(strncmp_test) {
  int i = 0, j = 0;
  i = strncmp(test[_i].str1, test[_i].str2, test[_i].n);
  j = s21_strncmp(test[_i].str1, test[_i].str2, test[_i].n);
  if (i == -1 || i == 1) {
    if (j < 0) j = -1;
    else if (j > 0) j = 1;
  }
  ck_assert_int_eq(i, j);
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

//to_upper
START_TEST(to_upper_test) {
  char *s = NULL;
  if (test[_i].str1 != NULL) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  for (size_t i = 0; i < strlen(test[_i].str1); i++) {
    str2[i] = toupper(str2[i]);
  }
    s = s21_to_upper(str1);
    ck_assert_pstr_eq(str2, s);
  } else {
    s = s21_to_upper(test[_i].str1);
    ck_assert_pstr_eq(NULL, s);
  }
  if (s) free(s);
}
END_TEST

//to_lower
START_TEST(to_lower_test) {
  char* s = NULL;
  if (test[_i].str1 != NULL) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str1);
  for (size_t i = 0; i < strlen(test[_i].str1); i++) {
    str2[i] = tolower(str2[i]);
  }
    s = s21_to_lower(str1);
    ck_assert_pstr_eq(str2, s);
  } else {
    s = s21_to_lower(test[_i].str1);
    ck_assert_pstr_eq(NULL, s);
  }
    if (s) free(s);
}
END_TEST

//insert
START_TEST(insert_test) { 
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  char str3[SIZE] = "";
  char str4[SIZE] = "";
  char* s = NULL;
  strcpy(str2, test[_i].str2);
  strcpy(str1, test[_i].str1);
  strcpy(str3, test[_i].str1);
  strcpy(str4, test[_i].str2);
  if ((size_t) test[_i].n < strlen(str1)) {
    char res[SIZE] = "";
    strncpy(res, str1, test[_i].n);
    strcat(res, str2);
    size_t j = 0;
    char res1[SIZE] = "";
    for (size_t i = test[_i].n; i < strlen(str1); i++) {
      res1[j] = str1[i]; 
      j++;
    }
    strcat(res, res1);
    s = s21_insert(str3, str4, test[_i].n);
    ck_assert_pstr_eq(res, s);
  } else {
    s = s21_insert(str3, str4, test[_i].n);
    ck_assert_pstr_eq(NULL, s);
  }
  if (s) free(s);
}
END_TEST

/*
void reverser(char* src, char* pat, char *res) {
    size_t n = strspn(src, pat);
    size_t j = 0;
    for (size_t i = n; i < strlen(src); i++) {
        res[j] = src[i]; j++;
    }
    res[j] = '\0';
    size_t size = strlen(src) - n;
    size_t i = 0;
    j = strlen(src) - n - 1;
    for (i = 0; i < size/2; i++) {
        char c = res[i];
        res[i] = res[j];
        res[j] = c;
        j--;
    }
    res[size] = '\0';
}
//trim
START_TEST(trim_test) {
  char str1[SIZE] = "";
  char str2[SIZE] = "";
  void *s = NULL;
  strcpy(str1, test[_i].str1);
  strcpy(str2, test[_i].str2);
  if (test[_i].str1 != NULL && test[_i].str2 != NULL) {
    char res[SIZE] = "";
      reverser(str1, str2, res);
      char res1[SIZE] = ""; 
      reverser(res, str2, res1);
      s = s21_trim(str1, str2);
    ck_assert_pstr_eq(res1, "s");
  } else {
      s = s21_trim(str1, str2);
      ck_assert_pstr_eq(NULL, "s");
  }
  if (s) free(s);
}
END_TEST
*/
TCase *create_tc(size_t index, size_t size) {
  TCase *tc = tcase_create(tcases[index].name);
  tcase_set_timeout(tc, 10);
  add_cases(&tc, index, size);
  return tc;
}

void print_log(double n_checks) {
    FILE *f = fopen("log.xml","r");
    if (f != NULL) {
      printf("\n");
      size_t len = 0;
      int found_err = 0, found_name = 0, counter = 0; 
      double fails = 0;
    char *line = NULL;
    ssize_t read = getline(&line, &len, f);
    char name[SIZE] = "", num[SIZE] = "", prev_name[SIZE] = "";
    while (read != -1) {
      if (!found_err && found_pattern(line, "failure")) found_err = 1;
      if (!found_name && found_err && found_pattern(line, "<id>")) {
        memset(name, 0, sizeof(name));
        for (size_t i = 0; line[i + 10] != '<'; i++) name[i] = line[i + 10];
        found_name = 1;
      }
      if (found_name && found_pattern(line, "<iteration>")) {
        memset(num, 0, sizeof(num));
        for (size_t i = 0; line[i + 17] != '<'; i++)  num[i] = line[i + 17];
        int iteration = atoi(num);
        if (strcmp(prev_name, name) != 0) {
          if (counter > MAX_ERRLOG_SIZE) printf("----------SEE OTHER %d ERRORS IN LOG-------------\n", counter - MAX_ERRLOG_SIZE);
          counter = 0;
          }
        print_error(name, iteration, counter);
        memset(prev_name, 0, sizeof(prev_name));
        strcpy(prev_name, name);
        counter++;
        fails++;
        found_err = 0;
        found_name = 0;
      }
      read = getline(&line, &len, f);
    }
    if (counter > MAX_ERRLOG_SIZE) printf("----------SEE OTHER %d ERRORS IN LOG-------------\n", counter - MAX_ERRLOG_SIZE);
    double perc = 100 - ((fails * 100) /n_checks);
    printf("%lf%c checks: %d, failures: %d", perc, 37, (int)n_checks, (int)fails);
    if (line) free(line);
      fclose(f);
    }
}

void print_error(char name_test[SIZE], int index, int counter) {
  if (counter <= MAX_ERRLOG_SIZE) {
    printf("-------------------------------------------------\n");
    printf("FAILED %s №%d:", name_test, index);
    printf("\t{ |%s|, |%s|, |%d|, |%d| }\n", test[index].str1, test[index].str2, test[index].c, test[index].n);
  } else {
    printf("''''''''''''''''''''''''''''''''''''''''''''''''\n");
    printf("failed %s №%d:", name_test, index);
    printf("\t/'%s', '%s', '%d', '%d'/\n", test[index].str1, test[index].str2, test[index].c, test[index].n);
  }
  
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

void add_cases(TCase** tc, size_t index, size_t size) {
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
    case 20: tcase_add_loop_test(*tc, to_upper_test, 0, size); break;
    case 21: tcase_add_loop_test(*tc, to_lower_test, 0, size); break;
    case 22: tcase_add_loop_test(*tc, insert_test, 0, size); break;
    case 23: break;//tcase_add_loop_test(*tc, trim_test, 0, size); break;
    case 24: tcase_add_test(*tc, sscanf_test); tcase_add_test(*tc, sscanf_extra_test); tcase_add_test(*tc, sscanf_bonus_test); break;
    case 25: tcase_add_test(*tc, sprintf_test); tcase_add_test(*tc, sprintf_extra_test); break;
    default: break;
  }
}

Suite *create_str_suite(size_t size_) {
  Suite *str_suite = suite_create("s21_string_test_suite");
  size_t size = sizeof(tcases) / sizeof(tcases[0]);
  for (size_t i = 0; i < size; i++) {
    TCase *tc = create_tc(i, size_);
    suite_add_tcase(str_suite, tc);
  }
  return str_suite;
}

list* add_elem(list* elem, char* str1) {
  struct list* tmp = (list*) malloc(sizeof(list));
  tmp->str1 = str1;
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
    free(p);
  }
}

size_t set_test(char* filename, list** tmp) {
  size_t size = START_STRUCT_SIZE;
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
                  test[size] = (struct test_struct){buf,buf1, i, j};
                  size++;
                }
            }
              p = p->next;
           }
      read = getline(&line, &len, f);
    }
    if (line) free(line); 
    fclose(f);
    }
  return size;
}

list* set_params(char* filename, list* tmp) {
  FILE *f = fopen(filename, "rb");
  if (f != NULL) {
    size_t len = 0;
    char *line = NULL;
    ssize_t read = getline(&line, &len, f);
    while (read != -1) {
        char* buf = strdup(line);
        tmp = add_elem(tmp, buf);
        read = getline(&line, &len, f);
      }
      if (line) free(line);
      fclose(f);
    }
  return tmp;
}

void printAllCases(size_t size) {
  printf("Cases\n");
  for (size_t i = 0; i < size; i++) {
    printf("case %d: [%s],[%s],[%d],[%d]\n", (int)i, test[i].str1,  test[i].str2,  test[i].c,  test[i].n);
    printf("::::::::::::::::::::::::::::::::::\n");
  }
  printf("\n");
}

int main(void) {
  list* tmp = NULL;
  size_t size = START_STRUCT_SIZE;
  size = set_test(FILENAME, &tmp);
  printAllCases(size);
  Suite *str_suite = create_str_suite(size - 1);
  SRunner *suite_runner = srunner_create(str_suite);
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_set_xml(suite_runner, "log.xml");
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_ntests_failed(suite_runner);
  double N = (TC_STRUCT_SIZE * (double)size) + EXTRA_TESTS_COUNT;
  print_log(N);
  srunner_free(suite_runner);
  destroy(tmp);
  return EXIT_SUCCESS;
}
