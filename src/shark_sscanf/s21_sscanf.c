#include "s21_sscanf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUR_ERROR_ "KufLv91ySdu64DYPiXOHGx5Jj9Q2eKcYwnrjxhQG"

#define MISMADCH_ 1
#define ENDET_ 2
#define FORMAD_ERR_ 3

// 1st argument is like user input for scanf
// 2nd argument are the specifiers
// 3rd (varargs) are parameters to raspihat according to specifiers :)
int s21_sscanf(const char *input, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char inputLocal[16384] = {0};   // local copy of whole "input" parameter
  char formatLocal[16384] = {0};  // local copy of whole "format" parameter
  strcpy(inputLocal, input);
  strcpy(formatLocal, format);

  char currentInputElem[8192] = {0};
  char currentFormatElem[8192] = {0};
  size_t n_counter = 0;  // ??
  int status = 0;
  int isScanfStarted = 0;    // ??
  int counterForReturn = 0;  // ??
  bool startParsing = true;
  while (status != MISMADCH_ && status != ENDET_) {
    int formatLoaded = 0;
    int inputLoaded = 0;
    int varArgLoaded = 0;
    struct Specifiers specifiers = {-1, -1, -1, -1};
    // CURRENT FORMAT ELEMENT PARSING:
    char checkDelim =
        formatParsing(formatLocal, currentFormatElem, &formatLoaded,
                      &specifiers, &isScanfStarted, &status);
    if (status != MISMADCH_) {  // maybe change to FORMAD_ERR
      // printf("\n[%s]\n", currentFormatElem);
      if (specifiers.argWid == 1) {  //если  *, то ширину берем из args // ?????
        specifiers.wid = va_arg(args, int);
      }

      checkFormatError(specifiers,  // is this needed ???
                       &status);  //сочетается ли длина со спецификатором

      if (specifiers.type == 'c' && specifiers.wid == -1) {  // ??????
        specifiers.wid = 1;
      }

      ifSpecIsD(&specifiers, inputLocal);
      ifSpecIsI(&specifiers, inputLocal);
      ifSpecIsF(&specifiers, inputLocal);
      ifSpecIsO(&specifiers, inputLocal);
      ifSpecIsX(&specifiers, inputLocal);
      ifSpecIsP(&specifiers, inputLocal);

      // CURRENT INPUT ELEMENT PARSING:
      if (specifiers.type != 'n') {
        inputParsing(inputLocal, currentInputElem, specifiers.wid, &inputLoaded,
                     specifiers.type, checkDelim, &startParsing);

      } else {
        inputLoaded = true;
      }
      // printf("\n[%s]\n", currentInputElem);

      // CURRENT VARARG ELEMENT PARSING:
      varArgParsingAndAssignment(currentFormatElem, currentInputElem,
                                 &varArgLoaded, va_arg(args, void *),
                                 specifiers, &n_counter);

      if (args != 0) {
        counterForReturn++;
      }
      // -------------------------------
      if (formatLoaded == false && inputLoaded == false &&
          varArgLoaded == false) {
        status = ENDET_;

      } else if (formatLoaded + inputLoaded + varArgLoaded > 0 &&
                 formatLoaded + inputLoaded + varArgLoaded < 3) {
        if (counterForReturn < 2) {
          counterForReturn--;
        }
        status = MISMADCH_;
      }
    }
  }
  va_end(args);
  return counterForReturn;  // to fix, I don't know what sscanf should return
                            // and why
}

void getNextFormatElem(char *input, char elem[8192], int *isScanfStarted) {
  // ??????????????????????? maybe to rewrite this
  char *returnStr = NULL;
  static char *currentFormatString = NULL;
  char formatDelims[] = "%";
  if (*isScanfStarted == 0) {
    currentFormatString = input;
    *isScanfStarted = 1;
  }
  while (*currentFormatString != '\0' && *currentFormatString != '%') {
    currentFormatString++;
  }
  if (*currentFormatString != '\0') {
    currentFormatString++;
    returnStr = currentFormatString;
  } else {
    currentFormatString = NULL;
  }
  if (returnStr != NULL) {
    strcpy(elem, returnStr);
  } else {  // if return is NULL then we return "error" string
    strcpy(elem, OUR_ERROR_);
  }
}

char formatParsing(char formatStatic[16384], char currentFormatElem[8192],
                   int *formatLoaded, struct Specifiers *specifiers,
                   int *isScanfStarted, int *status) {
  getNextFormatElem(formatStatic, currentFormatElem, isScanfStarted);
  // parsing current format element. worst case, something like this:
  // "*67hi"
  if (strcmp(currentFormatElem, OUR_ERROR_) != 0) {  // if no error
    *formatLoaded = true;

    if (*currentFormatElem == '*') {
      (*specifiers).argWid = 1;
      currentFormatElem++;
    } else if (*currentFormatElem >= '1' && *currentFormatElem <= '9') {
      (*specifiers).wid = atoi(currentFormatElem);
      while (*currentFormatElem >= '0' && *currentFormatElem <= '9') {
        currentFormatElem++;
      }
    }
    char nextSym[2];                             // ??
    sprintf(nextSym, "%c", *currentFormatElem);  // ??
    if (strpbrk(nextSym, "lLh")) {               // ??
      (*specifiers).leng = *currentFormatElem;
      currentFormatElem++;
    }
    sprintf(nextSym, "%c", *currentFormatElem);
    if (strpbrk(nextSym, "cdieEfgGosuxXpn")) {
      (*specifiers).type = *currentFormatElem;
    } else if (nextSym[0] == '%') {
      // do nothing
    } else {
      *status = MISMADCH_;  // ??? maybe an unknown type error here
    }
  }
  currentFormatElem++;
  return *currentFormatElem;
}

void ifSpecIsD(struct Specifiers *Specif, char inputStatic[16384]) {
  int startParse = 0;
  int j = 0;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).type == 'd' ||
      (*Specif).type == 'u') {  //если у нас какое то число и нет ширины -
                                //ширина пока встречаем в строке цифры.
    if ((*Specif).wid == -1) {
      (*Specif).wid = startParse;
      while (inputStatic[(*Specif).wid] >= '0' &&
             inputStatic[(*Specif).wid] <= '9') {
        (*Specif).wid++;
      }
    } else {  // если задана ширина и в строке встретилось не число раньше, чем
              // кончилась ширина, то это становится новой шириной, а не число
              // остается в строке
      int findNotNumber = (*Specif).wid;
      int i = startParse;
      while (inputStatic[i] >= '0' && inputStatic[i] <= '9' &&
             findNotNumber > 0) {
        findNotNumber--;
        i++;
      }
      if (findNotNumber != 0) {
        (*Specif).wid = i;
      }
    }
  }
}

void ifSpecIsI(struct Specifiers *Specif, char inputStatic[16384]) {
  int startParse = 2;
  int j = 0;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).type == 'i') {
    if ((inputStatic[0] != '0' &&
         !((inputStatic[0] == '+' || inputStatic[0] == '-'))) ||
        (inputStatic[1] != '0' &&
         ((inputStatic[0] == '+' ||
           inputStatic[0] ==
               '-')))) {  // если первое не 0 - то число десятичное
      ifSpecIsD(Specif, inputStatic);
    } else {
      if (inputStatic[startParse - 1] ==
          'x') {  // если второе х - то шестнадцатиричное
        if ((*Specif).wid == -1) {
          (*Specif).wid = startParse;
          while ((inputStatic[(*Specif).wid] >= '0' &&
                  inputStatic[(*Specif).wid] <= '9') ||
                 (inputStatic[(*Specif).wid] >= 'a' &&
                  inputStatic[(*Specif).wid] <= 'f') ||
                 (inputStatic[(*Specif).wid] >= 'A' &&
                  inputStatic[(*Specif).wid] <= 'F')) {
            (*Specif).wid++;
          }
        } else {
          int findNotNumber = (*Specif).wid;
          int i = startParse;
          while (((inputStatic[i] >= '0' && inputStatic[i] <= '9') ||
                  (inputStatic[i] >= 'a' && inputStatic[i] <= 'f') ||
                  (inputStatic[i] >= 'A' && inputStatic[i] <= 'F')) &&
                 findNotNumber > 0) {
            findNotNumber--;
            i++;
          }
          if (findNotNumber != 0) {
            (*Specif).wid = i;
          }
        }
      } else if (inputStatic[startParse - 2] ==
                 '0') {  // если первое 0, а второе не х, то восьмиричное
        startParse--;
        if ((*Specif).wid == -1) {
          (*Specif).wid = startParse;
          while (inputStatic[(*Specif).wid] >= '0' &&
                 inputStatic[(*Specif).wid] <= '7') {
            (*Specif).wid++;
          }
        } else {
          int findNotNumber = (*Specif).wid;
          int i = startParse;
          while (inputStatic[i] >= '0' && inputStatic[i] <= '7' &&
                 findNotNumber > 0) {
            findNotNumber--;
            i++;
          }
          if (findNotNumber != 0) {
            (*Specif).wid = i;
          }
        }
      }
    }
  }
}

void ifSpecIsF(struct Specifiers *Specif, char inputStatic[16384]) {
  int startParse = 0;
  int j = 0;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).type == 'f' || (*Specif).type == 'e' || (*Specif).type == 'E' ||
      (*Specif).type == 'g' || (*Specif).type == 'G') {
    if ((*Specif).wid == -1) {
      (*Specif).wid = startParse;
      int checkDot = 0;
      while ((inputStatic[(*Specif).wid] >= '0' &&
              inputStatic[(*Specif).wid] <= '9') ||
             (inputStatic[(*Specif).wid] == '.' && checkDot == 0)) {
        if (inputStatic[(*Specif).wid] ==
            '.') {  // встречаем точку только 1н раз в числе
          checkDot = 1;
        }
        (*Specif).wid++;
      }
      if (inputStatic[(*Specif).wid] == 'e' ||
          inputStatic[(*Specif).wid] == 'E') {
        (*Specif).wid++;
        if (inputStatic[(*Specif).wid] == '+' ||
            inputStatic[(*Specif).wid] == '-') {
          (*Specif).wid++;
        }
        while ((inputStatic[(*Specif).wid] >= '0' &&
                inputStatic[(*Specif).wid] <= '9')) {
          (*Specif).wid++;
        }
      }
    } else {
      int findNotNumber = (*Specif).wid;
      int i = startParse;
      int checkDot = 0;
      while (((inputStatic[i] >= '0' && inputStatic[i] <= '9') ||
              (inputStatic[i] == '.' && checkDot == 0)) &&
             findNotNumber > 0) {
        if (inputStatic[i] == '.') {
          checkDot = 1;
        }
        findNotNumber--;
        i++;
      }
      if (inputStatic[i] == 'e' || inputStatic[i] == 'E') {
        i++;
        findNotNumber--;
        if (inputStatic[i] == '+' || inputStatic[i] == '-') {
          i++;
          findNotNumber--;
        }
        while ((inputStatic[i] >= '0' && inputStatic[i] <= '9')) {
          i++;
          findNotNumber--;
        }
      }
      if (findNotNumber != 0) {
        (*Specif).wid = i;
      }
    }
  }
}

void ifSpecIsO(struct Specifiers *Specif, char inputStatic[16384]) {
  int startParse = 0;
  int j = 0;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).type == 'o') {  //если у нас какое то число и нет ширины -
                                //ширина пока встречаем в строке цифры.
    if ((*Specif).wid == -1) {
      (*Specif).wid = startParse;
      while (inputStatic[(*Specif).wid] >= '0' &&
             inputStatic[(*Specif).wid] <= '7') {
        (*Specif).wid++;
      }
    } else {  // если задана ширина и в строке встретилось не число раньше, чем
              // кончилась ширина, то это становится новой шириной, а не число
              // остается в строке
      int findNotNumber = (*Specif).wid;
      int i = startParse;
      while (inputStatic[i] >= '0' && inputStatic[i] <= '7' &&
             findNotNumber > 0) {
        findNotNumber--;
        i++;
      }
      if (findNotNumber != 0) {
        (*Specif).wid = i;
      }
    }
  }
}

void ifSpecIsX(struct Specifiers *Specif, char inputStatic[16384]) {
  int startParse = 0;
  int j = 0;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).type == 'x' ||
      (*Specif).type == 'X') {  //если у нас какое то число и нет ширины -
                                //ширина пока встречаем в строке цифры.
    if ((*Specif).wid == -1) {
      (*Specif).wid = startParse;
      while ((inputStatic[(*Specif).wid] >= '0' &&
              inputStatic[(*Specif).wid] <= '9') ||
             (inputStatic[(*Specif).wid] >= 'a' &&
              inputStatic[(*Specif).wid] <= 'f') ||
             (inputStatic[(*Specif).wid] >= 'A' &&
              inputStatic[(*Specif).wid] <= 'F')) {
        (*Specif).wid++;
      }
    } else {  // если задана ширина и в строке встретилось не число раньше, чем
              // кончилась ширина, то это становится новой шириной, а не число
              // остается в строке
      int findNotNumber = (*Specif).wid;
      int i = startParse;
      while ((inputStatic[(*Specif).wid] >= '0' &&
              inputStatic[(*Specif).wid] <= '9') ||
             (inputStatic[(*Specif).wid] >= 'a' &&
              inputStatic[(*Specif).wid] <= 'f') ||
             (inputStatic[(*Specif).wid] >= 'A' &&
              inputStatic[(*Specif).wid] <= 'F') &&
                 findNotNumber > 0) {
        findNotNumber--;
        i++;
      }
      if (findNotNumber != 0) {
        (*Specif).wid = i;
      }
    }
  }
}

void ifSpecIsP(struct Specifiers *Specif, char inputStatic[16384]) {
  int startParse = 0;
  int j = 0;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).type == 'p') {  //если у нас какое то число и нет ширины -
                                //ширина пока встречаем в строке цифры.
    if ((*Specif).wid == -1) {
      (*Specif).wid = startParse;
      while ((inputStatic[(*Specif).wid] >= '0' &&
              inputStatic[(*Specif).wid] <= '9') ||
             (inputStatic[(*Specif).wid] >= 'a' &&
              inputStatic[(*Specif).wid] <= 'f') ||
             (inputStatic[(*Specif).wid] >= 'A' &&
              inputStatic[(*Specif).wid] <= 'F')) {
        (*Specif).wid++;
      }
    } else {  // если задана ширина и в строке встретилось не число раньше, чем
              // кончилась ширина, то это становится новой шириной, а не число
              // остается в строке
      int findNotNumber = (*Specif).wid;
      int i = startParse;
      while ((inputStatic[(*Specif).wid] >= '0' &&
              inputStatic[(*Specif).wid] <= '9') ||
             (inputStatic[(*Specif).wid] >= 'a' &&
              inputStatic[(*Specif).wid] <= 'f') ||
             (inputStatic[(*Specif).wid] >= 'A' &&
              inputStatic[(*Specif).wid] <= 'F') &&
                 findNotNumber > 0) {
        findNotNumber--;
        i++;
      }
      if (findNotNumber != 0) {
        (*Specif).wid = i;
      }
    }
  }
}

void varArgParsingAndAssignment(char currentFormatElem[8192],
                                char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg, struct Specifiers Specif,
                                size_t *n_counter) {
  // here we will need to get a var arg based on currentFormatElem and set it
  // through a pointer to what we parsed from currentInputElem.
  // See formatI for a not perfect example

  // needed, cause passing static arrays too deep breaks them for some reason:
  char tempCurrentInputElem[8192] = {0};
  strcpy(tempCurrentInputElem, currentInputElem);

  if (Specif.type ==
      'i') {  // тут вместо строки уже можно структурой пользоваться

    // [0] part is of course incorrect , properly parsed format
    // logic is needed here.
    assignI(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 's' || Specif.type == 'c') {
    assignS(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 'f' || Specif.type == 'e' || Specif.type == 'E' ||
             Specif.type == 'g' || Specif.type == 'G') {
    assignF(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 'd' || Specif.type == 'u') {
    assignD(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 'o') {
    assignO(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 'x' || Specif.type == 'X') {
    assignX(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 'n') {
    assignN(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  } else if (Specif.type == 'p') {
    assignP(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter);
  }
}

void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    *n_counter = *n_counter + strlen(inCurrentInputElem);
    int checkSign = 1;
    int forNcount = 0;
    int i;  // чтобы перепрыгнуть знак
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
      *((int *)currentVarArg) =
          checkSign *
          strtol(temp, NULL,
                 16);  // либо свой strtol написать, либо функцию преобразования
                       // из 16й в 10ю (что наверное проще)

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
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    strcpy(currentVarArg, currentInputElem);
    *n_counter = *n_counter + strlen((char *)currentVarArg);
  } else {
    *varArgLoaded = false;
  }
}

void assignF(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    *((float *)currentVarArg) = atof(inCurrentInputElem);
    *n_counter = *n_counter + strlen(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignD(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    // int checkLoad = *((int *)currentVarArg);
    *((int *)currentVarArg) = atoi(inCurrentInputElem);

    *n_counter = *n_counter + strlen(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignO(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    *n_counter = *n_counter + strlen(inCurrentInputElem);
    int checkSign = 1;
    int i;
    if (inCurrentInputElem[0] == '-') {
      checkSign = -1;
      temp++;
    } else if (inCurrentInputElem[0] == '+') {
      checkSign = 1;
      temp++;
    }
    *varArgLoaded = true;
    *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 8);
  } else {
    *varArgLoaded = false;
  }
}

void assignX(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    *n_counter = *n_counter + strlen(inCurrentInputElem);
    int checkSign = 1;
    int i;
    if (inCurrentInputElem[0] == '-') {
      checkSign = -1;
      temp++;
    } else if (inCurrentInputElem[0] == '+') {
      checkSign = 1;
      temp++;
    }
    *varArgLoaded = true;
    *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 16);
  } else {
    *varArgLoaded = false;
  }
}

void assignN(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    *((int *)currentVarArg) = *(int *)n_counter;
    int forNcount = *n_counter;
    while (forNcount != 0) {
      *n_counter = *n_counter + 1;
      forNcount = forNcount / 10;
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignP(
    char inCurrentInputElem[8192], bool *varArgLoaded, void *currentVarArg,
    size_t *n_counter) {  // при отрицательных значениях какой-то не такой вывод
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    int i;
    *varArgLoaded = true;
    *((long int *)currentVarArg) = strtol(temp, NULL, 16);
    *n_counter = *n_counter + strlen(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void inputParsing(char inputFlip[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded, char Specif, char checkDelim,
                  bool *startParsing) {
  fillOneByOne(inputFlip, currentInputElem, wid, Specif, checkDelim,
               startParsing);

  if (strcmp(currentInputElem, OUR_ERROR_) != 0) {
    *inputLoaded = true;
  }
}

void fillOneByOne(char input[16384], char currentInputElem[8192], int wid,
                  char Specif, char checkDelim, bool *startParsing) {
  int i = 0;
  int j = 0;
  bool checkWid = false;

  if (wid == -1) {
    checkWid = true;
  }
  while (input[i] != '\0' && (j < wid || checkWid)) {
    if (i == 0 &&
        (Specif != 'c' &&
         !(*startParsing))) {  // если s, то игнорим все делимы в начале
      while (s21_match("\t \n", input[i])) {
        i++;
      }
    }
    *startParsing = false;

    if (s21_match("\t \n", input[i]) == false) {
      currentInputElem[j] = input[i];
      j++;
    } else if (Specif != 'c') {  // если поймали разделитель - прерываем
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

void checkFormatError(struct Specifiers Specif, int *status) {  // ?????
  char Sym[2];
  sprintf(Sym, "%c", Specif.type);
  if (Specif.leng == 'l' || Specif.leng == 'h') {
    if (!strpbrk(Sym, "idouxX")) {
      // *status = MISMADCH_; тут оказывается он просто игнорит, даже саму
      // функцию наверное можно удалить просто
    }
  } else if (Specif.leng == 'L') {
    if (!strpbrk(Sym, "eEfgG")) {
      // *status = MISMADCH_;
    }
  }
}

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