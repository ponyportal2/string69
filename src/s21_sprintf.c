#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200
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

int s21_sprintf(char* buff, const char* format, ...);
void formatPrint(char* buff, Specificator spec, va_list args);
Specificator parseSpecificator(char** pointerToSpec, bool* formatLoaded);
void strcpy_help(char* str1, char* str2, int index);
void strcat_with_spec(char* buff, char* src, Specificator spec);
void itoa(long long num, char* src, int radix);
void reverse(char* string);
void trimDouble(double inputDouble, int ndigit, char* buf);
void strcpy_help(char* str1, char* str2, int index);
void strchr_help(char* str1, char s);
bool is_digit(char type);

int main() {
  char* buf = calloc(1000, sizeof(char));
  int test = s21_sprintf(buf, "Takaya shtuka: %f gj", 300.005);
  return 0;
}

int s21_sprintf(char* buff, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* pointerToSpec = NULL;
  strcpy(buff, format);
  strchr_help(buff, '%');
  pointerToSpec = strstr(format, "%");
  while (pointerToSpec) {
    bool formatLoaded = false;
    // CURRENT FORMAT ELEMENT PRINT
    Specificator spec = parseSpecificator(&pointerToSpec, &formatLoaded);
    formatPrint(buff, spec, args);
    strcat(buff, pointerToSpec);
    strchr_help(buff, '%');
    if (strlen(pointerToSpec) == 1 && pointerToSpec[0] == '%') {
      pointerToSpec = NULL;
    } else {
      pointerToSpec = strstr(pointerToSpec, "%");
    }
    printf("buff - |%s|\n\n", buff);
  }
  va_end(args);
}

void formatPrint(char* buff, Specificator spec, va_list args) {
  char src[MAXLINE];
  switch (spec.type) {
    case 'c':
      src[0] = va_arg(args, int);
      src[1] = '\0';
      break;
    case 'i':
    case 'd':
      itoa((long long)va_arg(args, int), src, 10);
      break;
    case 'u':
      itoa((long long)va_arg(args, unsigned int), src, 10);
      break;
    case 'f':
      trimDouble(va_arg(args, double), spec.precision, src);
      break;
  }
  spec.type == 's' ? strcat_with_spec(buff, va_arg(args, char*), spec)
                   : strcat_with_spec(buff, src, spec);
}

void strcat_with_spec(char* buff, char* src, Specificator spec) {
  int length = strlen(src);
  char* temp = malloc(length * 2);
  if {is_digit(spec.type) && src[0] != '-') {
      if (spec.flag_space && !spec.flag_plus) {
        strcpy(temp, " ");
        strcat(temp, src);
        length++;
      }
      if (spec.flag_plus) {
        strcpy(temp, "+");
        strcat(temp, src);
        length++;
      }
    }
    if (spec.flag_minus) strcat(buff, temp);
    while (spec.width - length > 0) {
      strcat(buff, " ");
      length++;
    }
    if (!spec.flag_minus) strcat(buff, temp);
    strcat(buff, temp);
    free(temp);
  }

  bool is_digit(char type) {
    bool digit = false;
    if (type == 'd' || type == 'i' || type == 'e' || type == 'E' ||
        type == 'f' || type == 'g' || type == 'G' || type == 'o' ||
        type == 'x' || type == 'X' || type == 'u')
      digit = true;
    return digit;
  }

  void itoa(long long num, char* src, int radix) {
    int i = 0, j = 0;
    int digit;
    if (num < 0) {
      src[0] = '-';
      j++;
    }
    while (num >= pow(radix, i)) {
      digit = (int)(num / pow(radix, i)) % radix;
      src[i++] = (char)(digit + 48);
    }
    src[i] = '\0';
    reverse(src);
  }

  void reverse(char* string) {
    char temp[MAXLINE];
    strcpy(temp, string);
    int length = strlen(string);
    int i;
    for (i = 0; i < length; i++) string[i] = temp[length - i - 1];
    string[i] = '\0';
  }

  void trimDouble(double inputDouble, int ndigit, char* buf) {
    char rightPartStr[1024] = {0};
    char leftPartStr[1024] = {0};
    double leftPartDouble;
    double rightPart = modf(inputDouble, &leftPartDouble);

    if (ndigit == -1) {
      ndigit = 1;
      double tmp = rightPart;
      double fck;
      while (!(tmp == 0 || tmp >= 0.999999999)) {
        tmp = modf(10 * tmp, &fck);
        ndigit++;
      }
    }

    gcvt(rightPart, ndigit, rightPartStr);  // rewrite

    itoa((long long)leftPartDouble, leftPartStr, 10);
    int lIdx = strlen(leftPartStr) + 1;
    int rIdx = 2;

    if (rightPartStr[rIdx] != '\0') {
      leftPartStr[strlen(leftPartStr)] = '.';
      while (rightPartStr[rIdx] != '\0') {
        leftPartStr[lIdx] = rightPartStr[rIdx];
        lIdx++;
        rIdx++;
      }
    }
    strcpy(buf, leftPartStr);
  }

  unsigned long long hexToBaseTen(char* hexVal) {
    unsigned long long returnValue = 0;
    int hexLen = strlen(hexVal);
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
        // error can be added here for else
      } else if (hexVal[i] == ' ') {  // любые делиметры можно добавить сюда
        // do nothing
      } else {
        // error can be added here
      }
    }
    if (isNegative) returnValue = returnValue * -1;
    return returnValue;
  }

  unsigned long long octToBaseTen(char* octVal) {
    unsigned long long returnValue = 0;
    int octLen = strlen(octVal);
    bool numbersStarted = false;
    bool isNegative = false;
    for (int i = 0; i < octLen; i++) {
      if (octVal[i] >= '0' && octVal[i] <= '7') {
        returnValue = returnValue + (octVal[i] - '0') * pow(8, octLen - i - 1);
        numbersStarted = true;
      } else if (octVal[i] == '-') {
        if (numbersStarted == false) isNegative = true;
        // error can be added here for else
      } else if (octVal[i] == ' ') {  // любые делиметры можно добавить сюда
        // do nothing
      } else {
        // error can be added here
      }
    }
    if (isNegative) returnValue = returnValue * -1;
    return returnValue;
  }

  Specificator parseSpecificator(char** pointerToSpec, bool* formatLoaded) {
    Specificator spec = {0, -1, 0, 0, 0, 0, 0, 0, 0, 0};
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
          while (strchr(allnumb, width_temp[count]) &&
                 width_temp[count] != '.') {
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