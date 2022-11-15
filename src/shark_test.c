#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  // s21_strcat_helper("booba", "biba", 1, 1);
  // ----------
  // S21_STRCHR
  // ----------
  // for (int i = 0; i < argc; i++) {
  //   // char *love = NULL;
  //   // love = calloc(100, sizeof(char));
  //   // love = "abiba";
  //   char love[1024] = "aboba";
  //   if (s21_strchr(argv[i], 'a') != NULL) {
  //     printf("yes\n");
  //     s21_strcpy(love, s21_strchr(argv[i], 'a'));
  //     printf("[%c]", love[0]);
  //     printf("[%s]\n", love);
  //     s21_strcpy(love, strchr(argv[i], 'a'));
  //     printf("[%c]", love[0]);
  //     printf("[%s]\n", love);
  //   } else {
  //     printf("no\n");
  //   }
  // }
  // ----------
  // S21_STRCPY
  // ----------
  // char temp[1024] = {0};
  // char temp2[1024] = {0};
  // strcpy(temp, argv[1]);
  // if (argc == 3) {
  //   printf("[%s]", s21_strcpy(temp, argv[2]));
  //   printf("[%s]", strcpy(temp2, argv[2]));
  // }
  // return 0;
  // ----------
  // S21_STRNCPY
  // ----------
  // char temp[1024] = {0};
  // char temp2[1024] = {0};
  // strcpy(temp, argv[1]);
  // if (argc == 3) {
  //   printf("[%s]", s21_strncpy(temp, argv[2], 3));
  //   printf("[%s]", strncpy(temp2, argv[2], 3));
  // }
  // return 0;
  // ----------
  // S21_STRCAT
  // ----------
  // char temp[1024] = {0};
  // char temp2[1024] = {0};
  // for (int i = 0; i < argc; i++) {
  //   printf("s21:[%s]\n", s21_strcat(temp, argv[i]));
  //   printf("c:[%s]\n", strcat(temp2, argv[i]));
  // }
  // return 0;
  // ----------
  // S21_STRNCAT
  // ----------
  // char temp[1024] = {0};
  // char temp2[1024] = {0};
  // for (int i = 0; i < argc; i++) {
  //   printf("s21:[%s]\n", s21_strncat(temp, argv[i], 5));
  //   printf("c:[%s]\n", strncat(temp2, argv[i], 5));
  // }
  // return 0;
  // ----------
  // S21_STRLEN
  // ----------
  // char temp[1024] = {0};
  // printf("s21:%li\n", s21_strlen(temp));
  // printf("C:%li\n\n", strlen(temp));

  // strcpy(temp, "biba\0");
  // printf("s21:%li\n", s21_strlen(temp));
  // printf("C:%li\n\n", strlen(temp));

  // strcpy(temp, "biba");
  // printf("s21:%li\n", s21_strlen(temp));
  // printf("C:%li\n\n", strlen(temp));

  // strcpy(temp, "b");
  // printf("s21:%li\n", s21_strlen(temp));
  // printf("C:%li\n\n", strlen(temp));
  // ----------
  // S21_STRSPN
  // ----------
  // char temp1[1024] = "123456789";
  // char temp2[1024] = "56789";
  // char temp3[1024] = "156789";
  // char temp4[1024] = "56789";
  // printf("s21:[%li]\n", s21_strspn(temp2, temp1));
  // printf("c:[%li]\n", strspn(temp2, temp1));
  // printf("s21:[%li]\n", s21_strspn(temp1, temp2));
  // printf("c:[%li]\n", strspn(temp1, temp2));
  // printf("s21:[%li]\n", s21_strspn(temp3, temp4));
  // printf("c:[%li]\n", strspn(temp3, temp4));
  // printf("s21:[%li]\n", s21_strspn(temp4, temp3));
  // printf("c:[%li]\n", strspn(temp4, temp3));

  // char temp5[1024] = "12345";
  // char temp6[1024] = "";
  // printf("s21:[%li]\n", s21_strcspn(temp5, temp6));
  // printf("c:[%li]\n", strcspn(temp5, temp6));
  // printf("s21:[%li]\n", s21_strcspn(temp6, temp5));
  // printf("c:[%li]\n", strcspn(temp6, temp5));
  // // -----------
  // S21_STRRCHR
  // -----------
  // for (int i = 0; i < argc; i++) {
  //   char *love = NULL;
  //   love = calloc(100, sizeof(char));
  //   if (s21_strrchr(argv[i], 'z') != NULL) {
  //     printf("yes\n");
  //     s21_strcpy(love, strrchr(argv[i], 'z'));
  //     printf("c:[%c]", love[0]);
  //     printf("c:[%s]\n", love);
  //     s21_strcpy(love, s21_strrchr(argv[i], 'z'));
  //     printf("s21:[%c]", love[0]);
  //     printf("s21:[%s]\n", love);
  //   } else {
  //     printf("no\n");
  //   }
  // }
  // ----------
  // S21_STRCSPN
  // ----------
  // char temp1[1024] = "123456789";
  // char temp2[1024] = "56789";
  // char temp3[1024] = "156789";
  // char temp4[1024] = "56789";

  // printf("s21:[%li]\n", s21_strcspn(temp2, temp1));
  // printf("c:[%li]\n", strcspn(temp2, temp1));
  // printf("s21:[%li]\n", s21_strcspn(temp1, temp2));
  // printf("c:[%li]\n", strcspn(temp1, temp2));
  // printf("s21:[%li]\n", s21_strcspn(temp3, temp4));
  // printf("c:[%li]\n", strcspn(temp3, temp4));
  // printf("s21:[%li]\n", s21_strcspn(temp4, temp3));
  // printf("c:[%li]\n\n", strcspn(temp4, temp3));

  // char temp5[1024] = "12345";
  // char temp6[1024] = "";
  // printf("s21:[%li]\n", s21_strcspn(temp5, temp6));
  // printf("c:[%li]\n", strcspn(temp5, temp6));
  // printf("s21:[%li]\n", s21_strcspn(temp6, temp5));
  // printf("c:[%li]\n", strcspn(temp6, temp5));
  // ----------
  // S21_STRTOK
  // ----------

  // S21:
  // ----
  char delims[1024] = ",:;";
  char temp[1024] = "aboba,abiba,bobka,popa,,,,::;;;;aboba;abiba";
  printf("с:[%s]\n", s21_strtok(temp, delims));
  for (int i = 0; i < 40; i++) {
    printf("с:[%s]\n", s21_strtok(NULL, delims));
  }

  char temp2[1024] = ",";
  printf("с:[%s]\n", s21_strtok(temp2, delims));
  for (int i = 0; i < 4; i++) {
    printf("с:[%s]\n", s21_strtok(NULL, delims));
  }

  char temp3[1024] = ",,";
  printf("с:[%s]\n", s21_strtok(temp3, delims));
  for (int i = 0; i < 4; i++) {
    printf("с:[%s]\n", s21_strtok(NULL, delims));
  }

  char temp4[1024] = ",a,";
  printf("с:[%s]\n", s21_strtok(temp4, delims));
  for (int i = 0; i < 4; i++) {
    printf("с:[%s]\n", s21_strtok(NULL, delims));
  }

  // C:
  // --
  // char delims[1024] = ",:;";
  // char temp[1024] = "aboba,abiba,bobka,popa,,,,::;;;;aboba;abiba";
  // printf("с:[%s]\n", strtok(temp, delims));
  // for (int i = 0; i < 20; i++) {
  //   printf("с:[%s]\n", strtok(NULL, delims));
  // }

  // char temp2[1024] = ",";
  // printf("с:[%s]\n", strtok(temp2, delims));
  // for (int i = 0; i < 4; i++) {
  //   printf("с:[%s]\n", strtok(NULL, delims));
  // }

  // char temp3[1024] = ",,";
  // printf("с:[%s]\n", strtok(temp3, delims));
  // for (int i = 0; i < 4; i++) {
  //   printf("с:[%s]\n", strtok(NULL, delims));
  // }

  // char temp4[1024] = ",a,";
  // printf("с:[%s]\n", strtok(temp4, delims));
  // for (int i = 0; i < 4; i++) {
  //   printf("с:[%s]\n", strtok(NULL, delims));
  //   // }
  // }
  return 0;
}