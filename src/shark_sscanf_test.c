
#include "shark_sscanf_test.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  char testInput[] = "%%%%sabaka%%%%aboba%abiba%%%%";
  char specifiers[64][128] = {0};
  parseSpecifiers(specifiers, testInput);

  return 0;
}

// 1st argument is like user input for scanf
// 2nd argument are the specifiers
// 3rd (varargs) are parameters to raspihat according to specifiers :)
int sscanf(const char* input, const char* format, ...) {
  va_list args;
  va_start(args, format);

  char tempSpecifiers[] = "%sabaka%aboba%abiba%";
  char currentSpecifier[128] = parseNextSpecifier(tempSpecifiers);
  // while (format[i] != '\0') {
  //   if (format[i] == 's') {
  //     char* stringP = va_arg(args, char*);
  //     *stringP =
  //   }
  //   if (format[i] == 'd' || format[i] == 'i') {
  //     int* intP = va_arg(args, int*);
  //     *intP =
  //   } else if (format == 'c') {
  //     int c = va_arg(args, int);
  //     printf("%c\n", c);
  //   } else if (format == 'f') {
  //     double d = va_arg(args, double);
  //     printf("%f\n", d);
  //   }
  //   i++;
  //   }

  parseNextSpecifier(tempSpecifiers);
  parseNextVararg();

  va_end(args);
}

void parseSpecifiers(char parsed[][128], char* input) {
  int i = 0;
  char* tempStr = NULL;
  do {
    if (i == 0) {
      tempStr = s21_strtok(input, "%");
    } else {
      tempStr = s21_strtok(NULL, "%");
    }
    if (tempStr != NULL) {
      s21_strcpy(parsed[i], tempStr);
      printf("[%s]\n", parsed[i]);
    }
    i++;
  } while (tempStr != NULL);
}

void parseNextSpecifier(int i, char parsed[][128], char* input) {
  int i = 0;
  char* tempStr = NULL;
  do {
    if (i == 0) {
      tempStr = s21_strtok(input, "%");
    } else {
      tempStr = s21_strtok(NULL, "%");
    }
    if (tempStr != NULL) {
      s21_strcpy(parsed[i], tempStr);
      printf("[%s]\n", parsed[i]);
    }
    i++;
  } while (tempStr != NULL);
}

void parseNextVararg() {
  int i = 0;
  char* tempStr = NULL;
  do {
    if (i == 0) {
      tempStr = s21_strtok(input, "%");
    } else {
      tempStr = s21_strtok(NULL, "%");
    }
    if (tempStr != NULL) {
      s21_strcpy(parsed[i], tempStr);
      printf("[%s]\n", parsed[i]);
    }
    i++;
  } while (tempStr != NULL);
}
