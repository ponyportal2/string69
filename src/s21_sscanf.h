#include "s21_string.h"
#include <stdarg.h>

int s21_sscanf(const char *input, const char *format, ...);
char *parseNextSpecifier(char *tempSpecifiers);