#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "s21_string.h"

#define SIZE 1024
#define MAX_C 116
#define MIN_C 115
#define MAX_N 7
#define MIN_N 6
#define FILENAME "txt.txt"
#define START_STRUCT_SIZE 4

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
  "strstr_tc", "strtok_tc",
  "strspn_tc"
};

struct test_struct {
    char* str1;
    char* str2;
    int c;
    int n;
};

typedef struct list {
    char* str1;
    struct list* next;
}list;

struct test_struct test[SIZE] = {
  {"shrek is shrek", "shrek is shrek", 's', 6}, 
  {"\n", "\0", 'j', 10},
  {"ABOB\nA", "dgdfgdfg123", '\n', 6}, 
  {"ere\0re", "\n\t\0", '8', 5}
};

void printAllCases(size_t size);
size_t set_test(char* filename, list** tmp);
list* set_params(char* filename, list* tests_);
list* add_elem(list* elem, char* str1);
void destroy(list* root);
int found_pattern(char *line, char* pattern);
void print_error(char name_test[SIZE], int index);
void print_log();
void add_cases(TCase** tc, size_t index, size_t size);
Suite *create_str_suite(size_t size);
TCase *create_tc(size_t index, size_t size);

// goodStringTestCases:

// ""
// NULL
// "a"
// "\n"
// "\t"
// "\0"
// "\n lorem \n\t ipsum \n"
// "\n\0 lorem \n\t ipsum \n"
// "\0\n lorem \n\t ipsum \n"
// "\n lorem \0\n\t ipsum \n"
// "\n lorem \n\t ipsum \0\n"
// "\n lorem \n\t ipsum \n\0"
// " lorem \n\t ipsum \n"
// "\0 lorem \n\t ipsum \n"
// " lorem \0\n\t ipsum \n"
// " lorem \n\t ipsum \0\n"
// " lorem \n\t ipsum \n\0"
// "\0\0\0\00\00\00 is \n0 0\t\00 is 0 0\n"

#endif // SRC_TEST_H_
