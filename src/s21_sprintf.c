#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MISMADCH_ 1
#define ENDET_ 2

typedef struct Specificator {
  short width, precision;
  char type;
} Specificator;

void formatPrint(char* buff, Specificator spec, void* currentVarArg);
Specificator parseSpecificator(char* pointerToSpec, char** pointerToFormatStr);

int main() {
  char* buf;
  int test = s21_sprintf(buf, "Takaya shtuka: %6.2f", 3.1415);
  return 0;
}

int s21_sprintf(char* buff, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* pointerToFormatStr = format;
  short status = 0;
  while (status != MISMADCH_ && status != ENDET_) {
    bool formatLoaded = false;
    bool outputLoaded = false;
    bool varArgLoaded = false;
    // CURRENT FORMAT ELEMENT PRINT
    char* pointerToSpec = strtok(pointerToFormatStr, '%');
    strcat(buff, pointerToFormatStr);
    Specificator spec = parseSpecificator(pointerToSpec, pointerToFormatStr);
    formatPrint(buff, spec, va_arg(args, void*));
    // -------------------------------
    if (formatLoaded == false && outputLoaded == false &&
        varArgLoaded == false) {
      status = ENDET_;
    } else if (formatLoaded + outputLoaded + varArgLoaded > 0 &&
               formatLoaded + outputLoaded + varArgLoaded < 3) {
      status = MISMADCH_;
    }
  }
  va_end(args);
}

void formatPrint(char* buff, Specificator spec, void* currentVarArg) {
  if (spec.type == 'f') {
    char src[1024];
    gcvt(*(float*)currentVarArg, spec.precision, src);
    strcat_with_max_width(buff, src, spec.width);
  }
}

void strcat_with_max_width(char* buff, char* src, int width) {
  int length = strlen(src);
  while (width - length > 0) {
    strcat(buff, ' ');
    length++;
  }
  strcat(buff, src);
}

Specificator parseSpecificator(char* pointerToSpec, char** pointerToFormatStr) {
  Specificator spec = {6, 2, 'f'};
  return spec;
}