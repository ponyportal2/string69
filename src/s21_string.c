#include "s21_string.h"

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
  while (str1[i] != '\0' && a == NULL) {
    if (str1[i] == str2[j]) {
      j++;
    } else {
      j = 0;
    }
    if (str2[j] == '\0') {
      if (j == s21_strlen(str2)) {
        a = str1 + i - j + 1;
      }
    }
    i++;
  }
  return a;
}

void *s21_memchr(const void *arr, int c, size_t n) {
  unsigned char *sym = NULL;
  unsigned char *tmp = (unsigned char *)arr;
  while (*tmp != c && n > 1) {
    n--;
    tmp++;
  }
  if (*tmp == c) {
    sym = tmp;
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
  return result;
}

//вспомогающая функция для s21_strspn, чтобы не копировать код, такие же
//использую и для других функций:
size_t s21_strspn_helper(const char *stringOne, const char *stringTwo,
                         bool isCspn) {
  int i = 0;
  int returnValue = 0;
  bool whileBreak = false;
  while (stringTwo[i] != '\0' && whileBreak != true) {
    if (s21_match(stringTwo, stringOne[i]) == isCspn) {
      whileBreak = true;
      returnValue = i;
    }
    i++;
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
  int i = s21_strlen(str) - 1;
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
  int destLen = s21_strlen(dest - 1);
  int i = 0;
  size_t counter = 0;
  if (isNcopy == true) {
    while (src[i] != '\0' && counter < n) {
      dest[i] = src[i];
      counter++;
      i++;
    }
  } else {
    while (src[i] != '\0') {
      dest[i] = src[i];
      i++;
    }
  }
  dest[i] = '\0';
  return (char *)dest + destLen;
}

char *s21_strcat(char *dest, const char *src) {
  return s21_strcat_helper(dest, src, 0, false);
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  return s21_strcat_helper(dest, src, n, 1);
}

char *s21_strcat_helper(char *dest, const char *src, size_t n, bool isNcat) {
  int destLen = s21_strlen(dest);
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

// char *s21_strcpy(char *dest, const char *src) { // karnhor
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

// char *s21_strcat(char *str1, const char *str2) { // karnhor
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

// char *s21_strncat(char *str1, const char *str2, size_t n) { // karnhor
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