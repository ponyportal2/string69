#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "s21_string.h"

#define SIZE 1024

struct tcase_ {
  const char* name;
};

struct tcase_ tcases[] = {
  "memchr_tc", "memcmp_tc", 
  "memcpy_tc", "memset_tc", 
  "memmove_tc", "strcat_tc",
  "strncat_tc", "strchr_tc",
  "strcmp_tc", "strncmp_tc"
  "strcpy_tc", "strncpy_tc",
  "strcspn_tc", "strerror_tc",
  "strlen_tc", "strpbrk_tc",
  "strrchr_tc", "strspn_tc",
  "strstr_tc", "strtok_tc"
};

struct test_struct {
    char* str1;
    char* str2;
    int c;
    size_t n;
};

struct test_struct test[] = {
  {"123456789", "dgdfgdfg123", '5', 9}, 
  {"\n", "\0", 'j', 10}, 
  {"ABOB\nA", "dgdfgdfg123", '\n', 6}, 
  {"ere\0re", "\n\t\0", '8', 5}
};

void add_cases(TCase** tc, size_t index);
Suite *create_str_suite(void);
TCase *create_tc(size_t index);

#endif // SRC_TEST_H_