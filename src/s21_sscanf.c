// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include <stdarg.h>

#include "s21_string.h"

int sscanf(const char* buffer, const char* format, ...) {
  va_list args;
  va_start(args, format);

  int i = 0;
  while (buffer[i] != '\0') {
    if (buffer[i] ==) {
    }
  }

  va_end(args);
}

char* parsedSpecifiers(char* buffer) {
  int specifierStarted = 0;
  int i = 0;
  while (buffer[i] != '\0') {
    if (specifierStarted == 0) {
      if (buffer[i] == '%') {
        int specifierStarted = 1;
      }
    }
    i++;
  }
}

// while (format[i] != '\0') {
//   if (format[i] == 's') {
//     char* stringP = va_arg(args, char*);
//     *stringP =
//   }
// if (format[i] == 'd' || format[i] == 'i') {
//   int* intP = va_arg(args, int*);
//   *intP =
// } else if (format == 'c') {
//   int c = va_arg(args, int);
//   printf("%c\n", c);
// } else if (format == 'f') {
//   double d = va_arg(args, double);
//   printf("%f\n", d);
// }
// i++;