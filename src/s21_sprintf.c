#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUR_ERROR_ "KufLv91ySdu64DYPiXOHGx5Jj9Q2eKcYwnrjxhQG"

#define MISMADCH_ 1
#define ENDET_ 2
// структура: %[flags][width][.precisions][length]type;
// flags: flag_minus - "-"; flag_plus - "+"; flag_zero - "0"; flag_space - " ";
// flag_noargument - skip the argument; flag_hash - "#"; width: (number); (-1)
// the same as *; .precisions: (.number);
// (.-1) the same as *; length: h - short int, only with i, d, o, u, x and X; l
// - long int and long char, only with i, d, o, u, x, X, c and s; L - long
// double, only with e, E, f, g and G type: c, d, i, e, E, f, g, G, o, s, u, x,
// X, p, n;
typedef struct Specificator {
  short width, precision;
  char type, length;
  bool flag_minus, flag_plus, flag_space, flag_zero, flag_noargumet, flag_hash;
} Specificator;

void formatPrint(char* buff, Specificator spec, void* currentVarArg);
Specificator parseSpecificator(char** pointerToSpec, bool* formatLoaded);
int s21_sprintf(char* buff, const char* format, ...);
void strcpy_help(char* str1, char* str2, int index);
void strcat_with_max_width(char* buff, char* src, int width);
void strchr_help(char* str1, char s);

int main() {
  char* buf = calloc(1000, sizeof(char));
  int test =
      s21_sprintf(buf, "Takaya shtuka: % +-6.2f %*d %43c %24.21s%%010d %0#f",
                  3.1415, 100, 'C', "Far");
  return 0;
}

int s21_sprintf(char* buff, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* pointerToFormatStr = calloc(strlen(format), sizeof(char));
  strcpy(pointerToFormatStr, format);
  short status = 0;
  char* pointerToSpec = strstr(pointerToFormatStr, "%");
  while (pointerToSpec != NULL) {  //заменил условие в while
    bool formatLoaded = false;
    bool outputLoaded = false;
    bool varArgLoaded = false;
    // CURRENT FORMAT ELEMENT PRINT
    // strcat(buff, pointerToFormatStr);   - вроде не нужное действие, я даю
    // тебе строку в buff на 53-54 строке
    Specificator spec = parseSpecificator(&pointerToSpec, &formatLoaded);
    printf(  //
        "flag_minus - %d\nflag_plus - %d\nflag_space - %d\nflag_zero - "
        "%d\nflag_noargument - %d\nflag_hash - %d\nwidth - "
        "%d\nprecision - %d\nlength - %c\ntype - %c\n",
        spec.flag_minus, spec.flag_plus, spec.flag_space, spec.flag_zero,
        spec.flag_noargumet, spec.flag_hash, spec.width, spec.precision, spec.length,
        spec.type);
    strcpy(buff, pointerToSpec);
    strchr_help(buff, '%');
    if (strlen(pointerToSpec) == 1 && pointerToSpec[0] == '%') {
      pointerToSpec = NULL;
    } else {
      pointerToSpec = strstr(pointerToSpec, "%");
    }
    printf("buff - |%s|\n\n", buff);
    // formatPrint(buff, spec, va_arg(args, void*));
    //  -------------------------------
    if (formatLoaded == false &&
        outputLoaded == false &&  // это пока не использую
        varArgLoaded == false) {  //
      status = ENDET_;            //
    } else if (formatLoaded + outputLoaded + varArgLoaded > 0 &&  //
               formatLoaded + outputLoaded + varArgLoaded < 3) {  //
      status = MISMADCH_;                                         //
    }                                                             //
  }
  free(pointerToFormatStr);
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
    strcat(buff, " ");
    length++;
  }
  strcat(buff, src);
}

Specificator parseSpecificator(char** pointerToSpec, bool* formatLoaded) {
  Specificator spec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char allspec[] = "cdieEfgGosuxXpn";
  char allnumb[] = "1234567890";
  char alllength[] = "Llh";
  char* width_temp = calloc(strlen(*pointerToSpec), sizeof(char));
  int count = 0;
  char* str = *pointerToSpec;
  if (strcmp(str, OUR_ERROR_) != 0) {
    size_t i = 0;
    for (; i < strlen(str);) {
      if (strchr("-", str[i]) != NULL) {
        spec.flag_minus = 1;
        i++;
      } else if (str[i] == '+') {
        spec.flag_plus = 1;
        spec.flag_space = 0;
        i++;
      } else if (str[i] == ' ' && !spec.flag_plus) {
        spec.flag_space = 1;
        i++;
      } else if (str[i] == '0' && spec.width == 0) {
        spec.flag_zero = 1;
        i++;
      } else if (str[i] == '#') {
        spec.flag_hash = 1;
        i++;
      } else if (strchr(allnumb, str[i])) {
        strcpy_help(width_temp, str, i);
        while (strchr(allnumb, width_temp[count]) && width_temp[count] != '.') {
          count++;
        }
        width_temp[count] = '\0';
        spec.width = atoi(width_temp);
        i += strlen(width_temp);
      } else if (str[i] == '*') {
        spec.width = -1;
        i++;
      } else if (str[i] == '.') {
        strcpy_help(width_temp, str, i + 1);
        count = 0;
        while (strchr(allnumb, width_temp[count])) {
          count++;
        }
        if (width_temp[0] == '*') {
          spec.precision = -1;
          i += 2;
        } else {
          width_temp[count] = '\0';
          spec.precision = atoi(width_temp);
          i += strlen(width_temp) + 1;
        }
      } else if (strchr(alllength, str[i])) {
        spec.length = str[i];
        i++;
      } else if (strchr(allspec, str[i])) {
        spec.type = str[i];
        i++;
        break;
      } else if (str[i] == '%' && strlen(str) > i + 1 && str[i + 1] == '%') {
        i++;
        break;
      } else {
        i++;
      }
    }
    if (spec.type == 0) {
      spec.flag_noargumet = 1;
    }

    *pointerToSpec += i;
  }

  return spec;
}

void strcpy_help(
    char* str1, char* str2,
    int index) {  // копирует str2 начиная с некоторого индекса в str1
  size_t i = 0;
  for (; i < strlen(str2); i++) {
    if (index <= i) {
      str1[i - index] = str2[i];
    }
  }
  str1[i - index + 1] = '\0';
}

void strchr_help(char* str1, char s) {  //если находит символ s в строке str1,
                                        //то ставить \0 на место символа s
  size_t i = 0;
  for (; i < strlen(str1); i++) {
    if (str1[i] == s) {
      str1[i] = '\0';
    }
  }
}
