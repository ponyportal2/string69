#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

typedef struct Specificator {
  short width, precision;
  char type;
} Specificator;

int s21_sprintf(char* buff, const char* format, ...);
void formatPrint(char* buff, Specificator spec, void* currentVarArg);
Specificator parseSpecificator(char* pointerToSpec, char** pointerToFormatStr);
void strcat_with_max_width(char* buff, char* src, int width);
void itoa(int num, char* src, int radix);
void reverse(char* string);

int main() {
  char* buf = malloc(30);
  int test = s21_sprintf(buf, "Takaya shtuka: %6d", 35);
  puts(buf);
  return 0;
}

int s21_sprintf(char* buff, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* pointerToFormatStr = malloc(30);
  strcpy(pointerToFormatStr, format);
  short status = 0;
  int i = 0;
  while (!i) {
    // CURRENT FORMAT ELEMENT PRINT
    char* pointerToSpec = strtok(pointerToFormatStr, "%");
    strcat(buff, pointerToFormatStr);
    Specificator spec = parseSpecificator(pointerToSpec, &pointerToFormatStr);
    formatPrint(buff, spec, va_arg(args, void*));
    i++;
  }
  va_end(args);
}

void formatPrint(char* buff, Specificator spec, void* currentVarArg) {
  char src[MAXLINE];
  if (spec.type == 'f') gcvt(*(float*)currentVarArg, spec.precision, src);
  if (spec.type == 'd') itoa(*(int*)currentVarArg, src, 10);
  strcat_with_max_width(buff, src, spec.width);
}

void strcat_with_max_width(char* buff, char* src, int width) {
  int length = strlen(src);
  while (width - length > 0) {
    strcat(buff, " ");
    length++;
  }
  strcat(buff, src);
}

void itoa(int num, char* src, int radix) {
  int i = 0;
  while (num >= pow(radix, i)) {
    int digit = (int)(num / pow(radix, i)) % radix;
    src[i++] = (char)(digit + 48);
  }
  src[i] = '\0';
  reverse(src);
}

void reverse(char* string) {
  char temp[MAXLINE];
  strcpy(temp, string);
  int length = strlen(string);
  int i;
  for (i = 0; i < length; i++) string[i] = temp[length - i - 1];
  string[i] = '\0';
}

Specificator parseSpecificator(char* pointerToSpec, char** pointerToFormatStr) {
  Specificator spec = {8, 3, 'd'};
  *pointerToFormatStr = pointerToSpec + 4;
  return spec;
}