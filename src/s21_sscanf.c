#include "s21_sscanf.h"
#include <stdio.h>
#include <string.h>

// 1st argument is like user input for scanf
// 2nd argument are the specifiers
// 3rd (varargs) are parameters to raspihat according to specifiers :)
int s21_sscanf(const char *input, const char *format, ...) {
  (void)input;
  va_list args;
  va_start(args, format);

  char tempSpecifiers[] = "%s%i%f";
  char *currentSpecifier = NULL;

  bool varArgsEnded = false;
  while (varArgsEnded == false) {
    currentSpecifier = parseNextSpecifier(tempSpecifiers);
    if (strcmp(currentSpecifier, "PIZDEC") != 0) {
      if (currentSpecifier[0] == 's') {
        strcpy(va_arg(args, char *), "booba");
      } else if (currentSpecifier[0] == 'd' || currentSpecifier[0] == 'i') {
        int *intP = va_arg(args, int *);
        if (intP != NULL) {
          *intP = 67;
        } else {
          varArgsEnded = true;
        }
      } else if (currentSpecifier[0] == 'c') {
        int *charP = va_arg(args, int *);
        if (charP != NULL) {
          *charP = 67;
        } else {
          varArgsEnded = true;
        }
      } else if (currentSpecifier[0] == 'f') {
        double *doubleP = va_arg(args, double *);
        if (doubleP != NULL) {
          *doubleP = 67.67;
        } else {
          varArgsEnded = true;
        }
      }
    } else {
      varArgsEnded = true;
    }
  }
  va_end(args);
  return 1; // to fix
}

char *parseNextSpecifier(char *input) {
  char *returnValue = NULL;
  char *tempStr = NULL;
  static bool isInitilized = false;
  if (isInitilized) {
    tempStr = strtok(NULL, "%");
  } else {
    tempStr = strtok(input, "%");
    isInitilized = true;
  }
  //   printf("\n[%s]\n", tempStr);
  if (tempStr == NULL) {
    returnValue = "PIZDEC";
  } else {
    returnValue = tempStr;
  }
  return returnValue;
}

// if (tempStr != NULL) {
//   s21_strcpy(currentSpecifier, tempStr);
//   printf("[%s]\n", currentSpecifier);
// }

// void parseNextVararg() {
//   int i = 0;
//   char *tempStr = NULL;
//   do {
//     if (i == 0) {
//       tempStr = s21_strtok(input, "%");
//     } else {
//       tempStr = s21_strtok(NULL, "%");
//     }
//     if (tempStr != NULL) {
//       s21_strcpy(parsed[i], tempStr);
//       printf("[%s]\n", parsed[i]);
//     }
//     i++;
//   } while (tempStr != NULL);
// }

// void parseSpecifiers(char parsed[][128], char *input) {
//   int i = 0;
//   char *tempStr = NULL;
//   do {
//     if (i == 0) {
//       tempStr = s21_strtok(input, "%");
//     } else {
//       tempStr = s21_strtok(NULL, "%");
//     }
//     if (tempStr != NULL) {
//       s21_strcpy(parsed[i], tempStr);
//       printf("[%s]\n", parsed[i]);
//     }
//     i++;
//   } while (tempStr != NULL);
// }

// int sscanf(const char* buffer, const char* format, ...) {
//   // va_list args;
//   // va_start(args, format);

//   char tempSpecifiers[] = "%sabaka%aboba%abiba%";
//   parseSpecifiers(tempSpecifiers);
//   // int i = 0;
//   // while (buffer[i] != '\0') {
//   //   if (buffer[i] ==) {
//   //   }
//   // }

//   // va_end(args);
// }

// char* parseSpecifiers(char* buffer) {
//   int specifierStarted = 0;
//   char specifiers[128][128] = {0};
//   int i = 0;
//   strcpy(specifiers[0], s21_strtok(buffer, "%"));
//   do {
//     i++;
//     strcpy(specifiers[i], s21_strtok(NULL, "%"));
//   } while (specifiers[i] != NULL);
// }

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

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>