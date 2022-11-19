#include "s21_sscanf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUR_ERROR_ "KufLv91ySdu64DYPiXOHGx5Jj9Q2eKcYwnrjxhQG"

#define MISMADCH_ 1
#define ENDET_ 2

// 1st argument is like user input for scanf
// 2nd argument are the specifiers
// 3rd (varargs) are parameters to raspihat according to specifiers :)
int s21_sscanf(const char *input, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char inputStatic[16384] = {0};   // local copy of whole "input" parameter
  char formatStatic[16384] = {0};  // local copy of whole "format" parameter
  strcpy(inputStatic, input);
  strcpy(formatStatic, format);

  char currentInputElem[8192] = {0};
  char currentFormatElem[8192] = {0};

  int status = 0;
  while (status != MISMADCH_ && status != ENDET_) {
    bool formatLoaded = false;
    bool inputLoaded = false;
    bool varArgLoaded = false;
    // CURRENT FORMAT ELEMENT PARSING:
    formatParsing(formatStatic, currentFormatElem, &formatLoaded);
    // printf("\n[%s]\n", currentFormatElem);

    // CURRENT INPUT ELEMENT PARSING:
    inputParsing(inputStatic, currentInputElem, 3, &inputLoaded);
    // printf("\n[%s]\n", currentInputElem);

    // CURRENT VARARG ELEMENT PARSING:
    varArgParsingAndAssignment(currentFormatElem, currentInputElem,
                               &varArgLoaded, va_arg(args, void *));
    // -------------------------------
    if (formatLoaded == false && inputLoaded == false &&
        varArgLoaded == false) {
      status = ENDET_;
    } else if (formatLoaded + inputLoaded + varArgLoaded > 0 &&
               formatLoaded + inputLoaded + varArgLoaded < 3) {
      status = MISMADCH_;
    }
  }
  va_end(args);
  return 800815;  // to fix, I don't know what sscanf should return and why
}

void getNextFormatElem(char *input, char elem[8192]) {
  char *returnStr = NULL;
  static bool isFormatInitilized = false;
  char *currentFormatString = NULL;
  char formatDelims[] = "%";

  if (isFormatInitilized) {
    currentFormatString = strtok(NULL, formatDelims);
  } else {  // if not initialized - then initialize
    currentFormatString = strtok(input, formatDelims);
    isFormatInitilized = true;
  }

  returnStr = currentFormatString;

  if (returnStr != NULL) {
    strcpy(elem, returnStr);
  } else {  // if return is NULL then we return "error" string
    strcpy(elem, OUR_ERROR_);
  }
}

void formatParsing(char formatStatic[16384], char currentFormatElem[8192],
                   bool *formatLoaded) {
  getNextFormatElem(formatStatic, currentFormatElem);
  if (strcmp(currentFormatElem, OUR_ERROR_) != 0) {
    *formatLoaded = true;
    // parsing current format element. worst case, something like this:
    // "*6hhi"
  }
}

void varArgParsingAndAssignment(char currentFormatElem[8192],
                                char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg) {
  // here we will need to get a var arg based on currentFormatElem and set it
  // through a pointer to what we parsed from currentInputElem.
  // See formatI for a not perfect example

  // needed, cause passing static arrays too deep breaks them for some reason:
  char tempCurrentInputElem[8192] = {0};
  strcpy(tempCurrentInputElem, currentInputElem);
  if (currentFormatElem[0] == 'i') {
    // [0] part is of course incorrect, properly parsed format
    // logic is needed here.
    assignI(tempCurrentInputElem, varArgLoaded, currentVarArg);
  } else if (currentFormatElem[0] == 's') {
    assignS(tempCurrentInputElem, varArgLoaded, currentVarArg);
  }
}

void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    *((int *)currentVarArg) = atoi(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignS(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    strcpy(currentVarArg, currentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

char *strtokChop(char *str, const char *delim, char *leftOver) {
  static char *new_str;
  char *tmp = str;
  int check = 1;
  if (str != NULL) {
    new_str = str;
  } else if (!new_str) {  //если строка закончилась, возвращаем 0
    tmp = 0;
    check = 0;
  }
  if (check != 0) {
    size_t check1 = s21_strspn(new_str, delim);  // есть ли сейчас разделитель

    str = new_str + check1;  // перепрыгиваем разделитель
    tmp = new_str + check1;
    size_t check2 = s21_strcspn(str, delim);  // длина до следующего разделителя
    new_str = str + check2;  // перепрыгиваем до следующего разделителя
    if (new_str == str) {  // для случая когда стартовая строка пустая
      tmp = 0;
      new_str = 0;
    } else {
      if (*new_str != 0) {  // зануляем разделитель
        *new_str = 0;
        new_str++;
      } else {
        new_str = NULL;  // если строка закончилась то NULL
      }
    }
  }

  // right chop goes into leftOver:
  if (new_str != NULL) {
    strcpy(leftOver, new_str);
  } else {  // if return is NULL then we fill with "error" string
    strcpy(leftOver, OUR_ERROR_);
  }

  return tmp;  // возвращаем строку до зануленного разделителя
}

void inputParsing(char inputFlip[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded) {
  static bool flipFlop = false;
  static char inputFlop[16384] = {0};
  if (wid == -1) {
    if (flipFlop == false) {
      strcpy(currentInputElem, strtokChop(inputFlip, "\n \t", inputFlop));
      flipFlop = true;
    } else if (flipFlop == true) {
      strcpy(currentInputElem, strtokChop(inputFlop, "\n \t", inputFlip));
      flipFlop = false;
    }
  } else {
    if (flipFlop == false) {
      fillOneByOne(inputFlip, currentInputElem, wid);
    } else if (flipFlop == true) {
      fillOneByOne(inputFlop, currentInputElem, wid);
    }
  }
  if (strcmp(currentInputElem, OUR_ERROR_) != 0) {
    *inputLoaded = true;
  }
}

void fillOneByOne(char input[16384], char currentInputElem[8192], int wid) {
  int i = 0;
  int j = 0;
  while (input[i] != '\0' && j < wid) {
    if (s21_match("\t \n", input[i]) == false) {
      currentInputElem[j] = input[i];
      j++;
    }
    i++;
  }
  currentInputElem[j] = '\0';
  chopLeft(input, i);
}

void chopLeft(char input[16384], int howMany) {
  int j = 0;
  for (int i = howMany; input[i] != '\0'; i++, j++) {
    input[j] = input[i];
  }
  input[j] = '\0';
}

// shrakmer: тут я хомячу код потому что мне так удобно, в конце удалим:
// ---------------------------------------------------------------------

// printf("inputStatic: %s\n", inputStatic);
// printf("leftover: %s\n", leftOver);
// printf("curInputElem: %s\n", currentInputElem);

// printf("%s", input);

// void chopLeft(char input[16384], int howMany) {
//   int j = 0;
//   for (int i = howMany; (i < (howMany * 2)) && (input[i] != '\0'); i++, j++)
//   {
//     input[j] = input[i];
//   }
//   input[j] = '\0';
//   printf("%s", input);
// }

// printf("curIElem: %s\n", currentInputElem);
// printf("curIElem: %s\n", tempCurrentInputElem);
// printf("curFElem: %s\n", currentFormatElem);

// void inputParsing(char inputStatic[16384], char currentInputElem[8192],
//                   bool *inputLoaded) {
//   getNextElemWithStrtok(inputStatic, currentInputElem, INPUD_);
//   if (strcmp(currentInputElem, OUR_ERROR_) != 0) {
//     *inputLoaded = true;
//   }
// }

// printf("currentFormatElem:[%s]\n", currentFormatElem);

// printf("inputStatic:[%s]\n", inputStatic);

// printf("currentInputElem:[%s]\n", currentInputElem);

// void formatI(char currentInputElem[8192], bool *varArgLoaded,
//              void *currentVarArg) {
//   int *intP = currentVarArg;
//   if (intP != NULL) {
//     *varArgLoaded = true;
//     *intP = atoi(currentInputElem);
//   } else {
//     *varArgLoaded = false;
//   }
// }

// char *parseNextSpecifier(char *input) {
//   char *returnValue = NULL;
//   char *tempStr = NULL;
//   static bool isInitilized = false;
//   if (isInitilized) {
//     tempStr = strtok(NULL, "%");
//   } else {
//     tempStr = strtok(input, "%");
//     isInitilized = true;
//   }
//   //   printf("\n[%s]\n", tempStr);
//   if (tempStr == NULL) {
//     returnValue = "PIZDEC";
//   } else {
//     returnValue = tempStr;
//   }
//   return returnValue;
// }

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

//  if (currentSpecifier[0] == 's') {
//     strcpy(va_arg(args, char *), "booba");
//   } else if (currentSpecifier[0] == 'd' || currentSpecifier[0] == 'i') {
//     int *intP = va_arg(args, int *);
//     if (intP != NULL) {
//       *intP = 67;
//     } else {
//       varArgsEnded = true;
//     }
//   } else if (currentSpecifier[0] == 'c') {
//     int *charP = va_arg(args, int *);
//     if (charP != NULL) {
//       *charP = 67;
//     } else {
//       varArgsEnded = true;
//     }
//   } else if (currentSpecifier[0] == 'f') {
//     double *doubleP = va_arg(args, double *);
//     if (doubleP != NULL) {
//       *doubleP = 67.67;
//     } else {
//       varArgsEnded = true;
//     }
//   }

// if (isInitilized) {
//   switch (type) {
//     case INPUD_:
//       currentInputPtr = strtok_r(NULL, inputDelims, &currentInputPtr);
//       returnStr = currentInputPtr;
//       break;
//     case FORMAD_:
//       currentFormatPtr = strtok_r(NULL, formatDelims, &currentFormatPtr);
//       returnStr = currentFormatPtr;
//       break;
//   }
// } else {  // if not initialized - then initialize
//   switch (type) {
//     case INPUD_:
//       currentInputPtr = strtok_r(input, inputDelims, &currentInputPtr);
//       returnStr = currentInputPtr;
//       break;
//     case FORMAD_:
//       currentFormatPtr = strtok_r(input, formatDelims, &currentFormatPtr);
//       returnStr = currentFormatPtr;
//       break;
//   }
//   isInitilized = true;
// }

// if (isInitilized) {
//       currentInputPtr = strtok_r(NULL, inputDelims, &currentInputPtr);
//       returnStr = currentInputPtr;
//       break;
// } else {  // if not initialized - then initialize
//       currentInputPtr = strtok_r(input, inputDelims, &currentInputPtr);
//       returnStr = currentInputPtr;
//       break;
// }