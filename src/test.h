#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "s21_string.h"

struct memchr_struct {
  const void *arr;
  int c;
  size_t n;
};

struct memchr_struct memchr_args[] = {
    {"123456789", '5', 9}, {"\n", 'j', 10}, {"ABOB\nA", '\n', 6}
};

Suite *create_str_suite(void);
TCase *create_memchr_tc(void);

#endif // SRC_TEST_H_