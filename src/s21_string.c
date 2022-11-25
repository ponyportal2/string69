#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

#include "s21_strerror_codes.h"

size_t s21_strlen(const char *str) {
  size_t len = 0;
  while (*str != '\0') {
    str++;
    len++;
  }
  return (size_t)len;
}

char *s21_strstr(char *str1, char *str2) {
  size_t i = 0, j = 0;
  char *a = NULL;
  if (str1[0] == '\0' && str2[0] != '\0') {
    a = NULL;
  } else if (str1[0] == '\0' && str2[0] == '\0') {
    a = "";
  } else {
    while (str1[i] != '\0' && a == NULL) {
      if (str1[i] == str2[j]) {
        j++;
      } else {
        j = 0;
      }
      if (str2[j] == '\0') {
        if (j == s21_strlen(str2) && j != 0) {
          a = str1 + i - j + 1;
        } else if (j == s21_strlen(str2) && j == 0) {
          a = str1;
        }
      }
      i++;
    }
  }
  return a;
}

void *s21_memchr(const void *arr, int c, size_t n) {
  void *sym = NULL;
  void *tmp = (void *)arr;
  if (n > 0) {
    while ((*((int*)tmp) != c && *((unsigned char*)tmp) != c) && n > 1) {
      n--;
      tmp++;
    }
    if (*((int*)tmp) == c) {
      sym = tmp;
    } else if (*((unsigned char*)tmp) == c) {
      sym = tmp;
    }
  }
  return sym;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  int result = 0;
  char *tmp1 = (char *)str1;
  char *tmp2 = (char *)str2;
  while (n > 0) {
    result = *(char *)tmp1 - *(char *)tmp2;
    if (result != 0) {
      n = 0;
    } else {
      tmp1++;
      tmp2++;
      n--;
    }
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
  char *tmp = dest;
  const char *s = src;
  while (n > 0) {
    *tmp = *s;
    tmp++;
    s++;
    n--;
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, size_t n) {
  char *tmp = dest;
  const char *s = src;
  char move[n];
  for (size_t i = 0; i < n; i++) {
    move[i] = *s;
    s++;
  }
  for (size_t i = 0; i < n; i++) {
    *tmp = move[i];
    tmp++;
  }
  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  for (size_t i = 0; i < n; i++) {
    *tmp = c;
    tmp++;
  }
  if (n == 0) {
    
  }
  return str;
}

char *s21_strchr(const char *str, int c) {
  char *sym = NULL;
  int check = 1;
  while (*str && check) {
    if (*str == c) {
      sym = (char *)str;
      check = 0;
    }
    str++;
  }
  if (c == '\0') {
    sym = "";
  }
  return sym;
}

int s21_strcmp(const char *str1, const char *str2) {
  int check = 1, result = 0;
  while (*str1 && *str2 && check) {
    if (*str1 - *str2 != 0) {
      result = *str1 - *str2;
      check = 0;
    } else {
      str1++;
      str2++;
    }
  }
  if (!*str1 && !*str2) {
    result = 0;
  } else if (!*str2) {
    result = *str1;
  } else if (!*str1) {
    result = -*str2;
  }

  return result;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int check = 1, result = 0;
  while (*str1 && *str2 && check && n) {
    if (*str1 - *str2 != 0) {
      result = *str1 - *str2;
      check = 0;
    } else {
      str1++;
      str2++;
      n--;
    }
  }
  if (!*str1 && !*str2 && n) {
    result = 0;
  } else if (!*str2 && n) {
    result = *str1;
  } else if (!*str1 && n) {
    result = -*str2;
  }

  return result;
}

//вспомогающая функция для s21_strspn, чтобы не копировать код, такие же
//использую и для других функций:
size_t s21_strspn_helper(const char *stringOne, const char *stringTwo,
                         bool isCspn) {
  int i = 0;
  size_t returnValue = 0;
  bool whileBreak = false;
  bool check = false;

  while (stringOne[i] != '\0' && whileBreak != true) {
    if ((check = s21_match(stringTwo, stringOne[i])) == isCspn) {
      whileBreak = true;
      returnValue = i;
    }
    i++;
    if (stringOne[i] == '\0' && check == false && isCspn == true) {
      returnValue = i;
    }
  }
  if (stringOne[i] == '\0' && check == true && isCspn == false) {
    returnValue = i;
  }
  return (size_t)returnValue;
}

// проверяет есть ли символ inputChar в массиве inputCharArr:
bool s21_match(const char *inputCharArr, char inputChar) {
  int match = false;
  int i = 0;
  while (inputCharArr[i] != '\0') {
    if (inputCharArr[i] == inputChar) {
      match = true;
    }
    i++;
  }
  return match;
}

size_t s21_strspn(const char *stringOne, const char *stringTwo) {
  return s21_strspn_helper(stringOne, stringTwo, false);
}

size_t s21_strcspn(const char *stringOne, const char *stringTwo) {
  return s21_strspn_helper(stringOne, stringTwo, true);
}

char *s21_strrchr(const char *str, int c) {
  bool whileBreak = false;
  char *returnValue = NULL;
  long long int i = s21_strlen(str) - 1;
  if (c == '\0') {
    returnValue = "";
  }
  while (i >= 0 && whileBreak != true) {
    if (str[i] == c) {
      returnValue = (char *)str + i;
      whileBreak = true;
    }
    i--;
  }
  return returnValue;
}

char *s21_strcpy(char *dest, const char *src) { // sharkmer
  return s21_strcpy_helper(dest, src, 0, false);
}

char *s21_strncpy(char *dest, const char *src, size_t n) { // sharkmer
  return s21_strcpy_helper(dest, src, n, true);
}

char *s21_strcpy_helper(char *dest, const char *src, size_t n,
                        bool isNcopy) { // sharkmer
  int i = 0;
  size_t counter = 0;
  if (isNcopy == true) {
    while (src[i] != '\0' && counter < n) {
      dest[i] = src[i];
      counter++;
      i++;
    }
    while (counter < n) {
      dest[i] ='\0';
      counter++;
      i++;
    }
  } else {
    while (src[i] != '\0') {
      dest[i] = src[i];
      i++;
    }
    dest[i] = '\0';
  }
  return (char *)dest;
}

char *s21_strcat(char *dest, const char *src) {
  return s21_strcat_helper(dest, src, 0, false);
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  return s21_strcat_helper(dest, src, n, 1);
}

char *s21_strcat_helper(char *dest, const char *src, size_t n, bool isNcat) {
  size_t destLen = s21_strlen(dest);
  int i = 0;
  size_t counter = 0;
  if (isNcat == 1) { // strncat
    while (src[i] != '\0' && counter < n) {
      dest[destLen + i] = src[i];
      counter++;
      i++;
    }
  } else { // strcat
    while (src[i] != '\0') {
      dest[destLen + i] = src[i];
      i++;
    }
  }
  dest[destLen + i] = '\0';
  return (char *)dest;
}

char *s21_strtok(char *str, const char *delim) {
  static char *new_str;
  char *tmp = str;
  int check = 1;
  if (str != NULL) {
    new_str = str;
  } else if (!new_str) { //если строка закончилась, возвращаем 0
    tmp = 0;
    check = 0;
  }
  if (check != 0) {
    size_t check1 = s21_strspn(new_str, delim); // есть ли сейчас разделитель

    str = new_str + check1; // перепрыгиваем разделитель
    tmp = new_str + check1;
    size_t check2 = s21_strcspn(str, delim); // длина до следующего разделителя
    new_str = str + check2; // перепрыгиваем до следующего разделителя
    if (new_str == str) { // для случая когда стартовая строка пустая
      tmp = 0;
      new_str = 0;
    } else {
      if (*new_str != 0) { // зануляем разделитель
        *new_str = 0;
        new_str++;
      } else {
        new_str = NULL; // если строка закончилась то NULL
      }
    }
  }
  return tmp; // возвращаем строку до зануленного разделителя
}

char *s21_strpbrk(const char *str, const char *sym) {
  char *temp;
  size_t check = s21_strcspn(str, sym);
  if (check == s21_strlen(str)) {
    temp = NULL;
  } else {
    temp = (char *)str + check;
  }
  return temp;
}

char *s21_strerror(int errcode) { // надо в мейк добавить $(SYSFLAG)
  (void)errcode;
  char *error = NULL;
#ifdef APPLE
  int max = 106;
  static char unknown[50] = "Unknown error: ";
#endif
#ifdef LINUX
  int max = 133;
  static char unknown[50] = "Unknown error ";
#endif
#if defined(LINUX) || defined(APPLE)
  if (errcode >= 0 && errcode <= max) {
#ifdef APPLE
    error = ErrorNames[errcode];
#else
    error = ErrorNamesLinux[errcode];
#endif
  } else {
    char num_error[20];
    sprintf(num_error, "%d", errcode); // поменять на свой
    size_t i = s21_strlen(unknown);
    while (unknown[i] != ' ') {
      unknown[i] = '\0';
      i--;
    }
    s21_strcat(unknown, num_error);
    error = unknown;
  }
#endif
  return error;
}

/* KERENHOR
// char *s21_strcpy(char *dest, const char *src) { // kerenhor
//   char *tmp = dest;
//   while (*src != '\0') {
//     tmp = (char *)src;
//     tmp++;
//     src++;
//   }
//   if (*tmp != '\0') {
//     tmp++;
//     *tmp = '\0';
//   }
//   return tmp;
// }

// char *s21_strcat(char *str1, const char *str2) { // kerenhor
//   char *tmp1 = str1;
//   const char *tmp2 = str2;
//   while (*tmp1 != '\0') {
//     tmp1++;
//   }
//   while (*tmp2 != '\0') {
//     *tmp1 = *tmp2;
//     tmp1++;
//     tmp2++;
//   }
//   if (*tmp1 != '\0') {
//     tmp1++;
//     *tmp1 = '\0';
//   }
//   return tmp1;
// }

// char *s21_strncat(char *str1, const char *str2, size_t n) { // kerenhor
//   char *tmp1 = str1;
//   const char *tmp2 = str2;
//   while (*tmp1 != '\0') {
//     tmp1++;
//   }
//   while (*tmp2 != '\0' && n) {
//     *tmp1 = *tmp2;
//     tmp1++;
//     tmp2++;
//     n--;
//   }
//   if (*tmp1 != '\0') {
//     tmp1++;
//     *tmp1 = '\0';
//   }
//   return tmp1;
// }
*/

/* SHARKMER:
char* s21_strchr(const char* str, int c) {
  bool whileBreak = false;
  char* returnValue = NULL;
  int i = 0;
  while (str[i] != '\0' || whileBreak == true) {
    if (str[i] == c) {
      returnValue = (char*)str + i;
    }
    i++;
  }
  return returnValue;
}

size_t s21_strlen(const char* str) {
  size_t i = 0;
  while (str[i] != '\0') {
    i++;
  }
  return (size_t)i;
}
*/

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// duffmank
// Part 5 Специальные функции обработки строк (вдохновленные классом String в
// языке C#)
void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *temp = NULL;
  if (start_index < s21_strlen(src)) {
    size_t size = 1;
    temp = malloc(sizeof(char) * (s21_strlen(src) + 2 + s21_strlen(str)));
    for (size_t i = 0; i < start_index; i++) {
      temp[i] = src[i];
    }
    for (size_t i = start_index; (i - start_index) < s21_strlen(str); i++) {
      temp[i] = str[i - start_index];
    }
    for (size = start_index + s21_strlen(str); size <= (s21_strlen(src) + s21_strlen(str));
         size++) {
      temp[size] = src[size - s21_strlen(str)];
    }
    temp[size] = '\0';
  }
  return temp;
}

void *s21_to_upper(const char *str) {
  char *temp = NULL;
  if (str != NULL) {
    temp = malloc(sizeof(char) * (s21_strlen(str) + 1));
    size_t i = 0;
    for (i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        temp[i] = str[i] - 32;
      } else {
        temp[i] = str[i];
      }
    }
    temp[i]='\0';
  }
  return temp;
}

void *s21_to_lower(const char *str) {
  char *temp = NULL;
  if (str != NULL) {
    temp = malloc(sizeof(char) * (s21_strlen(str) + 1));
    size_t i = 0;
    for (i = 0; i < s21_strlen(str); i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        temp[i] = str[i] + 32;
      } else {
        temp[i] = str[i];
      }
    }
    temp[i]='\0';
  }
  return temp;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *temp = NULL;
  if (src != NULL && trim_chars != NULL) {
    size_t counts = 0;
    size_t counte = 0;
    for (size_t i = 0; i < s21_strlen(src); i++) {
      for (size_t j = 0; j < s21_strlen(trim_chars); j++) {
        if (src[i] == trim_chars[j]) {
          counts++;
          break;
        }
      }
      if (counts - 1 != i) {
        break;
      }
    }
    for (size_t i = s21_strlen(src) - 1; i > counts; i--) {
      for (size_t j = 0; j < s21_strlen(trim_chars); j++) {
        if (src[i] == trim_chars[j]) {
          counte++;
          break;
        }
      }
      if (counte != s21_strlen(src) - i) {
        break;
      }
    }
    if (counts + counte <= s21_strlen(src) && (counts + counte) != 0) {
      temp = malloc(sizeof(char) * (s21_strlen(src) - counts - counte+1));
      size_t i = 0;
      for (i = counts; i < s21_strlen(src) - counte; i++) {
        temp[i - counts] = src[i];
      }
      temp[i - counts] = '\0';
    }
  }
  return temp;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
