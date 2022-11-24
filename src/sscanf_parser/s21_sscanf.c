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
  size_t n_counter = 0;
  int status = 0;
  int checkStartScanf = 1;
  int counterForReturn = 0;
  bool startParsing = true;
  bool stopMove = false;
  while (status != MISMADCH_ && status != ENDET_) {
    bool formatLoaded = false;
    bool inputLoaded = false;
    bool varArgLoaded = false;
    struct Specificators Specif = {-1, -1, (char)NULL, (char)NULL};
    // CURRENT FORMAT ELEMENT PARSING:
    char checkDelim = formatParsing(formatStatic, currentFormatElem, &formatLoaded, &Specif, &checkStartScanf, &status);
    if (status == MISMADCH_) {
      break; //мб тут поменять брей и все что ниже запихать под условие
    }
    // printf("\n[%s]\n", currentFormatElem);
    if (Specif.argWidth == 1) { //если  *, то ширину берем из args
      Specif.width = va_arg(args, int);
    }
   
    checkFormatError(Specif, &status);  //сочетается ли длина со спецификатором

    if (Specif.Specif == 'c' && Specif.width == -1) {
      Specif.width = 1;
    }

    ifSpecIsD(&Specif, inputStatic, &stopMove);
    ifSpecIsI(&Specif, inputStatic, &stopMove);
    ifSpecIsF(&Specif, inputStatic, &stopMove);
    ifSpecIsO(&Specif, inputStatic, &stopMove);
    ifSpecIsX(&Specif, inputStatic, &stopMove);
    ifSpecIsP(&Specif, inputStatic, &stopMove);
    
    // CURRENT INPUT ELEMENT PARSING:
    if (Specif.Specif != 'n' && !stopMove) {
    inputParsing(inputStatic, currentInputElem, Specif.width, &inputLoaded, Specif.Specif, checkDelim, &startParsing);
    
    } else {
      inputLoaded = true;
    }
    // printf("\n[%s]\n", currentInputElem);
    // CURRENT VARARG ELEMENT PARSING:
    if (!stopMove) {
    varArgParsingAndAssignment(currentFormatElem, currentInputElem,
                               &varArgLoaded, va_arg(args, void *), Specif, &n_counter, &counterForReturn);
    } else {
      va_arg(args, void *);
    }


    // -------------------------------
    if (formatLoaded == true && inputLoaded == true &&
        varArgLoaded == true) {
          counterForReturn++;
    } else {
      status = ENDET_;
    }
  }
  va_end(args);
  return counterForReturn;  // to fix, I don't know what sscanf should return and why
}

void getNextFormatElem(char *input, char elem[8192], int *checkStartScanf) {
  char *returnStr = NULL;
  static char *currentFormatString = NULL;
  char formatDelims[] = "%";
  if (*checkStartScanf) {
    currentFormatString = input;
    *checkStartScanf = 0;
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
                   bool *formatLoaded, struct Specificators *Specif, int *checkStartScanf, int *status) {

    getNextFormatElem(formatStatic, currentFormatElem, checkStartScanf);
    

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
    } else if (nextSym[0] == '%') {
     
    } else {
       *status = MISMADCH_;
    }
    
    // parsing current format element. worst case, something like this:
    // "*6hhi"
  }
  currentFormatElem++;
  return *currentFormatElem;
}

void checkFormatError(struct Specificators Specif, int *status) {
  char Sym[2];
  sprintf(Sym, "%c", Specif.Specif);
  if (Specif.length == 'l' || Specif.length == 'h') {
    if (!strpbrk(Sym, "idouxX")) {
     // *status = MISMADCH_; тут оказывается он просто игнорит, даже саму функцию наверное можно удалить просто
    }
  } else if (Specif.length == 'L') {
    if (!strpbrk(Sym, "eEfgG")) {
     // *status = MISMADCH_;
    }
  } 
}

void ifSpecIsD(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
  int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j]) && (wid > 1 || wid <= -1)) {
    j++;
    startParse++;
    wid--;
  }
  
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'd' || (*Specif).Specif == 'u') {//если у нас какое то число и нет ширины - ширина пока встречаем в строке цифры. 
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9') {
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
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
        if ((*Specif).width == startParse) {
          
          *stopMove = true;
        }
      }
    }
}

void ifSpecIsI(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 2;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j]) && (wid > 1 || wid <= -1)) {
    j++;
    startParse++;
    wid--;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'i') {
  if ((inputStatic[0] != '0' && !((inputStatic[0] == '+' || inputStatic[0] == '-'))) ||
      (inputStatic[1] != '0' && ((inputStatic[0] == '+' || inputStatic[0] == '-'))) ){ // если первое не 0 - то число десятичное
        ifSpecIsD(Specif, inputStatic, stopMove);
  } else {
    if (inputStatic[startParse - 1] == 'x') { // если второе х - то шестнадцатиричное
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
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
    } else if (inputStatic[startParse - 2] == '0') { // если первое 0, а второе не х, то восьмиричное
      startParse--;
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '7') {
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
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
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
    }
  }
}
}

void ifSpecIsF(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j]) && (wid > 1 || wid <= -1)) {
    j++;
    startParse++;
    wid--;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'f' || (*Specif).Specif == 'e' || (*Specif).Specif == 'E' || (*Specif).Specif == 'g' || (*Specif).Specif == 'G') {
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
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
        if (inputStatic[(*Specif).width] == 'e' || inputStatic[(*Specif).width] == 'E') {
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
          (*Specif).width = i;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
        
    }

}

void ifSpecIsO(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j]) && (wid > 1 || wid <= -1)) {
    j++;
    startParse++;
    wid--;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'o') {//если у нас какое то число и нет ширины - ширина пока встречаем в строке цифры. 
      if ((*Specif).width == -1) {
        (*Specif).width = startParse;
        while (inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '7') {
          (*Specif).width++;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      } else { // если задана ширина и в строке встретилось не число раньше, чем кончилась ширина, то это становится новой шириной, а не число остается в строке
        int findNotNumber = (*Specif).width;
        int i = startParse;
        while (inputStatic[i] >= '0' && inputStatic[i] <= '7' && findNotNumber > 0) {
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
    }
}

void ifSpecIsX(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j]) && (wid > 1 || wid <= -1)) {
    j++;
    startParse++;
    wid--;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'x' || (*Specif).Specif == 'X') {//если у нас какое то число и нет ширины - ширина пока встречаем в строке цифры. 
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
      } else { // если задана ширина и в строке встретилось не число раньше, чем кончилась ширина, то это становится новой шириной, а не число остается в строке
        int findNotNumber = (*Specif).width;
        int i = startParse;
        while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9')
        || (inputStatic[(*Specif).width] >= 'a' && inputStatic[(*Specif).width] <= 'f')
        || (inputStatic[(*Specif).width] >= 'A' && inputStatic[(*Specif).width] <= 'F') && findNotNumber > 0) {
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
    }
}

void ifSpecIsP(struct Specificators *Specif, char inputStatic[16384], bool *stopMove) {
  int startParse = 0;
    int j = 0;
  int wid = (*Specif).width;
  while (s21_match("\t \n", inputStatic[j]) && (wid > 1 || wid <= -1)) {
    j++;
    startParse++;
    wid--;
  }
  if (inputStatic[j] == '+' || inputStatic[j] == '-') {
    startParse++;
  }
  if ((*Specif).Specif == 'p') {//если у нас какое то число и нет ширины - ширина пока встречаем в строке цифры. 
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
      } else { // если задана ширина и в строке встретилось не число раньше, чем кончилась ширина, то это становится новой шириной, а не число остается в строке
        int findNotNumber = (*Specif).width;
        int i = startParse;
        while ((inputStatic[(*Specif).width] >= '0' && inputStatic[(*Specif).width] <= '9')
        || (inputStatic[(*Specif).width] >= 'a' && inputStatic[(*Specif).width] <= 'f')
        || (inputStatic[(*Specif).width] >= 'A' && inputStatic[(*Specif).width] <= 'F') && findNotNumber > 0) {
          findNotNumber--;
          i++;
        }
        if (findNotNumber != 0) {
          (*Specif).width = i;
        }
        if ((*Specif).width == startParse) {
          *stopMove = true;
        }
      }
    }
}

void varArgParsingAndAssignment(char currentFormatElem[8192],
                                char currentInputElem[8192], bool *varArgLoaded,
                                void *currentVarArg, struct Specificators Specif, size_t *n_counter, int *counterForReturn) {
  // here we will need to get a var arg based on currentFormatElem and set it
  // through a pointer to what we parsed from currentInputElem.
  // See formatI for a not perfect example

  // needed, cause passing static arrays too deep breaks them for some reason:
  char tempCurrentInputElem[8192] = {0};
  strcpy(tempCurrentInputElem, currentInputElem);
 
  if (Specif.Specif == 'i') {// тут вместо строки уже можно структурой пользоваться

    // [0] part is of course incorrect , properly parsed format
    // logic is needed here.
    assignI(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 's' || Specif.Specif == 'c') {
    assignS(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 'f' || Specif.Specif == 'e' || Specif.Specif == 'E' || Specif.Specif == 'g' || Specif.Specif == 'G') {
    assignF(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 'd' || Specif.Specif == 'u') {
    assignD(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 'o') {
    assignO(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 'x' || Specif.Specif == 'X') {
    assignX(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 'n') {
    assignN(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  } else if (Specif.Specif == 'p') {
    assignP(tempCurrentInputElem, varArgLoaded, currentVarArg, n_counter, counterForReturn, Specif);
  }
  
}

void assignI(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
     *n_counter = *n_counter + strlen(inCurrentInputElem);
    int checkSign = 1;
    int forNcount = 0;
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
      long int checkLoadLong = *((long int *)currentVarArg);
      short int checkLoadShort = *((short int *)currentVarArg);
      int checkLoad = *((int *)currentVarArg);
    if (inCurrentInputElem[i] == 'x') { 
      temp++;
      temp++;
      // либо свой strtol написать, либо функцию преобразования из 16й в 10ю (что наверное проще)
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * strtol(temp, NULL, 16); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * strtol(temp, NULL, 16); 
    } else {
       *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 16); 
    }
    } else if (inCurrentInputElem[i - 1] == '0') {
      temp++;
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * strtol(temp, NULL, 8); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * strtol(temp, NULL, 8); 
    } else {
       *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 8); 
    }
    } else {
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * atoi(inCurrentInputElem); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * atoi(inCurrentInputElem); 
    } else {
       *((int *)currentVarArg) = checkSign * atoi(inCurrentInputElem); 
    }

    }
    if (Specif.length == 'l') {
    if (checkLoadLong == *((long int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else if (Specif.length == 'h') {
      if (checkLoadShort == *((short int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else {
    if (checkLoad == *((int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    }

  } else {
    *varArgLoaded = false;
  }
}

void assignS(char currentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    char checkLoad[8192] = {'\0'};
    wchar_t checkLoadLong[8192] = {'\0'};
    if (Specif.length == 'l') {
      strcpy((char*)checkLoadLong, currentInputElem);//не знаю не сломает ли это преобразование что-то
    } else {
      strcpy(checkLoad, currentInputElem);
    }
    strcpy(currentVarArg, currentInputElem);
    if (Specif.length == 'l') {
    if (strcmp((char*)checkLoadLong, currentVarArg)) {
      //*varArgLoaded = false;
      *counterForReturn = *counterForReturn - 1;
    }
    } else {
      if (strcmp(checkLoad, currentVarArg)) {
      //*varArgLoaded = false;
      *counterForReturn = *counterForReturn - 1;
    }
    }
  *n_counter = *n_counter + strlen((char*)currentVarArg);

  } else {
    *varArgLoaded = false;
  }
}

void assignF(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    float checkLoad = *((float *)currentVarArg);
    long double checkLoadLong = *((long double *)currentVarArg);
    if (Specif.length == 'L') {
      *((long double *)currentVarArg) = atof(inCurrentInputElem); // тут надо сделать atold?
    } else {
      *((float *)currentVarArg) = atof(inCurrentInputElem);
    }
    if (Specif.length == 'L') {
    if (checkLoad == *((long double *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else {
    if (checkLoad == *((float *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    }
    *n_counter = *n_counter + strlen(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignD(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    //  printf("%s\n ", inCurrentInputElem);
      long int checkLoadLong = *((long int *)currentVarArg);
      short int checkLoadShort = *((short int *)currentVarArg);
      int checkLoad = *((int *)currentVarArg);
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = atoi(inCurrentInputElem); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = atoi(inCurrentInputElem); 
    } else {
       *((int *)currentVarArg) = atoi(inCurrentInputElem); 
    }
    if (Specif.length == 'l') {
    if (checkLoadLong == *((long int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else if (Specif.length == 'h') {
      if (checkLoadShort == *((short int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else {
    if (checkLoad == *((int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    }
      *n_counter = *n_counter + strlen(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void assignO(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
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
      long int checkLoadLong = *((long int *)currentVarArg);
      short int checkLoadShort = *((short int *)currentVarArg);
      int checkLoad = *((int *)currentVarArg);
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * strtol(temp, NULL, 8); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * strtol(temp, NULL, 8); 
    } else {
       *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 8); 
    }
    if (Specif.length == 'l') {
    if (checkLoadLong == *((long int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else if (Specif.length == 'h') {
      if (checkLoadShort == *((short int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else {
    if (checkLoad == *((int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignX(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
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
      long int checkLoadLong = *((long int *)currentVarArg);
      short int checkLoadShort = *((short int *)currentVarArg);
      int checkLoad = *((int *)currentVarArg);
    if (Specif.length == 'l') {
      *((long int *)currentVarArg) = checkSign * strtol(temp, NULL, 16); 
    } else if (Specif.length == 'h') {
      *((short *)currentVarArg) = checkSign * strtol(temp, NULL, 16); 
    } else {
       *((int *)currentVarArg) = checkSign * strtol(temp, NULL, 16); 
    }
if (Specif.length == 'l') {
    if (checkLoadLong == *((long int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else if (Specif.length == 'h') {
      if (checkLoadShort == *((short int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    } else {
    if (checkLoad == *((int *)currentVarArg)) {
      *counterForReturn = *counterForReturn - 1;
    }
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignN(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) {
  if (currentVarArg != NULL) {
    *varArgLoaded = true;
    int checkLoad = *((int *)currentVarArg);
    *((int *)currentVarArg) = *(int*)n_counter;
    if (checkLoad == *((int *)currentVarArg)) {
      //*varArgLoaded = false;
      *counterForReturn = *counterForReturn - 1;
    }
    int forNcount = *n_counter;
    while (forNcount != 0) {
      *n_counter = *n_counter + 1;
      forNcount = forNcount / 10;
    }
  } else {
    *varArgLoaded = false;
  }
}

void assignP(char inCurrentInputElem[8192], bool *varArgLoaded,
             void *currentVarArg, size_t *n_counter, int *counterForReturn, struct Specificators Specif) { // при отрицательных значениях какой-то не такой вывод
  if (currentVarArg != NULL) {
    char *temp = inCurrentInputElem;
    int i; 
    *varArgLoaded = true;
    long int checkLoad = *((long int *)currentVarArg);
    *((long int *)currentVarArg) = strtol(temp, NULL, 16);
    if (checkLoad == *((long int *)currentVarArg)) {
      //*varArgLoaded = false;
      *counterForReturn = *counterForReturn - 1;
    }
    *n_counter = *n_counter + strlen(inCurrentInputElem);
  } else {
    *varArgLoaded = false;
  }
}

void inputParsing(char inputFlip[16384], char currentInputElem[8192], int wid,
                  bool *inputLoaded, char Specif, char checkDelim, bool *startParsing) {
  static bool flipFlop = false;
  static char inputFlop[16384] = {0};
  fillOneByOne(inputFlip, currentInputElem, wid, Specif, checkDelim, startParsing);

  if (strcmp(currentInputElem, OUR_ERROR_) != 0) {
    *inputLoaded = true;
  }
}

void fillOneByOne(char input[16384], char currentInputElem[8192], int wid, char Specif, char checkDelim, bool *startParsing) {
  int i = 0;
  int j = 0;
  bool checkWid = false;
  if (wid <= -1) {
    checkWid = true;
    
  }
  while (input[i] != '\0' && (j < wid || checkWid)) {
    
    if (i == 0 && (!(*startParsing))) { // если s, то игнорим все делимы в начале
      while (s21_match("\t \n", input[i]) && (wid > 0 || checkWid || Specif == 'c')) {
        i++;
        wid--;
      }
    
    }
    *startParsing = false;
 
    if (s21_match("\t \n", input[i]) == false) {
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