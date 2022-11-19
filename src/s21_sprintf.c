#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MISMADCH_ 1
#define ENDET_ 2

typedef struct Specificator {
  short width, precision;
  char specif;
} Specificator;

void formatStringToBufferCat(char* buff, char* pointerToStr,
                             char* pointerToSpec);
void formatPrint(char* buff, Specificator spec, void* currentVarArg);
Specificator parseSpecificator(char* pointerToSpec);

int main() {
  char* buf;
  int test = s21_sprintf(buf, "Takaya shtuka: %6.2f %d %c %s", 3.1415, 100, 'C',
                         "Far");
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
    char* pointerToSpec = strchr(pointerToFormatStr, '%');
    formatStringToBufferCat(buff, pointerToFormatStr, pointerToSpec);
    Specificator spec = parseSpecificator(pointerToSpec);
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

void formatStringToBufferCat(char* buff, char* pointerToFormatStr,
                             char* pointerToSpec) {
  char* pointer = buff;
  while (pointerToFormatStr != pointerToSpec) {
    *pointer = *pointerToFormatStr;
    pointer++;
    pointerToFormatStr++;
  }
  *pointer = '\0';
}

void formatPrint(char* buff, Specificator spec, void* currentVarArg) {}

Specificator parseSpecificator(char* pointerToSpec) {
  Specificator spec = {6, 1, 'f'};
  return spec;
}