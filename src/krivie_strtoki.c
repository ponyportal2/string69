#include <stdio.h>
#include <string.h>

char *s21_strtok(char *str1, const char *str2) {
  int i = 0, j = 0;
  static char a[50];
  while (str1[i] != '\0') {
    if (str1[i] == str2[j]) {
      break;
    }
    a[i] = str1[i];
    i++;
  }
  return (char *)a;
}

int main() {
  char test10[20] = {"/"};
  char test12[20] = {"acs/vgh/asd/jyg"};
  // char test13[20] = {"."};
  // char test14[20] = {"Zav.Kaj.Masjyg.Los"};
  // char test15[20] = {"abcdefghj"};
  // char test9[20] = {""};
  printf("%s", s21_strtok(test12, test10));
  printf("%s", s21_strtok(NULL, test10));
  return 0;
}
