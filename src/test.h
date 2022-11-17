#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "s21_string.h"

struct tcase_ {
  const char* name;
};

struct tcase_ tcases[] = {
  "memchr_tc", "memcmp_tc", "memcpy_tc"
};

struct memchr_struct {
  const void *arr;
  int c;
  size_t n;
};

struct memset_struct {
  void *arr;
  int c;
  size_t n;
};

struct memcmp_struct {
  const void *arr;
  const void *arr2;
  size_t n;
};

struct memcpy_struct { //memmmove
  void *dest;
  const void *src;
  size_t n;
};

struct strcat_struct { //strcpy strtok
    char* dest;
    const char *src;
};

struct strncat_struct { // strncpy
    char* dest;
    const char *src;
    size_t n;
};

struct strlen_struct {
    const char *str1;
};

struct strchr_struct { // strrchr
    const char *str1;
    int c;
};

struct strcmp_struct { //strcspn strbrk strspn strstr
    const char* str1;
    const char* str2;
};

struct strncmp_struct {
    const char* str1;
    const char* str2;
    size_t n;
};

struct strerror_struct {
    int errnum;
};

struct memchr_struct memchr_args[] = {
    {"123456789", '5', 9}, {"\n", 'j', 10}, {"ABOB\nA", '\n', 6}, {"ere\0re", '8', 5}
};

struct memset_struct memset_args[] = {
    {"123456789", '5', 9}, {"\n", 'j', 10}, {"ABOB\nA", '\n', 6}, {"ere\0re", '8', 5}
};

struct memcmp_struct memcmp_args[] = {
    {"123456789", "ghjggkhgty", 9}, {"1234\n", "1234asdasd", 4}, {"ABOB\nA", "\0", 6}, {"ere\0re", "ere\0re", 5}
};

struct memcpy_struct memcpy_args[] = {
    {"123456789", "ghjggkhgty", 9}, {"1234\n", "1234asdasd", 4}, {"ABOB\nA", "\0", 6}, {"ere\0re", "ere\0re", 5}
};

void add_cases(TCase** tc, size_t index);
Suite *create_str_suite(void);
TCase *create_memchr_tc(void);

#endif // SRC_TEST_H_