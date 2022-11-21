#include "s21_sscanf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUR_ERROR_ "KufLv91ySdu64DYPiXOHGx5Jj9Q2eKcYwnrjxhQG"

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
    // printf("\n[%s]\n", currentFormatElem);
    if (Specif.argWidth == 1) { //если  *, то ширину берем из args
      Specif.width = va_arg(args, int);
    }
   
    checkFormatError(Specif);  //сочетается ли длина со спецификатором

    if (Specif.Specif == 'c' && Specif.width == -1) {
      Specif.width = 1;
    }

    ifSpecIsD(&Specif, inputStatic);
    ifSpecIsI(&Specif, inputStatic);
    ifSpecIsF(&Specif, inputStatic);
    
    
    // CURRENT INPUT ELEMENT PARSING:
    inputParsing(inputStatic, currentInputElem, Specif.width, &inputLoaded, Specif.Specif);
    // printf("\n[%s]\n", currentInputElem);

    // CURRENT VARARG ELEMENT PARSING:
    varArgParsingAndAssignment(currentFormatElem, currentInputElem,
                               &varArgLoaded, va_arg(args, void *), Specif);
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
                   bool *formatLoaded, struct Specificators *Specif) {
  getNextFormatElem(formatStatic, currentFormatElem);
  if (strcmp(currentFormatElem, OUR_ERROR_) != 0) {
    *formatLoaded = true;
        
    if (*currentFormatElem == '*') {
      (*Specif).argWidth = 1;
      currentFormatElem++;
    } else if (*currentFormatElem >= '1' && *currentFormatElem <= '9') {
        (*Specif).width = atoi(currentFormatElem);
      while (*currentFormatElem >= '0' && *currentFormatElem <= '9') {
        currentFormatElem++;
      }
    }
    char nextSym[2];
    sprintf(nextSym, "%c", *currentFormatElem);
    if (strpbrk(nextSym, "lLh")) {
      (*Specif).length = *currentFormatElem;
      currentFormatElem++;
    }
    sprintf(nextSym, "%c", *currentFormatElem);
    if (strpbrk(nextSym, "cdieEfgGosuxXpn")) {
      (*Specif).Specif = *currentFormatElem;
    } else {
      printf("error"); //тут типо ошибка при парсинге
    }
    
    // parsing current format element. worst case, something like this:
    // "*6hhi"
  }
}

void checkFormatError(struct Specificators Specif) {
  char Sym[2];
  sprintf(Sym, "%c", Specif.Specif);
  if (Specif.length == 'l' || Specif.length == 'h') {
    if (!strpbrk(Sym, "idouxX")) {
      //ошибка и выход из программы, сюда наверное нужно статус передавать и изменить его
    }
  } else if (Specif.length == 'L') {
    if (!strpbrk(Sym, "eEfgG")) {
      //ошибка и выход из программы
    }
  } 
}

void ifSpecIsD(struct Specificators *Specif, char inputStatic[16384]) {
  int startParse = 0;
  if (inputStatic[0] == '+' || inputStatic[0] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'd') {//если у нас какое то число и нет ширины - ширина пока встречаем в строке цифры. 
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9') {
          (*Specif).width++;
        }
      } else { // если задана ширина и в строке встретилось не число раньше, чем кончилась ширина, то это становится новой шириной, а не число остается в строке
        int findNotNumber = (*Specif).width;
        int i = startParse;
        while (inputStatic[i] >= '0' && inputStatic[i] <= '9' && findNotNumber > 0) {
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
      }
    }
}

void ifSpecIsI(struct Specificators *Specif, char inputStatic[16384]) {
  int startParse = 2;
  if (inputStatic[0] == '+' || inputStatic[0] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'i') {
  if ((inputStatic[0] != '0' && !((inputStatic[0] == '+' || inputStatic[0] == '-'))) ||
      (inputStatic[1] != '0' && ((inputStatic[0] == '+' || inputStatic[0] == '-'))) ){ // если первое не 0 - то число десятичное
        ifSpecIsD(Specif, inputStatic);
  } else {
    if (inputStatic[startParse - 1] == 'x') { // если второе х - то шестнадцатиричное
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9')
        || (inputStatic[(*Specif).width] >= 'a' && inputStatic[(*Specif).width] <= 'f')
        || (inputStatic[(*Specif).width] >= 'A' && inputStatic[(*Specif).width] <= 'F')) {
          (*Specif).width++;
        }
      } else {
        int findNotNumber = (*Specif).width;
        int i = startParse;
        while (((inputStatic[i] >= '0' && inputStatic[i] <= '9')
        || (inputStatic[i] >= 'a' && inputStatic[i] <= 'f')
        || (inputStatic[i] >= 'A' && inputStatic[i] <= 'F')) && findNotNumber > 0) {
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
      }
    } else if (inputStatic[startParse - 2] == '0') { // если первое 0, а второе не х, то восьмиричное
      startParse--;
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '7') {
          (*Specif).width++;
        }
      } else {
        int findNotNumber = (*Specif).width;
        int i = startParse;
        while (inputStatic[i] >= '0' && inputStatic[i] <= '7' && findNotNumber > 0) {
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
      }
    }
  }
}
}

void ifSpecIsF(struct Specificators *Specif, char inputStatic[16384]) {
  int startParse = 0;
  if (inputStatic[0] == '+' || inputStatic[0] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'f') {
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        int checkDot = 0;
        while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9')
        || (inputStatic[(*Specif).width] == '.' && checkDot == 0)) {
          if (inputStatic[(*Specif).width] == '.') { // встречаем точку только 1н раз в числе
            checkDot = 1;
          }
          (*Specif).width++;
        }
      } else { 
        int findNotNumber = (*Specif).width;
        int i = startParse;
        int checkDot = 0;
        while (((inputStatic[i] >= '0' && inputStatic[i] <= '9')
        || (inputStatic[i] == '.' && checkDot == 0)) && findNotNumber > 0) {
          if (inputStatic[i] == '.') {
            checkDot = 1;
          }
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
      }
    }
}

void varArgParsingAndAssignment(char currentFormatElem[8192],
                                char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg, struct Specificators Specif) {
  // here we will need to get a var arg based on currentFormatElem and set it
  // through a pointer to what we parsed from currentInputElem.
  // See formatI for a not perfect example

  // needed, cause passing static arrays too deep breaks them for some reason:
  char tempCurrentInputElem[8192] = {0};
  strcpy(tempCurrentInputElem, currentInputElem);
  
  if (Specif.Specif == 'i') {// тут вместо строки уже можно структурой пользоваться

    // [0] part is of course incorrect , properly parsed format
    // logic is needed here.
    assignI(tempCurrentInputElem, varArgLoaded, currentVarArg);
  } else if (Specif.Specif == 's' || Specif.Specif == 'c') {
    assignS(tempCurrentInputElem, varArgLoaded, currentVarArg);
  } else if (Specif.Specif == 'f') {
    assignF(tempCurrentInputElem, varArgLoaded, currentVarArg);
  } else if (Specif.Specif == 'd') {
    assignD(tempCurrentInputElem, varArgLoaded, currentVarArg);
  }
}

void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) {
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    int checkSign = 1;
    int i; // чтобы перепрыгнуть знак 
    if (inCurrentInputElem[0] == '-') {
      checkSign = -1;
      i = 2; 
      temp++;
    } else if (inCurrentInputElem[0] == '+') {
      checkSign = 1;
      i = 2;
      temp++;
    } else {
      i = 1;
    }
    *varArgLoaded = true;
    if (inCurrentInputElem[i] == 'x') { 
      temp++;
      temp++;
      *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 16); // либо свой strtol написать, либо функцию преобразования из 16й в 10ю (что наверное проще)
    } else if (inCurrentInputElem[i - 1] == '0') {
      temp++;
      *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 8);
    } else {
      *((int *)currentVarArg) = checkSign * atoi(inCurrentInputElem);
    }
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

void assignF(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    *((float *)currentVarArg) = atof(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignD(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    *((int *)currentVarArg) = atoi(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}


char *strtokChop(char *str, const char *delim, char *leftOver) {
  static char *new_str;
  char *tmp = str;
  char rememberDelim[2] = {'\0', '\0'};
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
        rememberDelim[0] = *new_str;
         
        *new_str = 0;
        new_str++;
      } else {
        new_str = NULL;  // если строка закончилась то NULL
      }
    }
  }

  // right chop goes into leftOver:
  if (new_str != NULL) {
    if (rememberDelim[0] != '\0') {
      strcat(leftOver, rememberDelim);
    }
    strcat(leftOver, new_str);
  } else {  // if return is NULL then we fill with "error" string
    strcpy(leftOver, OUR_ERROR_);
  }

  return tmp;  // возвращаем строку до зануленного разделителя
}

void inputParsing(char inputFlip[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded, char Specif) {
  static bool flipFlop = false;
  static char inputFlop[16384] = {0};
  fillOneByOne(inputFlip, currentInputElem, wid, Specif);

  if (strcmp(currentInputElem, OUR_ERROR_) != 0) {
    *inputLoaded = true;
  }
}

void fillOneByOne(char input[16384], char currentInputElem[8192], int wid, char Specif) {
  int i = 0;
  int j = 0;
  bool checkWid = false;
  if (wid == -1) {
    checkWid = true;
  }
  while (input[i] != '\0' && (j < wid || checkWid)) {
    if (i == 0 && Specif == 's') { // если s, то игнорим все делимы в начале
      while (s21_match("\t \n", input[i])) {
        i++;
      }
    }
    if (s21_match("\t \n", input[i]) == false && Specif == 's') {
      currentInputElem[j] = input[i];
      j++;
    } else if (Specif == 's') { // если поймали разделитель - прерываем
      currentInputElem[j] = '\0';
      i--;
      j = wid;
      checkWid = false;
    } else {
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