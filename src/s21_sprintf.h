#ifndef SRC_SPRINTF_H_
#define SRC_SPRINTF_H_

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define MAXLINE 200
#define OUR_ERROR_ "KufLv91ySdu64DYPiXOHGx5Jj9Q2eKcYwnrjxhQG"

#define MISMADCH_ 1
#define ENDET_ 2
// структура: %[flags][width][.precisions][length]type;
// flags: flag_minus - "-"; flag_plus - "+"; flag_zero - "0"; flag_space - " ";
// flag_noargument - skip the argument; flag_hash - "#"; width: (number); (-1)
// the same as *; .precisions: (.number);
// (.-1) the same as *; length: h - short int, only with i, d, o, u, x and X; l
// - long int and long char, only with i, d, o, u, x, X, c and s; L - long
// double, only with e, E, f, g and G type: c, d, i, e, E, f, g, G, o, s, u, x,
// X, p, n;
typedef struct Specificator {
  short width, precision;
  char type, length;
  bool flag_minus, flag_plus, flag_space, flag_zero, flag_noargumet, flag_hash;
} Specificator;

int s21_sprintf(char* buff, const char* format, ...);
void formatPrint(char* buff, Specificator spec, va_list args);
Specificator parseSpecificator(char** pointerToSpec, bool* formatLoaded);
void strcpy_help(char* str1, char* str2, int index);
void strcat_with_spec(char* buff, char* src, Specificator spec);
void itoa(long long num, char* src, int radix);
void reverse(char* string);
void trimDouble(double inputDouble, int ndigit, char* buf);
void ourGcvt(long double value, int ndigit, char* buf, int radix);
int zeroOs(char* str);
void strcpy_help(char* str1, char* str2, int index);
void strchr_help(char* str1, char s);
bool is_digit(char type);

#endif  // SRC_SPRINTF_H_