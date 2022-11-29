#include "s21_sscanf.h"

#include <stdio.h>
#include <stdlib.h>


#define OUR_ERROR_ "KufLv91ySdu64DYPiXOHGx5Jj9Q2eKcYwnrjxhQG"

#define MISMADCH_ 1
#define ENDET_ 2

struct Specificators;


int s21_sscanf(const char *input, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char inputStatic[16384] = {0};   // local copy of whole "input" parameter
  char formatStatic[16384] = {0};  // local copy of whole "format" parameter
  s21_strcpy(inputStatic, input);
  s21_strcpy(formatStatic, format);
  char currentInputElem[8192] = {0};
  char currentFormatElem[8192] = {0};
  size_t n_counter = 0;
  int status = 0;
  int checkStartScanf = 1;
  int counterForReturn = 0;
  bool startParsing = true;
  bool stopMove = false;
  bool checkSpace = false;
  bool checkLoaded = false;
  struct Specificators Specif = {-1, -1, '\0', '\0', '\0', {'\0'}};
  while (status != MISMADCH_ && status != ENDET_) {
    bool formatLoaded = false;
    bool inputLoaded = false;
    bool varArgLoaded = false;
    bool checkArgWidth= false;
    if (Specif.Space == ' ') {
      checkSpace = true;
    } else {
      checkSpace = false;
    }
    Specif.width = -1;
    Specif.argWidth = -1;
    Specif.length = '\0';
    Specif.Specif = '\0';
    Specif.Space = '\0';
    Specif.buff[0] = '\0'; 
    formatParsing(formatStatic, currentFormatElem, &formatLoaded, &Specif, &checkStartScanf, &status);
    if (status == MISMADCH_) {
      break; //мб тут поменять брей и все что ниже запихать под условие
    }
    if (Specif.Specif == 'c' && (Specif.width == -1 || Specif.width == 0)) {
      Specif.width = 1;
    }
    chooseSpecif(&Specif, inputStatic, &stopMove);
    if (Specif.Specif != 'n' && !stopMove) {
    inputParsing(inputStatic, currentInputElem, Specif.width, &inputLoaded, Specif, &startParsing, checkSpace, &n_counter);
    } else {
      if (inputStatic[0] == '\0') {
        n_counter--;
      }
      inputLoaded = true;
    }
    if (input[0] == '\0' && counterForReturn == 0) {
      counterForReturn = EOF;
      inputLoaded = false;
    }
    if (!stopMove && Specif.Specif != '%') {
      if (Specif.argWidth != 1) {
    varArgParsingAndAssignment(currentInputElem,
                               &varArgLoaded, va_arg(args, void *), Specif, &n_counter, &counterForReturn);
      } else {
        checkArgWidth = true;
        counterForReturn--;
      }
    } else if (Specif.Specif != '%') {
        if (counterForReturn == 0) {
            varArgParsingAndAssignment(currentInputElem,
                               &varArgLoaded, va_arg(args, void *), Specif, &n_counter, &counterForReturn);
          if (!varArgLoaded && !checkLoaded) {
            counterForReturn = EOF;
          } else {
            checkLoaded = true;
          }
      } 
    } else if (Specif.Specif == '%') {
      varArgLoaded = true;
     counterForReturn--;
    }
    if (formatLoaded == true && inputLoaded == true &&
        (varArgLoaded == true || checkArgWidth == true)) {
          if (!checkLoaded) {
          counterForReturn++;
          }
      checkArgWidth = false;
    } else {
      status = ENDET_;
    }
  }
  va_end(args);
  return counterForReturn; 
}

void getNextFormatElem(char *input, char elem[8192], int *checkStartScanf) {
  char *returnStr = NULL;
  static char *currentFormatString = NULL;
  bool checkFirst = true;
  if (*checkStartScanf == 1) {
    checkFirst = true;
  } else {
    checkFirst = false;
  }
  if (*checkStartScanf) {
    currentFormatString = input;
    *checkStartScanf = 0;
  }
if (*currentFormatString == '%' && !checkFirst) {
    currentFormatString++;
    returnStr = currentFormatString;
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
    s21_strcpy(elem, returnStr);
  } else {  // if return is NULL then we return "error" string
    s21_strcpy(elem, OUR_ERROR_);
  }
}

char formatParsing(char formatStatic[16384], char currentFormatElem[8192],
                   bool *formatLoaded, struct Specificators *Specif, int *checkStartScanf, int *status) {
    getNextFormatElem(formatStatic, currentFormatElem, checkStartScanf);
  if (s21_strcmp(currentFormatElem, OUR_ERROR_) != 0) {
    *formatLoaded = true;
    if (*currentFormatElem == '*') {
      (*Specif).argWidth = 1;
      currentFormatElem++;
    } else if (*currentFormatElem >= '0' && *currentFormatElem <= '9') {
        (*Specif).width = s21_atoi(currentFormatElem);
      while (*currentFormatElem >= '0' && *currentFormatElem <= '9') {
        currentFormatElem++;
      }
    }
    char nextSym[2];
    sprintf(nextSym, "%c", *currentFormatElem);
    if (s21_strpbrk(nextSym, "lLh")) {
      (*Specif).length = *currentFormatElem;
      currentFormatElem++;
    }
    sprintf(nextSym, "%c", *currentFormatElem);
    if (s21_strpbrk(nextSym, "cdieEfgGosuxXpn")) {
      (*Specif).Specif = *currentFormatElem;
      currentFormatElem++;
      sprintf(nextSym, "%c", *currentFormatElem);
          if (s21_strpbrk(nextSym, "\n \t")) {
            (*Specif).Space = ' ';
          }
          int i = 0;
      while (*currentFormatElem != '%') {
        (*Specif).buff[i] = *currentFormatElem;
        i++;
        currentFormatElem++;
      }
      (*Specif).buff[i] ='\0';
    } else if (nextSym[0] == '%') {
     (*Specif).Specif = *currentFormatElem;
     currentFormatElem++;
     int i = 0;
    while (*currentFormatElem != '%') {
        (*Specif).buff[i] = *currentFormatElem;
        i++;
        currentFormatElem++;
    }
    } else {
       *status = MISMADCH_;
    }
  }
  currentFormatElem++;
  return *currentFormatElem;
}

void chooseSpecif(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  if ((*Specif).Specif == 'd' || (*Specif).Specif == 'u') {
    ifSpecIsD(Specif, inputStatic, stopMove);
  } else if ((*Specif).Specif == 'i') {
    ifSpecIsI(Specif, inputStatic, stopMove);
  } else if ((*Specif).Specif == 'f' || (*Specif).Specif == 'e' || 
  (*Specif).Specif == 'E' || (*Specif).Specif == 'g' || (*Specif).Specif == 'G') {
    ifSpecIsF(Specif, inputStatic, stopMove);
  } else if ((*Specif).Specif == 'o') {
    ifSpecIsO(Specif, inputStatic, stopMove);
  } else if ((*Specif).Specif == 'x' || (*Specif).Specif == 'X' || (*Specif).Specif == 'p') {
    ifSpecIsX(Specif, inputStatic, stopMove);
  }
}

void ifSpecIsD(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
  int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if ((inputStatic[j] == '+' || inputStatic[j] == '-') && (wid > 1 || wid == -1)) {
    startParse++;
  }
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9') {
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      } else { 
        int findNotNumber = (*Specif).width;
        (*Specif).width = startParse;
        int i = startParse;
        bool checkIfAnyNumber = false;
        while (inputStatic[i] >= '0' && inputStatic[i] <= '9' && findNotNumber > 0) {
          findNotNumber--;
          i++;
          (*Specif).width++;
          checkIfAnyNumber = true;
        }
        if (!checkIfAnyNumber) {
          *stopMove = true;
        }
      }
}

void ifSpecIsI(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 2;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if ((inputStatic[j] == '+' || inputStatic[j] == '-') && (wid > 1 || wid == -1)) {
    startParse++;
  }
  if  (inputStatic[startParse - 2] != '0' && inputStatic[startParse - 1] != 'x'){ // если первое не 0 - то число десятичное
        (*Specif).Specif ='d';
        ifSpecIsD(Specif, inputStatic, stopMove);
  } else {
    if (inputStatic[startParse - 1] == 'x') { // если второе х - то шестнадцатиричное
    helpHexPars(Specif, inputStatic, stopMove, startParse);
    } else if (inputStatic[startParse - 2] == '0') { // если первое 0, а второе не х, то восьмиричное
      startParse--;
      startParse--;
      helpOctPars(Specif, inputStatic, stopMove, startParse);
    }
  }
}

void ifSpecIsF(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if ((inputStatic[j] == '+' || inputStatic[j] == '-') && (wid > 1 || wid == -1)) {
    startParse++;
  }
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        int checkDot = 0;
        bool checkNan = false;
        if (((inputStatic[(*Specif).width] == 'i' || inputStatic[(*Specif).width] == 'I')
         && (inputStatic[(*Specif).width + 1] == 'n' || inputStatic[(*Specif).width + 1] == 'N')
         && (inputStatic[(*Specif).width + 2] == 'f' || inputStatic[(*Specif).width + 2] == 'F'))
        || ((inputStatic[(*Specif).width] == 'N' || inputStatic[(*Specif).width] == 'n')
        && (inputStatic[(*Specif).width + 1] == 'a' || inputStatic[(*Specif).width + 1] == 'A')
        && (inputStatic[(*Specif).width + 2] == 'N' || inputStatic[(*Specif).width + 2] == 'n')))
        {
          (*Specif).width = (*Specif).width + 3;
          checkNan = true;
        }
        while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9' && !checkNan)
        || (inputStatic[(*Specif).width] == '.' && checkDot == 0 && (*Specif).width != startParse)) {
          if (inputStatic[(*Specif).width] == '.') { // встречаем точку только 1н раз в числе
            checkDot = 1;
          }
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
        if ((inputStatic[(*Specif).width] == 'e' || inputStatic[(*Specif).width] == 'E') && !checkNan) {
          (*Specif).width++;
            if (inputStatic[(*Specif).width] == '+' || inputStatic[(*Specif).width] == '-') {
              (*Specif).width++;
            }
            while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9')) {
              (*Specif).width++;
            }
        }
      } else { 
        int findNotNumber = (*Specif).width;
        (*Specif).width = startParse;
        int i = startParse;
        bool checkNan = false;
        if ((((inputStatic[(*Specif).width] == 'i' || inputStatic[(*Specif).width] == 'I')
         && (inputStatic[(*Specif).width + 1] == 'n' || inputStatic[(*Specif).width + 1] == 'N')
         && (inputStatic[(*Specif).width + 2] == 'f' || inputStatic[(*Specif).width + 2] == 'F'))
        || ((inputStatic[(*Specif).width] == 'N' || inputStatic[(*Specif).width] == 'n')
        && (inputStatic[(*Specif).width + 1] == 'a' || inputStatic[(*Specif).width + 1] == 'A')
        && (inputStatic[(*Specif).width + 2] == 'N' || inputStatic[(*Specif).width + 2] == 'n')))
        && findNotNumber >= 3)
        {
          (*Specif).width = (*Specif).width + 3;
          checkNan = true;
        }
        int checkDot = 0;
        while (((inputStatic[i] >= '0' && inputStatic[i] <= '9' && !checkNan)
        || (inputStatic[i] == '.' && checkDot == 0)) && findNotNumber > 0) {
          if (inputStatic[i] == '.') {
            checkDot = 1;
          }
          findNotNumber--;
          (*Specif).width++;
          i++;
        }
        if ((inputStatic[i] == 'e' || inputStatic[i] == 'E') && !checkNan) {
          i++;
          findNotNumber--;
          (*Specif).width++;
            if (inputStatic[i] == '+' || inputStatic[i] == '-') {
              i++;
              findNotNumber--;
              (*Specif).width++;
            }
            while ((inputStatic[i] >= '0' && inputStatic[i] <= '9')) {
              i++;
              findNotNumber--;
              (*Specif).width++;
            }
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }   
}

void ifSpecIsO(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if ((inputStatic[j] == '+' || inputStatic[j] == '-') && (wid > 1 || wid == -1)) {
    startParse++;
  }
  helpOctPars(Specif, inputStatic, stopMove, startParse);
}

void ifSpecIsX(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j])) {
    j++;
    startParse++;
  }
  if ((inputStatic[j] == '+' || inputStatic[j] == '-') && (wid > 1 || wid == -1)) {
    startParse++;
  }
  if  ((inputStatic[startParse] == '0' && inputStatic[startParse + 1] == 'x' && (wid > 2 || wid <= -1))
   && (((inputStatic[startParse + 2] >= '0' && inputStatic[startParse + 2] <= '9')
        || (inputStatic[startParse + 2] >= 'a' && inputStatic[startParse + 2] <= 'f')
        || (inputStatic[startParse + 2] >= 'A' && inputStatic[startParse + 2] <= 'F')) )) {
    startParse++;
    startParse++;
  }
  helpHexPars(Specif, inputStatic, stopMove, startParse);
}

void helpHexPars(struct Specificators *Specif, char inputStatic[16384], bool *stopMove, int startParse) {
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9')
        || (inputStatic[(*Specif).width] >= 'a' && inputStatic[(*Specif).width] <= 'f')
        || (inputStatic[(*Specif).width] >= 'A' && inputStatic[(*Specif).width] <= 'F')) {
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      } else {
        int findNotNumber = (*Specif).width;
        (*Specif).width = startParse;
        int i = startParse;
        while (((inputStatic[i] >= '0' && inputStatic[i] <= '9')
        || (inputStatic[i] >= 'a' && inputStatic[i] <= 'f')
        || (inputStatic[i] >= 'A' && inputStatic[i] <= 'F')) && findNotNumber > 0) {
          findNotNumber--;
          i++;
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
}

void helpOctPars(struct Specificators *Specif, char inputStatic[16384], bool *stopMove, int startParse) {
      if ((*Specif).width <= -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '7') {
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      } else { // если задана ширина и в строке встретилось не число раньше, чем кончилась ширина, то это становится новой шириной, а не число остается в строке
        int findNotNumber = (*Specif).width;
        (*Specif).width = startParse;
        int i = startParse;
        while (inputStatic[i] >= '0' && inputStatic[i] <= '7' && findNotNumber > 0) {
          findNotNumber--;
          (*Specif).width++;
          i++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
}


void varArgParsingAndAssignment(char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg, struct Specificators Specif, size_t *n_counter, int *counterForReturn) {
  char tempCurrentInputElem[8192] = {0};
  s21_strcpy(tempCurrentInputElem, currentInputElem);
  if (Specif.Specif == 'i') {
    assignI(tempCurrentInputElem, varArgLoaded, currentVarArg, Specif);
  } else if (Specif.Specif == 's' || Specif.Specif == 'c') {
    assignS(tempCurrentInputElem, varArgLoaded, currentVarArg);
  } else if (Specif.Specif == 'f' || Specif.Specif == 'e' || Specif.Specif == 'E' || Specif.Specif == 'g' || Specif.Specif == 'G') {
    assignF(tempCurrentInputElem, varArgLoaded, currentVarArg, Specif);
  } else if (Specif.Specif == 'd' || Specif.Specif == 'u') {
    assignD(tempCurrentInputElem, varArgLoaded, currentVarArg, Specif);
  } else if (Specif.Specif == 'o') {
    assignO(tempCurrentInputElem, varArgLoaded, currentVarArg, Specif);
  } else if (Specif.Specif == 'x' || Specif.Specif == 'X') {
    assignX(tempCurrentInputElem, varArgLoaded, currentVarArg, Specif);
  } else if (Specif.Specif == 'n') {
    assignN(varArgLoaded, currentVarArg, n_counter, counterForReturn);
  } else if (Specif.Specif == 'p') {
    assignP(tempCurrentInputElem, varArgLoaded, currentVarArg);
  }
}

void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    int checkSign = 1;
    int i = 0;
    while (s21_match("\t \n", inCurrentInputElem[i])) {
        i++;
        temp++;
    }
    if (inCurrentInputElem[i] == '-') {
      checkSign = -1;
      i = i + 2; 
      temp++;
    } else if (inCurrentInputElem[i] == '+') {
      checkSign = 1;
      i = i + 2;
      temp++;
    } else {
      i = i + 1;
    }
    *varArgLoaded = true;
    if (inCurrentInputElem[i] == 'x') { 
      temp++;
      temp++;
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * hexToBaseTenLong(temp); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * hexToBaseTenShort(temp); 
    } else {
       *((int *)currentVarArg) = checkSign * hexToBaseTen(temp); 
    }
    } else if (inCurrentInputElem[i - 1] == '0') {
      temp++;
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * octToBaseTenLong(temp); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * octToBaseTenShort(temp); 
    } else {
       *((int *)currentVarArg) = checkSign * octToBaseTen(temp); 
    }
    } else {
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * s21_atoiLong(temp); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * s21_atoiShort(temp); 
    } else {
       *((int *)currentVarArg) = checkSign * s21_atoi(temp); 
    }
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignS(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    s21_strcpy(currentVarArg, currentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignF(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;    
    if (Specif.length == 'L') {
      *((long double *)currentVarArg) = s21_atofLong(inCurrentInputElem);
    } else if (Specif.length == 'l') {
      *((double *)currentVarArg) = s21_atof(inCurrentInputElem);
    } else {
      *((float *)currentVarArg) = s21_atof(inCurrentInputElem);
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignD(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = s21_atoiLong(inCurrentInputElem); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = s21_atoiShort(inCurrentInputElem); 
    } else {
       *((int *)currentVarArg) = s21_atoi(inCurrentInputElem); 
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignO(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif) {
  if (currentVarArg != NULL) {
      char *temp = inCurrentInputElem;
    int checkSign = 1;
    int i = 0; 
    while (s21_match("\t \n", inCurrentInputElem[i])) {
        i++;
        temp++;
    }
    if (inCurrentInputElem[i] == '-') {
      checkSign = -1;
      temp++;
    } else if (inCurrentInputElem[i] == '+') {
      checkSign = 1;
      temp++;
    }
    *varArgLoaded = true;
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * octToBaseTenLong(temp); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * octToBaseTenShort(temp); 
    } else {
       *((int *)currentVarArg) = checkSign * octToBaseTen(temp); 
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignX(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, struct Specificators Specif) {
  if (currentVarArg != NULL) {
      char *temp = inCurrentInputElem;
    int checkSign = 1;
        int i = 0; 
    while (s21_match("\t \n", inCurrentInputElem[i])) {
        i++;
        temp++;
    } 
    if (inCurrentInputElem[i] == '-') {
      checkSign = -1;
      temp++;
      i++;
    } else if (inCurrentInputElem[i] == '+') {
      checkSign = 1;
      temp++;
      i++;
    }
    if (inCurrentInputElem[i] == '0' && inCurrentInputElem[i + 1] == 'x') {
      temp++;
      temp++;
    }
     *varArgLoaded = true;
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * hexToBaseTenLong(temp); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * hexToBaseTenShort(temp); 
    } else {
       *((int *)currentVarArg) = checkSign * hexToBaseTen(temp); 
    }
  } else {
    *varArgLoaded = false;
        
  }
}

void assignN(bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    *((int *)currentVarArg) = *(int*)n_counter;
    *counterForReturn = *counterForReturn - 1;
  } else {
    *varArgLoaded = false;
  }
}

void assignP(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg) { // при отрицательных значениях какой-то не такой вывод
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    *varArgLoaded = true;
    *((long int *)currentVarArg) = hexToBaseTenLong(temp);
  } else {
    *varArgLoaded = false;
  }
}

void inputParsing(char inputFlip[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded, struct Specificators Specif, bool *startParsing, bool checkSpace, size_t *n_counter) {
  fillOneByOne(inputFlip, currentInputElem, wid, Specif, startParsing, checkSpace, n_counter);
  if (s21_strcmp(currentInputElem, OUR_ERROR_) != 0) {
    *inputLoaded = true;
  }
}

void fillOneByOne(char input[16384], char currentInputElem[8192], int wid, struct Specificators Specif, bool *startParsing, bool checkSpace, size_t *n_counter) {
  int i = 0;
  int j = 0;
  bool checkWid = false;
  if (wid == -1) {
    checkWid = true;
  }
  if (Specif.Specif == 's') {
    *startParsing = false; 
  }
  if (Specif.Specif != '%') {
  while (input[i] != '\0' && (j < wid || checkWid)) {
    if ((i == 0 && (!(*startParsing)))) {
    if ((Specif.Specif == 'c' && checkSpace) || Specif.Specif != 'c') {
      while (s21_match("\t \n", input[i]) && (wid > 0 || checkWid || Specif.Specif == 's' || (Specif.Specif == 'c' && checkSpace))) {
        i++;
     *n_counter = *n_counter + 1;
        if (Specif.Specif != 's') {
        wid--;
        }
      }
    }
    }
    *startParsing = false;
    if (s21_match("\t \n", input[i]) == false) {
      currentInputElem[j] = input[i];
      j++;
    } else if (Specif.Specif == 's') { // если поймали разделитель - прерываем
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
}
  currentInputElem[j] = '\0';
  chopLeft(input, i, n_counter, Specif);
}

void chopLeft(char input[16384], int howMany, size_t *n_counter, struct Specificators Specif) {
  int j = 0, counter = 0;
  bool checkBuff = false; 
  size_t length = s21_strlen(input);
  for (int i = howMany; input[i] != '\0'; i++, j++) {
    counter++;
      input[j] = input[i];
  }
  *n_counter = *n_counter + (int)length - counter;
  input[j] = '\0';
int k = 0;
int i = 0;
j = 0;
  while ((Specif.buff[k] != '\0' && input[i] != '\0') || Specif.Specif == '%') {
    if (s21_match("\t \n", Specif.buff[k]) || Specif.Specif == '%') {
      while (input[i] != '\0' && s21_match("\t \n", input[i])) {
        i++;
      }
      k++;
    } 
      while (Specif.buff[k] != '\0' && s21_match("\t \n", Specif.buff[k])) {
        k++;
      }
      if ((Specif.buff[k] == input[i] && Specif.buff[k] != '\0') || (Specif.Specif == '%' && input[i] == Specif.Specif)) {
        i++;
        k++;
       checkBuff = true;
        if (Specif.Specif == '%') {
      while (input[i] != '\0' && s21_match("\t \n", input[i])) {
        i++;
      }
        }
      } else {
        if (Specif.buff[k] != '\0' ) {
          checkBuff = false;
        }
        break;
      }
      if (Specif.Specif == '%') {
        Specif.Specif = '\0';
        k--;
        k--;
      }
  }
  if(checkBuff && Specif.buff[k] == '\0') {
    *n_counter = *n_counter + 1;
  }
  j = 0;
    if (checkBuff) {
       *n_counter = *n_counter + (int)s21_strlen(Specif.buff); 
  while (input[i] != '\0') {
    input[j] = input[i];
    i++;
    j++;
  }
   input[j] = '\0';
    }
}

unsigned long hexToBaseTenLong(char *hexVal) {
  unsigned long returnValue = 0;
  int hexLen = s21_strlen(hexVal);
  bool numbersStarted = false;
  bool isNegative = false;
  for (int i = 0; i < hexLen; i++) {
    if (hexVal[i] >= 'a' && hexVal[i] <= 'f') {
      returnValue = returnValue + (hexVal[i] - 87) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
      returnValue = returnValue + (hexVal[i] - 55) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] >= '0' && hexVal[i] <= '9') {
      returnValue = returnValue + (hexVal[i] - 48) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] == '-') {
      if (numbersStarted == false) isNegative = true;
    } else if (hexVal[i] == ' ') {
      // do nothing
    }
  }
  if (isNegative) returnValue = returnValue * -1;
  return returnValue;
}

unsigned int hexToBaseTen(char *hexVal) {
  unsigned int returnValue = 0;
  int hexLen = s21_strlen(hexVal);
  bool numbersStarted = false;
  bool isNegative = false;
  for (int i = 0; i < hexLen; i++) {
    if (hexVal[i] >= 'a' && hexVal[i] <= 'f') {
      returnValue = returnValue + (hexVal[i] - 87) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
      returnValue = returnValue + (hexVal[i] - 55) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] >= '0' && hexVal[i] <= '9') {
      returnValue = returnValue + (hexVal[i] - 48) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] == '-') {
      if (numbersStarted == false) isNegative = true;
    } else if (hexVal[i] == ' ') {
      // do nothing
    }
  }
  if (isNegative) returnValue = returnValue * -1;
  return returnValue;
}

unsigned short int hexToBaseTenShort(char *hexVal) {
  unsigned short int returnValue = 0;
  int hexLen = s21_strlen(hexVal);
  bool numbersStarted = false;
  bool isNegative = false;
  for (int i = 0; i < hexLen; i++) {
    if (hexVal[i] >= 'a' && hexVal[i] <= 'f') {
      returnValue = returnValue + (hexVal[i] - 87) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
      returnValue = returnValue + (hexVal[i] - 55) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] >= '0' && hexVal[i] <= '9') {
      returnValue = returnValue + (hexVal[i] - 48) * pow(16, hexLen - i - 1);
      numbersStarted = true;
    } else if (hexVal[i] == '-') {
      if (numbersStarted == false) isNegative = true;
    } else if (hexVal[i] == ' ') { 
      // do nothing
    }
  }
  if (isNegative) returnValue = returnValue * -1;
  return returnValue;
}

unsigned int octToBaseTen(char* octVal) {
  int returnValue = 0;
  int octLen = s21_strlen(octVal);
  bool numbersStarted = false;
  bool isNegative = false;
  for (int i = 0; i < octLen; i++) {
    if (octVal[i] >= '0' && octVal[i] <= '7') {
      returnValue = returnValue + (octVal[i] - '0') * pow(8, octLen - i - 1);
      numbersStarted = true;
    } else if (octVal[i] == '-') {
      if (numbersStarted == false) isNegative = true;
    } else if (octVal[i] == ' ') {
      // do nothing
    }
  }
  if (isNegative) returnValue = returnValue * -1;
  return returnValue;
}

unsigned long int octToBaseTenLong(char* octVal) {
  long int returnValue = 0;
  int octLen = s21_strlen(octVal);
  bool numbersStarted = false;
  bool isNegative = false;
  for (int i = 0; i < octLen; i++) {
    if (octVal[i] >= '0' && octVal[i] <= '7') {
      returnValue = returnValue + (octVal[i] - '0') * pow(8, octLen - i - 1);
      numbersStarted = true;
    } else if (octVal[i] == '-') {
      if (numbersStarted == false) isNegative = true;
    } else if (octVal[i] == ' ') { 
      // do nothing
    }
  }
  if (isNegative) returnValue = returnValue * -1;
  return returnValue;
}

unsigned short int octToBaseTenShort(char* octVal) {
  short int returnValue = 0;
  int octLen = s21_strlen(octVal);
  bool numbersStarted = false;
  bool isNegative = false;
  for (int i = 0; i < octLen; i++) {
    if (octVal[i] >= '0' && octVal[i] <= '7') {
      returnValue = returnValue + (octVal[i] - '0') * pow(8, octLen - i - 1);
      numbersStarted = true;
    } else if (octVal[i] == '-') {
      if (numbersStarted == false) isNegative = true;
    } else if (octVal[i] == ' ') {  
      // do nothing
    }
  }
  if (isNegative) returnValue = returnValue * -1;
  return returnValue;
}

int s21_atoi(char *str) {
  int length = s21_strlen(str);
  int returnValue = 0;
  int sign = 1;
  int i = 0;
  while (s21_match("\t \n", str[i])) {
        i++;
  }
  for (; i < length; i++) {
    if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        sign = -1;
      }
      i++;
    }
    if (!(str[i] >= '0' && str[i] <= '9')) {
      break;
    }
    returnValue = returnValue * 10 + (str[i] - 48);
  }
  return sign * returnValue;
}

short int s21_atoiShort(char *str) {
  int length = s21_strlen(str);
  short int returnValue = 0;
    int sign = 1;
      int i = 0;
  while (s21_match("\t \n", str[i])) {
        i++;
  }
  for (; i < length; i++) {
        if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        sign = -1;
      }
      i++;
    }
    if (!(str[i] >= '0' && str[i] <= '9')) {
      break;
    }
    returnValue = returnValue * 10 + (str[i] - 48);
  }
  return sign * returnValue;
}

long int s21_atoiLong(char *str) {
  int length = s21_strlen(str);
  long int returnValue = 0;
    int sign = 1;
      int i = 0;
  while (s21_match("\t \n", str[i])) {
        i++;
  }
  for (; i < length; i++) {
        if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        sign = -1;
      }
      i++;
    }
    if (!(str[i] >= '0' && str[i] <= '9')) {
      break;
    }
    returnValue = returnValue * 10 + (str[i] - 48);
  }
  return sign * returnValue;
}

double s21_atof(char *str) {
  double returnValue = 0;
  int counterE = 0;
    int sign = 1;
    int i = 0;
            if ((str[i] == 'i' || str[i] == 'I')
         && (str[i + 1] == 'n' || str[i + 1] == 'N')
         && (str[i + 2] == 'f' || str[i + 2] == 'F')) {
          returnValue = INFINITY;
         }
                if ((str[i] == 'N' || str[i] == 'n')
         && (str[i + 1] == 'a' || str[i + 1] == 'A')
         && (str[i + 2] == 'N' || str[i + 2] == 'n')) {
          returnValue = NAN;
         }
  while (s21_match("\t \n", str[i])) {
        i++;
  }
    if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        sign = -1;
      }
      i++;
    }
    while(str[i] >= '0' && str[i] <= '9') {
      returnValue = returnValue * 10 + (str[i] - 48);
      i++;
    }
    if (str[i] == '.') {
      i++;
    }
    int pow1 = 1;
    while(str[i] >= '0' && str[i] <= '9') {
      returnValue = returnValue + (str[i] - 48.0) / (10 * pow1);
      i++;
      pow1 = pow1 * 10;
    }
    if (str[i] == 'e') {
      i++;
    }
    int signE = 1;
    if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        signE = -1;
      }
      i++;
    }
    while(str[i] >= '0' && str[i] <= '9') {
      counterE = counterE * 10 + (str[i] - 48);
      i++;
    }
    returnValue = returnValue * pow(10, signE * counterE);
  return sign * returnValue;
}

long double s21_atofLong(char *str) {
  long double returnValue = 0;
  int counterE = 0;
    int sign = 1;
    int i = 0;
                if ((str[i] == 'i' || str[i] == 'I')
         && (str[i + 1] == 'n' || str[i + 1] == 'N')
         && (str[i + 2] == 'f' || str[i + 2] == 'F')) {
          returnValue = INFINITY;
         }
                if ((str[i] == 'N' || str[i] == 'n')
         && (str[i + 1] == 'a' || str[i + 1] == 'A')
         && (str[i + 2] == 'N' || str[i + 2] == 'n')) {
          returnValue = NAN;
         }
  while (s21_match("\t \n", str[i])) {
        i++;
  }
    if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        sign = -1;
      }
      i++;
    }
    while(str[i] >= '0' && str[i] <= '9') {
      returnValue = returnValue * 10 + (str[i] - 48);
      i++;
    }
    if (str[i] == '.') {
      i++;
    }
    int pow1 = 1;
    while(str[i] >= '0' && str[i] <= '9') {
      returnValue = returnValue + (str[i] - 48.0) / (10 * pow1);
      i++;
      pow1 = pow1 * 10;
    }
    if (str[i] == 'e') {
      i++;
    }
    int signE = 1;
    if (str[i] == '+' || str[i] == '-') {
      if (str[i] == '-') {
        signE = -1;
      }
      i++;
    }
    while(str[i] >= '0' && str[i] <= '9') {
      counterE = counterE * 10 + (str[i] - 48);
      i++;
    }
    returnValue = returnValue * pow(10, signE * counterE);
  return sign * returnValue;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
