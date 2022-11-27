#include "s21_sprintf.h"

int main() {
  char* buf = calloc(1000, sizeof(char));
  int test = s21_sprintf(buf, "Takaya shtuka: %+i gj %20f %s\n", 300,
                         9999999.08, "zepi");
  printf("Takaya shtuka: %+i gj %20f %s\n", 300, 9999999.08, "zepi");
  printf("buff - |%s|\n\n", buf);
  return 0;
}

int s21_sprintf(char* buff, const char* format, ...) {
  va_list args;
  va_start(args, format);
  char* pointerToSpec = NULL;
  s21_strcpy(buff, format);
  strchr_help(buff, '%');
  pointerToSpec = s21_strstr((char*)format, "%");
  while (pointerToSpec) {
    bool formatLoaded = false;
    // CURRENT FORMAT ELEMENT PRINT
    Specificator spec = parseSpecificator(&pointerToSpec, &formatLoaded);
    formatPrint(buff, spec, args);
    s21_strcat(buff, pointerToSpec);
    strchr_help(buff, '%');
    if (s21_strlen(pointerToSpec) == 1 && pointerToSpec[0] == '%') {
      pointerToSpec = NULL;
    } else {
      pointerToSpec = s21_strstr(pointerToSpec, "%");
    }
  }
  va_end(args);
}

void formatPrint(char* buff, Specificator spec, va_list args) {
  char src[MAXLINE];
  long long num;
  long double floatNum;
  switch (spec.type) {
    case 'c':
      src[0] = va_arg(args, int);
      src[1] = '\0';
      break;
    case 'i':
    case 'd':
    case 'u':
      if (spec.type == 'u')
        num = spec.length == 'l' ? va_arg(args, unsigned long)
                                 : va_arg(args, unsigned int);
      else
        num = spec.length == 'l' ? va_arg(args, long) : va_arg(args, int);
      itoa(num, src, 10);
      break;
    case 'f':
      floatNum =
          spec.length == 'L' ? va_arg(args, long double) : va_arg(args, double);
      trimDouble(floatNum, spec.precision, src);
      break;
  }
  spec.type == 's' ? strcat_with_spec(buff, va_arg(args, char*), spec)
                   : strcat_with_spec(buff, src, spec);
}

void strcat_with_spec(char* buff, char* src, Specificator spec) {
  int length = s21_strlen(src);
  char* temp = malloc(length * 2);
  if (is_digit(spec.type) && src[0] != '-') {
    if (spec.flag_space && !spec.flag_plus) {
      s21_strcpy(temp, " ");
      s21_strcat(temp, src);
      length++;
    } else if (spec.flag_plus) {
      s21_strcpy(temp, "+");
      s21_strcat(temp, src);
      length++;
    } else {
      s21_strcpy(temp, src);
    }
  } else {
    s21_strcpy(temp, src);
  }
  if (spec.flag_minus) s21_strcat(buff, temp);
  while (spec.width - length > 0) {
    s21_strcat(buff, " ");
    length++;
  }
  if (!spec.flag_minus) s21_strcat(buff, temp);
  free(temp);
}

bool is_digit(char type) {
  bool digit = false;
  if (type == 'd' || type == 'i' || type == 'e' || type == 'E' || type == 'f' ||
      type == 'g' || type == 'G' || type == 'o' || type == 'x' || type == 'X' ||
      type == 'u')
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
    src[i++] =
        (digit >= 0 && digit <= 9) ? (char)(digit + 48) : (char)(digit + 65);
  }
  src[i] = '\0';
  reverse(src);
}

void reverse(char* string) {
  char temp[MAXLINE];
  s21_strcpy(temp, string);
  int length = s21_strlen(string);
  int i;
  for (i = 0; i < length; i++) string[i] = temp[length - i - 1];
  string[i] = '\0';
}

void trimDouble(double inputDouble, int ndigit, char* buf) {
  char rightPartStr[1024] = {0};
  char leftPartStr[1024] = {0};
  double leftPartDouble;
  double rightPart = modf(inputDouble, &leftPartDouble);

  ourGcvt((long double)rightPart, ndigit, rightPartStr, 10);  // rewrite

  itoa((long long)leftPartDouble, leftPartStr, 10);
  int lIdx = s21_strlen(leftPartStr) + 1;
  int rIdx = 2;

  if (rightPartStr[rIdx] != '\0') {
    leftPartStr[s21_strlen(leftPartStr)] = '.';
    while (rightPartStr[rIdx] != '\0') {
      leftPartStr[lIdx] = rightPartStr[rIdx];
      lIdx++;
      rIdx++;
    }
  }
  s21_strcpy(buf, leftPartStr);
}

void ourGcvt(long double value, int ndigit, char* buf, int radix) {
  long double localValue = value;
  bool isNegative = false;
  if (value < 0) {
    isNegative = true;
    localValue = localValue * -1;
  }
  long long leftPartInt = localValue;
  char* leftPartStr = calloc(1024, sizeof(char));
  long double leftPartDouble = leftPartInt;
  long double rightPartDouble = localValue - leftPartDouble;
  bool firstOneAdded = false;
  char* finalStr = calloc(1024, sizeof(char));
  if (leftPartInt != 0) {
    itoa(leftPartInt, leftPartStr, radix);
  } else {
    leftPartStr[0] = '0';
  }
  if ((rightPartDouble - 0.1) < 0) {
    rightPartDouble += 0.1;
    firstOneAdded = true;
  } else {
    // do nothing
  }
  char leftPartChunk[1024] = {0};
  char finalRightPart[1024] = {0};
  bool whileBreak = false;
  int rightPartIntTemp = 0;
  int i = 0;
  while (i < 15 && whileBreak == false) {
    rightPartDouble = rightPartDouble - (long double)rightPartIntTemp;
    rightPartDouble = rightPartDouble * 10;
    rightPartIntTemp = rightPartDouble;
    itoa(rightPartIntTemp, leftPartChunk, 10);
    if (s21_strcmp(leftPartChunk, "") == 0) {
      s21_strcat(finalRightPart, "0");
      // whileBreak = true;
      // printf("[%i]", i);
    } else {
      s21_strcat(finalRightPart, leftPartChunk);
    }
    i++;
  }
  if (firstOneAdded) finalRightPart[0] = '0';
  finalRightPart[ndigit] = '\0';
  if (isNegative) {
    if (zeroOs(leftPartStr) && zeroOs(finalRightPart)) {
      // do nothing
    } else {
      s21_strcat(finalStr, "-");
    }
  }
  s21_strcat(finalStr, leftPartStr);
  if (ndigit != 0) s21_strcat(finalStr, ".");
  s21_strcat(finalStr, finalRightPart);
  s21_strcpy(buf, finalStr);
  free(leftPartStr);
  free(finalStr);
}

int zeroOs(char* str) {
  int result = 1;
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] != '0') {
      result = 0;
      break;
    }
    i++;
  }
  return result;
}

Specificator parseSpecificator(char** pointerToSpec, bool* formatLoaded) {
  Specificator spec = {0, 6, 0, 0, 0, 0, 0, 0, 0, 0};
  char allspec[] = "cdieEfgGosuxXpn";
  char allnumb[] = "1234567890";
  char alllength[] = "Llh";
  char* width_temp = calloc(s21_strlen(*pointerToSpec), sizeof(char));
  int count = 0;
  char* str = *pointerToSpec;
  if (s21_strcmp(str, OUR_ERROR_) != 0) {
    size_t i = 0;
    for (; i < s21_strlen(str);) {
      if (s21_strchr("-", str[i]) != NULL) {
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
      } else if (s21_strchr(allnumb, str[i])) {
        strcpy_help(width_temp, str, i);
        while (s21_strchr(allnumb, width_temp[count]) &&
               width_temp[count] != '.') {
          count++;
        }
        width_temp[count] = '\0';
        spec.width = atoi(width_temp);
        i += s21_strlen(width_temp);
      } else if (str[i] == '*') {
        spec.width = -1;
        i++;
      } else if (str[i] == '.') {
        strcpy_help(width_temp, str, i + 1);
        count = 0;
        while (s21_strchr(allnumb, width_temp[count])) {
          count++;
        }
        if (width_temp[0] == '*') {
          spec.precision = -1;
          i += 2;
        } else {
          width_temp[count] = '\0';
          spec.precision = atoi(width_temp);
          i += s21_strlen(width_temp) + 1;
        }
      } else if (s21_strchr(alllength, str[i])) {
        spec.length = str[i];
        i++;
      } else if (s21_strchr(allspec, str[i])) {
        spec.type = str[i];
        i++;
        break;
      } else if (str[i] == '%' && s21_strlen(str) > i + 1 &&
                 str[i + 1] == '%') {
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
  for (; i < s21_strlen(str2); i++) {
    if (index <= i) {
      str1[i - index] = str2[i];
    }
  }
  str1[i - index + 1] = '\0';
}

void strchr_help(char* str1, char s) {  //если находит символ s в строке str1,
                                        //то ставить \0 на место символа s
  size_t i = 0;
  for (; i < s21_strlen(str1); i++) {
    if (str1[i] == s) {
      str1[i] = '\0';
    }
  }
}