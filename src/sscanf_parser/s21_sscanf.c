#include "s21_sscanf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUD_ 1
#define FORMAD_ 2

#define OUR_ERROR_ "KufLv91ySdu64DYPiXOH"

#define MISMADCH_ 1
#define ENDET_ 2

struct Specificators;


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
    struct Specificators Specif = {-1, -1, (char)NULL, (char)NULL};
    // CURRENT FORMAT ELEMENT PARSING:
    formatParsing(formatStatic, currentFormatElem, &formatLoaded, &Specif);
    // CURRENT INPUT ELEMENT PARSING:
    inputParsing(inputStatic, currentInputElem, &inputLoaded);
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

void getNextElem(char *input, char elem[8192], int type) {
  char *returnStr = NULL;
  static bool isInputInitilized = false, isFormatInitilized = false;
  char *currentInputPtr = NULL, *currentFormatPtr = NULL;
  char inputDelims[] = {'\t', 32, '\n'};
  char formatDelims[] = "%";

  switch (type) {
    case INPUD_:
      if (isInputInitilized) {
        currentInputPtr = strtok_r(NULL, inputDelims, &currentInputPtr);
        break;
      } else {  // if not initialized - then initialize
        currentInputPtr = strtok_r(input, inputDelims, &currentInputPtr);
        break;
      }
    case FORMAD_:
      if (isFormatInitilized) {
        currentFormatPtr = strtok_r(NULL, formatDelims, &currentFormatPtr);
        break;
      } else {  // if not initialized - then initialize
        currentFormatPtr = strtok_r(input, formatDelims, &currentFormatPtr);
        break;
      }
  }

  if (type == INPUD_) {
    returnStr = currentInputPtr;
  } else if (type == FORMAD_) {
    returnStr = currentFormatPtr;
  }

  if (returnStr != NULL) {
    strcpy(elem, returnStr);
  } else {  // if return is NULL then we return "error" string
    strcpy(elem, OUR_ERROR_);
  }
}

void formatParsing(char formatStatic[16384], char currentFormatElem[8192],
                   bool *formatLoaded, struct Specificators *Specif) {
  getNextElem(formatStatic, currentFormatElem, FORMAD_);
  if (strcmp(currentFormatElem, OUR_ERROR_) != 0) {
    *formatLoaded = true;
    char *temp = currentFormatElem;
    if (*temp  == '*') {
      (*Specif).argWidth = 1;
      temp++;
    } else if (*temp >= '1' && *temp <= '9') {
        (*Specif).width = atoi(temp);
      while (*temp >= '0' && *temp <= '9') {
        temp++;
      }
    }
    char nextSym[2];
    sprintf(nextSym, "%c", *temp);
    if (strpbrk(nextSym, "lLh")) {
      (*Specif).length = *temp;
      temp++;
    }
    sprintf(nextSym, "%c", *temp);
    if (strpbrk(nextSym, "cdieEfgGosuxXpn")) {
      (*Specif).Specif = *temp;
      
    } else {
      printf("error"); //тут типо ошибка при парсинге
    }
    
    // parsing current format element. worst case, something like this:
    // "*6hhi"
  }
}

void inputParsing(char inputStatic[16384], char currentInputElem[8192],
                  bool *inputLoaded) {
  getNextElem(inputStatic, currentInputElem, INPUD_);
  if (strcmp(currentInputElem, OUR_ERROR_) != 0) {
    *inputLoaded = true;
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
  
    // [0] part is of course incorrect, properly parsed format
    // logic is needed here.
    assignI(tempCurrentInputElem, varArgLoaded, currentVarArg);
  
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

// shrakmer: тут я хомячу код потому что мне так удобно, в конце удалим:
// ---------------------------------------------------------------------

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